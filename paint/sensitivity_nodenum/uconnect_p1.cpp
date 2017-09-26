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
//const double PROB1 = 0.5;
//const double PROB2 = 0.5;
const int TIMES = 100;
const int NODENUM = 21;

int latency[1000][1000];
int neighborMap[1000][1000];
int aveLatency[1000][1000];
std::vector<int> primeset;
int P[m];
double the[m];

void findAllPrimes(int n)
{
   
    primeset.push_back(2);
    for(int k = 3; k<=n; k++){
        bool isPrime = true;
        for(int i = 2; i*i <= k; i++){
            if(k % i == 0){
                isPrime = false;
                break;
            }
        }
        if(isPrime) {
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
  	int t1, t2;
  	bool noOnBefore;
  	double PROB1;
  	double PROB2;
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
	    t1 = 0;
	    t2 = 0;
	    noOnBefore = true;
		uconnect_generate_cn();
	}
	void resetStartTime(){
		startTime = rand()%(STARTRANGE+1);
	}

	//Energy Module Algorithm 1
	void energySupply1(double theta0){
		setTheta(theta0 / Pmax * this->energy);
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
		t1 = 0;
		t2 = 0;
		noOnBefore = true;
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
		n = c;
		uconnect_init_output();
	}
	
	void uconnect_init_output(){
		std::stringstream ss;
	    ss << "uconnect/Prime Time.txt";
	    std::fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	    f << "Node " << ID << ", start at "<<startTime<<", n: "<<n<<", c:"<<c<<std::endl;
	}
	
	bool uconnect_isOff(int time){
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
	
	
	bool uconnect_isOff_collision1(int time){
		int num = rand()%10;
		if(uconnect_isOff(time) == false){	
			if(num*1.0/10 < PROB1){
				return false;
			}
    	}
    	return true;
	}
	
	void findNext(int time, int timeInterval){
		if(uconnect_isOff(time) == false){
			t1 = time;
			for(int i = t1+1; i < timeInterval; i++){
				if(uconnect_isOff(i) == false){
					t2 = i;
					noOnBefore = true;
					return;
				}
			}
		}
	}
	
	bool uconnect_isOff_collision2(int tt, int timeInterval){
		findNext(tt, timeInterval);
		if(t1 != 0 && t2 != 0 && t1 < t2 && noOnBefore){
			double poss = (t2-tt)*1.0/(t2-t1+1);
      		double realP = poss * PROB2;
			int x = rand()%10000;
			if(realP * 10000 <= x){
				noOnBefore = false;
				return false;
			}
			return true;
		}
		else if(t1 != 0 && t1 > t2 && t1 == tt){
			return false;
		}
		return true;
	}
	
	
};

wifiContainer w[NODENUM];

void initEnergySupply2(double theta0){
	stringstream ss;
	ss << "uconnect/energy_theta_table.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	
	w[0].energy = Pmax;
	w[0].setTheta(theta0);
	w[0].alive = true;
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

void setAllPROB1(double prob){
	for(int i = 0; i < NODENUM; i++){
		w[i].PROB1 = prob;
	}
}

void setAllPROB2(double prob){
	for(int i = 0; i < NODENUM; i++){
		w[i].PROB2 = prob;
	}
}

void setAllTheta(double the){
	for(int i = 0; i < NODENUM; i++){
		w[i].setTheta(the);
	}
}

void ModCollision_1(int timeInterval)
{
	int findNeighborTime[NODENUM];
	int starlatency = MAX_INT;;
	int onNeighbor = 0;
	int max = 0;
	int now = 0;
	for(int i = 0; i < NODENUM; i++){
		wifiContainer tempw(i);
		w[i] = tempw;
		findNeighborTime[i] = 0;
	}
	stringstream ss;
	ss << "uconnect/mod1.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	setAllTheta(0.3);
	for(double prob = 0.1; prob <= 0.9; prob+=0.1){
		setAllPROB1(prob);
		for(int s = 0; s < TIMES; s++){
			for(int timeFrame = w[0].startTime; timeFrame <= timeInterval; timeFrame ++){
				if(w[0].uconnect_isOff_collision1(timeFrame) == false){
					for(int j = 1; j < NODENUM; j++){
						if(w[j].uconnect_isOff_collision1(timeFrame) == false){
							onNeighbor++;
						}
					}
					if(onNeighbor == 1){
						for(int j = 1; j < NODENUM; j++){
							if(w[j].uconnect_isOff_collision1(timeFrame) == false && findNeighborTime[j] == 0){
								findNeighborTime[j] = timeFrame;
								max = timeFrame;
							}
						}
					}
				}
				onNeighbor = 0;
			}
			starlatency += max - w[0].startTime;
			now = now>max?now:max;
			
			
			for(int l = 1; l < NODENUM; l++){
				findNeighborTime[l] = 0;
			}
			if(max == 0){
				starlatency = MAX_INT;
				break;
			}
			max = 0;
		}
		
		if(starlatency == MAX_INT){
//			cout<<"theta = "<<w[0].theta<<",   avelatency = "<<MAX_INT<<"   ,maxlatency="<<MAX_INT<<endl;
			f<<prob<<","<<MAX_INT<<","<<MAX_INT<<endl;
		}
		else{
//			cout<<"theta = "<<w[0].theta<<",   avelatency = "<<starlatency/TIMES<<"   ,maxlatency="<<now-w[0].startTime<<endl;
			f<<prob<<","<<starlatency/TIMES<<","<<now-w[0].startTime<<endl;
		}
		starlatency = 0;
	}
}

void ModCollision_2(int timeInterval)
{
	int findNeighborTime[NODENUM];
	int starlatency = MAX_INT;;
	int onNeighbor = 0;
	int max = 0;
	int now = 0;
	bool temp[NODENUM];
	for(int i = 0; i < NODENUM; i++){
		wifiContainer tempw(i);
		w[i] = tempw;
		findNeighborTime[i] = 0;
	}
	
	stringstream ss;
	ss << "uconnect/mod2.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	setAllTheta(0.3);
	
	for(double prob = 0.1; prob <= 0.9; prob+=0.1) {
		setAllPROB2(prob);
		for(int s = 0; s < TIMES; s++){
			for(int timeFrame = w[0].startTime; timeFrame <= timeInterval; timeFrame ++){
				for(int x = 0; x < NODENUM; x++){
					temp[x] = w[x].uconnect_isOff_collision2(timeFrame, timeInterval);
				}
				if(temp[0] == false){
					for(int j = 1; j < NODENUM; j++){
						if(temp[j] == false){
							onNeighbor++;
						}
					}
					if(onNeighbor == 1){
						for(int j = 1; j < NODENUM; j++){
							if(temp[j] == false && findNeighborTime[j] == 0){
								findNeighborTime[j] = timeFrame;
								max = timeFrame;
							}
						}
					}
				}
				onNeighbor = 0;
			}
			starlatency += max - w[0].startTime;
			now = now>max?now:max;
			
			
			for(int l = 1; l < NODENUM; l++){
				findNeighborTime[l] = 0;
			}
			if(max == 0){
				starlatency = MAX_INT;
//				max = 0;
//				break;
			}
			max = 0;
		}
		if(starlatency == MAX_INT){
			f<<prob<<","<<MAX_INT<<","<<MAX_INT<<endl;
		}
		else{
			f<<prob<<","<<starlatency/TIMES<<","<<now-w[0].startTime<<endl;
		}
		starlatency = 0;
	}
}

int main (int argc, char *argv[])
{
	srand(time(NULL));
	
	findAllPrimes(10000);
	
//  	ModCollision_1(100000);
  	ModCollision_2(100000);

	return 0;
}
