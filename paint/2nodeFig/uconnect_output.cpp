/*

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>

using namespace std;

//NS_LOG_COMPONENT_DEFINE ("WifiSimpleAdhocGrid");

const int STARTRANGE = 1000;
const int SCOPE = 1000;
const int Pmax = 100000;
const int Pmin = 200;
const int pn = 1;
const int MAX_INT = -1;
const int CYCLENUM = 20;
const int T = 100000;
const int m = 30;
const int dc = 50;

int latency[1000][1000];
int neighborMap[1000][1000];
int aveLatency[1000][1000];
std::vector<int> primeset;
int P[m];
double the[m];

void findAllPrimes(int n)
{

    primeset.push_back(2);
    for(int k = 3; k<=n; k++)
    {
        bool isPrime = true;
        for(int i = 2; i*i <= k; i++)
        {
            if(k % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        if(isPrime)
        {
            primeset.push_back(k);
        }
    }

}
void initLatency()
{
	for(int i = 0; i < 1000; i++){
		for (int j = 0; j < 1000; j++){
      		latency[i][j] = MAX_INT;
    	}
  	}
}

class wifiContainer
{
public:
	int startTime;
  	long long endTime;
  	double x, y;
  	bool alive;
  	int ID;
  	int energy;
  	double theta;
  	int c;
  	int n;
//  	int anchor;  //only in hedis
	wifiContainer(){
	}
	wifiContainer(int id)
	{
	    ID = id;
	    alive = true;
	    energy = Pmax;
	    startTime = rand()%(STARTRANGE+1);
	    endTime = -1;
	    x = rand()%(SCOPE+1);
	    y = rand()%(SCOPE+1);
	    theta = 0.1+(rand()%9)*0.05;
	    uconnect_generate_cn();
	}
	void resetStartTime(){
		startTime = rand()%(STARTRANGE+1);
	}

	//Energy Module Algorithm 1
	void energySupply1(double theta0){
		setTheta(theta0 / Pmax * this->energy);
//		cout<<"energy="<<energy<<" ,theta="<<theta<<endl;
	}

	//Energy Module Algorithm 2
	void energySupply2(){
		for(int i = 0; i < m; i++){
			if(energy <= Pmin){
				setTheta(Pmin*1.0/Pmax * the[0]);
				break;
			}
			else if(energy > P[i]){
				setTheta(the[i-1]);
				break;
			}
		}
	}

	void setTheta(double the){
		theta = the;
		uconnect_generate_cn();
	}
	void uconnect_generate_cn(){
		double num = 1.5 / theta;
		for(int i = 0; i < primeset.size(); i++){
			if(primeset[i] == num){
				this->c = primeset[i];
				break;
			}
			else if(primeset[i] > num && i >= 1){
				if( primeset[i]-num < num-primeset[i-1]){
					this->c = primeset[i];
				}
				else{
					this->c = primeset[i-1];
				}
				break;
			}
			else if(primeset[i] > num && i == 0){
				this->c = primeset[i];
				break;
			}
		}
//		cout<<ID<<" "<<theta<<" c="<<c<<" n="<<n<<endl;
		n = c;
		uconnect_init_output();
	}

	void uconnect_init_output(){
		std::stringstream ss;
	    ss << "uconnect/Prime Time.txt";
	    std::fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	    f << "Node " << ID << ", start at "<<startTime<<", n: "<<n<<", c:"<<c<<std::endl;
	}

	bool uConnect_isOff(int time){
    	if(time - startTime > 0){
      		if ( ( time-startTime  ) % (c * n) < c/2.0 || ( time-startTime ) % c == 0){
      			return false;
			}

      		else
        		return true;
    	}
    	else if (time - startTime == 0)
      		return false;
    	else
      		return true;
    }

};

wifiContainer warray[1000];

void initMap()
{
	for(int i = 0; i < 1000; i++){
		wifiContainer wc(i);
		warray[i] = wc;
	}

	for(int i = 0; i < 1000; i++){
		for(int j = 0; j < 1000; j++){
			if(sqrt((warray[i].x-warray[j].x)*(warray[i].x-warray[j].x)+(warray[i].y-warray[j].y)*(warray[i].y-warray[j].y)) <= dc && i != j){//warray[i].alive == true && warray[j].alive == true &&
				neighborMap[i][j] = 1;
				neighborMap[j][i] = 1;
			}
		}
	}
}

void setLatency(int i, int j, int t)
{
  	if(latency[i][j] == MAX_INT)
  	{
    	if (warray[i].startTime > warray[j].startTime){
    		latency[i][j] = t - warray[i].startTime;
    	}

    	else{
    		latency[i][j] = t - warray[j].startTime;
    	}
  	}
}

void initEnergySupply2(double theta0)
{
	stringstream ss;
	ss << "uconnect/energy_theta_table.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);

	warray[0].energy = Pmax;
	warray[0].setTheta(theta0);
	warray[0].alive = true;
	P[0] = Pmax;
	the[0] = theta0;
	cout<<0<<" "<<P[0]<<" "<<the[0]<<endl;
	for(int i = 1; i < m; i++){
		P[i] = P[i-1] - T * the[i-1] * pn;
		the[i] = P[i]*1.0/P[0] * the[0];
		f<<i<<" "<<P[i]<<" "<<the[i]<<endl;
		cout<<i<<" "<<P[i]<<" "<<the[i]<<endl;
	}
}

//Figure 1
void twoNodeNoModCollision(int timeInterval, int arrayLength)
{
  int twoNodeAvgLatency[21]={0};
  int twoNodeMaxLatency[21]={0};
  for (int i = 0; i < arrayLength; i++)
  {
  	wifiContainer A(0), B(1);
  	A.setTheta(0.2);
  	int latency = -1;
  	double timeFrame;
  //	Time t;
  	A.startTime = rand()%(STARTRANGE+1);
  	B.startTime = rand()%(STARTRANGE+1);
  	int laterTime = A.startTime > B.startTime ? A.startTime : B.startTime;

  	for(double bthe = 0.1; bthe <= 0.31; bthe += 0.01) {
  		latency = MAX_INT;
  		B.setTheta(bthe);
  		B.resetStartTime();//???????????
  		laterTime = A.startTime > B.startTime ? A.startTime : B.startTime;//??????????

  		for(int timeFrame = 1; timeFrame <= timeInterval; timeFrame ++){
  //				t = Seconds(timeFrame);
  			if(A.uConnect_isOff(timeFrame) == false && B.uConnect_isOff(timeFrame) == false){//i and j are neighbors in default
  				latency = timeFrame - laterTime;
  				break;
  			}
  		}
      double temp = (bthe - 0.10)/0.01;
      int nodeNum = (int) (temp+0.5);
      if( latency != MAX_INT){
        twoNodeAvgLatency[nodeNum] += latency;
        if (twoNodeMaxLatency[nodeNum] < latency)
          twoNodeMaxLatency[nodeNum] = latency;
      }
  		cout <<"A.startTime:"<<A.startTime<<" A.theta:"<<A.theta<<" B.startTime:"<<B.startTime<<" B.theta:"<<B.theta<<" latency:" <<latency<<endl;
      }
  	}
    stringstream ss;
      ss << "uconnect/two_node_latency.txt";
      fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
      for (int i=0;i<21;i++)
      {
        double th = i*0.01 + 0.1;
        twoNodeAvgLatency[i]=twoNodeAvgLatency[i]/arrayLength;
        f <<th << "," << twoNodeAvgLatency[i] <<","<< twoNodeMaxLatency[i] <<endl;
      }
}

//Figure 2 run one time
/*
void noModCollision2(int timeInterval)
{
	int onNeighbor[1000];

//	Time t;

	initLatency();
    initMap();

    for(int i = 0; i < 1000; i++){
		onNeighbor[i] = 0;

	}

	for(int timeFrame = 1; timeFrame <= timeInterval; timeFrame ++){
//			t = Seconds(timeFrame);

		for(int i = 0; i < 1000; i++){
			if(warray[i].hedis_isOff(timeFrame) == false){
				for(int j = 0; j < 1000; j++){
					if(warray[j].hedis_isOff(timeFrame) == false && neighborMap[i][j] == 1){
						onNeighbor[j]++;
					}
				}
			}
		}

		for(int i = 0; i < 1000; i++){
			if(onNeighbor[i] == 1 && warray[i].hedis_isOff(timeFrame) ==false){
				for(int j = 0; j < 1000; j++){
					if(neighborMap[i][j] == 1 && onNeighbor[j] == 1 && warray[j].hedis_isOff(timeFrame) ==false){
						setLatency(i, j, timeFrame);
						cout<<timeFrame<<" "<<i<<" "<<j<<endl;
					}
				}
			}
		}
		for(int i = 0; i < 1000; i++){
			onNeighbor[i] = 0;
		}
	}
	stringstream ss;
	ss << "hedis/thousand_node_latency.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);

	for(int i = 0; i < 1000; i++){
		for(int j = 0; j < 1000; j++){
			f <<latency[i][j]<<",";
		}
		f<<endl;
	}
}
*/

//Figure 2 run arrayLength times to compute the average latency
void noModCollision2(int timeInterval, int arrayLength)
{
	int onNeighbor[1000];
//
	stringstream ss;
	ss << "uconnect/thousand_times_latency.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);

//	Time t;

	initLatency();
    initMap();

    for(int i = 0; i < 1000; i++){
		onNeighbor[i] = 0;
		for(int j = 0; j < 1000; j++){
			aveLatency[i][j] = 0;
		}
	}
	for(int k = 0; k < arrayLength; k++){
		cout<<"******************"<<k<<"***************"<<endl;
		for(int timeFrame = 1; timeFrame <= timeInterval; timeFrame++){
//			t = Seconds(timeFrame);
			if(timeFrame%10000 == 0) cout<<"******************"<<"timeFrame/10000="<<timeFrame/10000<<"***************"<<endl;
			for(int i = 0; i < 1000; i++){
				if(warray[i].uConnect_isOff(timeFrame) == false){
					for(int j = 0; j < 1000; j++){
						if(warray[j].uConnect_isOff(timeFrame) == false && neighborMap[i][j] == 1){
							onNeighbor[j]++;
						}
					}
				}
			}

			for(int i = 0; i < 1000; i++){
				if(onNeighbor[i] == 1 && warray[i].uConnect_isOff(timeFrame) ==false){
					for(int j = 0; j < 1000; j++){
						if(neighborMap[i][j] == 1 && onNeighbor[j] == 1 && warray[j].uConnect_isOff(timeFrame) ==false){
							setLatency(i, j, timeFrame);
							cout<<timeFrame<<" "<<i<<" "<<j<<endl;
						}
					}
				}
			}
			for(int i = 0; i < 1000; i++){
				onNeighbor[i] = 0;
			}
		}

		for(int i = 0; i < 1000; i++){
			for(int j = 0; j < 1000; j++){
				if(neighborMap[i][j] == 1 && latency[i][j] != MAX_INT){
					aveLatency[i][j] += latency[i][j];
				}
			}
		}
		initLatency();
	}
	for(int i = 0; i < 1000; i++){
		for(int j = 0; j < 1000; j++){
			aveLatency[i][j] = aveLatency[i][j]/arrayLength;
			f<<aveLatency[i][j]<<",";
		}
		f<<endl;
	}
}

//Figure 3 First curve
//void noModCollision3_1(int timeInterval, int arrayLength)
//{
//	int onNeighbor[1000];
//	int theta0 = 0.3;
////	Time t;
//
//	initLatency();
//    initMap();
//
//    for(int i = 0; i < 1000; i++){
//		onNeighbor[i] = 0;
//		warray[i].setTheta(theta0);
//	}
//
//	for(int k = 1; k < arrayLength; k++){
//		for(int timeFrame = 1; timeFrame <= timeInterval; timeFrame ++){
////			t = Seconds(timeFrame);
//			//onOff = function;dutycycle is not changed, algorithm,figure 3 undone
//			for(int i = 0; i < 1000; i++){
//				if(warray[i].alive == true && warray[i].hedis_isOff(timeFrame) == false){
//					warray[i].energy -= pn;
//					if(warray[i].energy <= Pmin){
//						warray[i].alive = false;
//						warray[i].endTime = timeFrame;
//					}
//					for(int j = 0; j < 1000; j++){
//						if(warray[j].alive == true && warray[j].hedis_isOff(timeFrame) == false && neighborMap[i][j] == 1){
//							onNeighbor[j]++;
//						}
//					}
//				}
//			}
//			for(int i = 0; i < 1000; i++){
//				if(onNeighbor[i] == 1 && warray[i].alive == true && warray[i].hedis_isOff(timeFrame) ==false){
//					for(int j = 0; j < 1000; j++){
//						if(neighborMap[i][j] == 1 && onNeighbor[j] == 1 && warray[j].alive == true && warray[j].hedis_isOff(timeFrame) ==false){
//							setLatency(i, j, timeFrame);
//							cout<<timeFrame<<" "<<i<<" "<<j<<endl;
//						}
//					}
//				}
//			}
//		}
//		stringstream ss;
//    	ss << "hedis/energy_node_latency.csv";
//    	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
//
//		for(int i = 0; i < 1000; i++){
//			for(int j = 0; j < 1000; j++){
//				f <<latency[i][j]<<",";
//			}
//			f<<endl;
//		}
//	}
//	//latency output, calculate percentage
//}

//Figrue 3 & 4: star, node0
void energyAlg1(int timeInterval, double theta0)
{
	double dutycycle[CYCLENUM];
	double percent[CYCLENUM];
	int late[CYCLENUM];
	int findNeighborTime[1000];
	int onNeighbor=0;
	int i = 0;
	int max = 0;
	bool flag = true;

	stringstream ss;
	ss << "uconnect/energy1.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);

	for(int l = 0; l < 1000; l++){
		findNeighborTime[l] = 0;
		warray[i].setTheta(theta0);

	}


//	warray[0].energy = Pmax;

	warray[i].endTime = CYCLENUM * timeInterval;
	for(int k = 0; k < CYCLENUM && warray[i].alive == true; k++){
		for(int timeFrame = warray[0].startTime; timeFrame <= timeInterval && warray[i].alive == true; timeFrame ++){
			if(warray[i].alive == true && warray[i].uConnect_isOff(timeFrame) == false){
				warray[i].energy -= pn;
//				if(warray[i].energy <= Pmin && flag == true){
//					warray[i].endTime = k * timeInterval + timeFrame;
//					flag = false;
//				}
				if(warray[i].energy <= 0 && flag == true){
					warray[i].alive = false;
					warray[i].endTime = k * timeInterval + timeFrame;
					flag = false;
					cout<<"+++++++++++++++++++++++++++++++++++++++++++"<<endl;
					break;
				}
				for(int j = 0; j < 1000; j++){
					if(warray[j].alive == true && warray[j].uConnect_isOff(timeFrame) == false && neighborMap[i][j] == 1){
						onNeighbor++;
					}
				}
				if(onNeighbor == 1){
					for(int j = 0; j < 1000; j++){
						if(neighborMap[i][j] == 1 && warray[j].alive == true && warray[j].uConnect_isOff(timeFrame) == false && findNeighborTime[j] == 0){
							findNeighborTime[j] = timeFrame;
						}
					}
				}
			}
			onNeighbor = 0;
		}

//		cout<<"energy = "<<warray[0].energy<<endl;
		warray[0].energySupply1(theta0);
		dutycycle[k] = warray[0].theta;
		percent[k] = warray[0].energy*1.0 / Pmax;

		for(int l = 0; l < 1000; l++){
			max = findNeighborTime[l] > max ? findNeighborTime[l] : max;
		}
//		cout<<"max="<<max<<endl;
		late[k] = max - warray[0].startTime;

		cout<<k<<" "<<dutycycle[k]<<" "<<percent[k]<<" "<<late[k]<<endl;

		for(int l = 0; l < 1000; l++){
			findNeighborTime[l] = 0;
		}
		max = 0;
	}

	cout<<"life Cycle = "<<warray[0].endTime - warray[0].startTime<<endl;
	for(int k = 0; k <CYCLENUM; k++){
		f<<k<<": "<<dutycycle[k]<<",";
		f<<percent[k]<<",";
		f<<late[k]<<endl;

	}
	f<<"life Cycle = "<<warray[0].endTime - warray[0].startTime<<endl;
	f<<"*********************************************************************"<<endl;
}

void energyAlg2(int timeInterval, double theta0)
{
	double dutycycle[CYCLENUM];
	double percent[CYCLENUM];
	int late[CYCLENUM];
	int findNeighborTime[1000];
	int onNeighbor=0;
	int i = 0;
	int bound = CYCLENUM;
	int max = 0;
	bool flag = true;

	stringstream ss;
	ss << "uconnect/energy2.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);

//	warray[0].energy = Pmax;
	initEnergySupply2(theta0);

	for(int l = 0; l < 1000; l++){
		findNeighborTime[l] = 0;
		warray[0].setTheta(theta0);
	}

	for(int k = 0; k < CYCLENUM && warray[i].alive == true; k++){
		for(int timeFrame = warray[0].startTime; timeFrame <= timeInterval && warray[i].alive == true; timeFrame ++){
			if(warray[i].alive == true && warray[i].uConnect_isOff(timeFrame) ==false){
				warray[i].energy -= pn;
//				if(warray[i].energy <= Pmin && flag == true){
//					flag == false;
//					warray[i].endTime = k * timeInterval + timeFrame;
//				}
				if(warray[i].energy <= 0 && flag == true){
					warray[i].alive = false;
					warray[i].endTime = k * timeInterval + timeFrame;
					bound = k;
					cout<<"+++++++++++++++++++++++++++++++++++++++++++"<<endl;
					break;
				}
				for(int j = 0; j < 1000; j++){
					if(warray[j].alive == true && warray[j].uConnect_isOff(timeFrame) == false && neighborMap[i][j] == 1){
						onNeighbor++;
					}
				}
				if(onNeighbor == 1){
					for(int j = 0; j < 1000; j++){
						if(neighborMap[i][j] == 1 && warray[j].alive == true && warray[j].uConnect_isOff(timeFrame) == false && findNeighborTime[j] == 0){
							findNeighborTime[j] = timeFrame;
						}
					}
				}
			}
			onNeighbor = 0;
		}

		warray[0].energySupply2();
//		cout<<"energy = "<<warray[0].energy<<" alive="<<warray[0].alive<<endl;
		dutycycle[k] = warray[0].theta;
		percent[k] = warray[0].energy*1.0 / Pmax;

		for(int l = 0; l < 1000; l++){
			max = findNeighborTime[l] > max ? findNeighborTime[l] : max;
		}
//		cout<<"max="<<max<<endl;
		late[k] = max - warray[0].startTime;

		cout<<k<<" "<<dutycycle[k]<<" "<<percent[k]<<" "<<late[k]<<endl;

		for(int l = 0; l < 1000; l++){
			findNeighborTime[l] = 0;
		}
		max = 0;
	}
//	cout<<warray[0].endTime<<endl;
//	cout<<warray[0].startTime<<endl;
	cout<<"life Cycle = "<<warray[0].endTime - warray[0].startTime<<endl;
	for(int k = 0; k < bound; k++){
		f<<k<<": "<<dutycycle[k]<<",";
		f<<percent[k]<<",";
		f<<late[k]<<endl;

	}
	f<<"life Cycle = "<<warray[0].endTime - warray[0].startTime<<endl;
	f<<"******************************************************************"<<endl;
}

//2 nodes symmertric
void twoNodeNoModCollisionSymmetric(int timeInterval, int arrayLength)
{
  int twoNodeAvgLatency[21]={0};
  int twoNodeMaxLatency[21]={0};
  for (int i = 0; i < arrayLength; i++)
  {
  	wifiContainer A(0), B(1);
  	int latency = -1;
  	double timeFrame;
  //	Time t;
  	A.startTime = rand()%(STARTRANGE+1);
  	B.startTime = rand()%(STARTRANGE+1);
  	int laterTime = A.startTime > B.startTime ? A.startTime : B.startTime;

  	for(double bthe = 0.1; bthe <= 0.31; bthe += 0.01) {
  		latency = MAX_INT;
      A.setTheta(bthe);
  		B.setTheta(bthe);
      A.resetStartTime();
  		B.resetStartTime();//???????????
  		laterTime = A.startTime > B.startTime ? A.startTime : B.startTime;//??????????

  		for(int timeFrame = 1; timeFrame <= timeInterval; timeFrame ++){
  //				t = Seconds(timeFrame);
  			if(A.uConnect_isOff(timeFrame) == false && B.uConnect_isOff(timeFrame) == false){//i and j are neighbors in default
  				latency = timeFrame - laterTime;
  				break;
  			}
  		}
      double temp = (bthe - 0.10)/0.01;
      int nodeNum = (int) (temp+0.5);
      if( latency != MAX_INT){
        twoNodeAvgLatency[nodeNum] += latency;
        if (twoNodeMaxLatency[nodeNum] < latency)
          twoNodeMaxLatency[nodeNum] = latency;
      }
  		cout <<"A.startTime:"<<A.startTime<<" A.theta:"<<A.theta<<" B.startTime:"<<B.startTime<<" B.theta:"<<B.theta<<" latency:" <<latency<<endl;
      }
  	}
    stringstream ss;
      ss << "uconnect/two_node_latency_sym.txt";
      fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
      for (int i=0;i<21;i++)
      {
        double th = i*0.01 + 0.1;
        twoNodeAvgLatency[i]=twoNodeAvgLatency[i]/arrayLength;
        f <<th << "," << twoNodeAvgLatency[i] <<","<< twoNodeMaxLatency[i] <<endl;
      }
}

void noModCollisionAdjust(int timeInterval)
{
	double theta0 = 0.3;
    initMap();

	energyAlg1(timeInterval, theta0);
	energyAlg2(timeInterval, theta0);
}

void modCollision()
{

}



int main (int argc, char *argv[])
{
	srand(time(NULL));
	findAllPrimes(10000);


	 twoNodeNoModCollision(100000,1000);
//  noModCollision2(100000, 100);
//	noModCollisionAdjust(100000);
  twoNodeNoModCollisionSymmetric(100000,1000);
	return 0;
}
