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
const int NODENUM=100;
const int theta0 = 0.3;

int latency[NODENUM][NODENUM];
int neighborMap[NODENUM][NODENUM];
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
	for(int i = 0; i < NODENUM; i++){
		for (int j = 0; j < NODENUM; j++){
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
  	int anchor;  //only in hedis
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
	    hedis_generate_anchor();

	}
	void reset(){
		alive = true;
	    energy = Pmax;
	}

	//Energy Module Algorithm 1
	void energySupply1(double theta0){
		theta = theta0 / Pmax * this->energy;
		hedis_generate_anchor();
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
		hedis_generate_anchor();
	}
	void hedis_generate_anchor(){
		double num = 2/theta;
		for(int i = 0; i < primeset.size(); i++){
			if(primeset[i] == num){
				this->anchor = primeset[i];
				break;
			}
			else if(primeset[i] > num && i >= 1){
				this->anchor = primeset[i]-num < num -  primeset[i-1] ? primeset[i] : primeset[i-1];
				break;
			}
			else if(primeset[i] > num && i == 0){
				this->anchor = primeset[i];
				break;
			}
		}
//		cout<<ID<<" "<<theta<<" "<<anchor<<endl;
		hedis_init_output();
	}

	void hedis_init_output(){
		stringstream ss;
    	ss << "hedis/Prime_Time_pset.txt";
    	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
    	f << "Node " << ID << ", start at "<<startTime<<", anchor: " << anchor <<std::endl;
//    	cout<<ID<<" "<<anchor<<endl;
	}

	bool hedis_isOff(int time){
		if( time - startTime > 0)
    	{
//    		cout<<"anchor=" <<anchor<<endl;
      		if ( (time - startTime) % anchor == 0 || (time - startTime - 1) % ( anchor + 1 ) == 0 )
      		{
//      			cout<<startTime<<" time"<<time<<endl;
          		return false;

      		}
    	}
    	return true;
	}

};

wifiContainer warray[NODENUM];

void initMap()
{
	stringstream ss;
	ss << "hedis/neighborMap.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	for(int i = 0; i < NODENUM; i++){
		wifiContainer wc(i);
		warray[i] = wc;
	}

	for(int i = 0; i < NODENUM; i++){
		for(int j = 0; j < NODENUM; j++){
			if(sqrt((warray[i].x-warray[j].x)*(warray[i].x-warray[j].x)+(warray[i].y-warray[j].y)*(warray[i].y-warray[j].y)) <= dc && i != j){//warray[i].alive == true && warray[j].alive == true &&
				neighborMap[i][j] = 1;
				neighborMap[j][i] = 1;
			}
		}
	}
	for(int i = 0; i < NODENUM; i++){
		for(int j = 0; j < NODENUM; j++){
			f<<neighborMap[i][j]<<",";
		}
		f<<endl;
	}
}

void setLatency(int i, int j, int t)
{
  	if(latency[i][j] == MAX_INT)
  	{
    	if (warray[i].startTime > warray[j].startTime){
    		latency[i][j] = t - warray[i].startTime;
    		latency[j][i] = t - warray[i].startTime;
    	}

    	else{
    		latency[i][j] = t - warray[j].startTime;
    		latency[j][i] = t - warray[j].startTime;
    	}
  	}
}

void initEnergySupply2(double theta0){
	stringstream ss;
	ss << "hedis/energy_theta_table.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	
	
	
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


//Figure 2 run arrayLength times to compute the average latency
void noModCollision2(int timeInterval, int arrayLength)
{
	int onNeighbor[NODENUM];
	stringstream ss;
	ss << "hedis/thousand_times_latency.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);


	initLatency();
	for(int i = 0; i < NODENUM; i++){
		warray[i].reset();
		onNeighbor[i] = 0;
	}
	
	for(int k = 0; k < arrayLength; k++){
		
		for(int timeFrame = 1; timeFrame <= timeInterval; timeFrame++){
			for(int i = 0; i < NODENUM; i++){
				warray[i].endTime++;
				if(warray[i].hedis_isOff(timeFrame) == false){
					warray[i].energy -= pn;
					for(int j = 0; j < NODENUM; j++){
						if(warray[j].hedis_isOff(timeFrame) == false && neighborMap[i][j] == 1){
							onNeighbor[j]++;
						}
					}
				}
			}

			for(int i = 0; i < NODENUM; i++){
				if(onNeighbor[i] == 1 && warray[i].hedis_isOff(timeFrame) ==false){
					for(int j = 0; j < NODENUM; j++){
						if(neighborMap[i][j] == 1 && onNeighbor[j] == 1 && warray[j].hedis_isOff(timeFrame) ==false && latency[i][j] == MAX_INT){
							setLatency(i, j, timeFrame);
						}
					}
				}
			}
			for(int i = 0; i < NODENUM; i++){
				onNeighbor[i] = 0;
			}
		}
		for(int i = 0; i < NODENUM; i++){
			for(int j = 0; j < NODENUM; j++){
				f<<latency[i][j]<<",";
			}
			f<<endl;
		}
		initLatency();
	}
	
}


void energy_1(int timeInterval, int arrayLength)
{
	int onNeighbor[NODENUM];

	stringstream ss;
	ss << "hedis/thousand_times_latency_energy1.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);


	initLatency();
	for(int i = 0; i < NODENUM; i++){
		warray[i].reset();
		onNeighbor[i] = 0;
	}

	
	for(int k = 0; k < arrayLength; k++){
		for(int timeFrame = 1; timeFrame <= timeInterval; timeFrame++){
			for(int i = 0; i < NODENUM; i++){
				warray[i].endTime++;
				if(warray[i].hedis_isOff(timeFrame) == false){
					warray[i].energy -= pn; 
					for(int j = 0; j < NODENUM; j++){
						if(warray[j].hedis_isOff(timeFrame) == false && neighborMap[i][j] == 1){
							onNeighbor[j]++;
						}
					}
				}
			}

			for(int i = 0; i < NODENUM; i++){
				if(onNeighbor[i] == 1 && warray[i].hedis_isOff(timeFrame) == false){
					for(int j = 0; j < NODENUM; j++){
						if(neighborMap[i][j] == 1 && onNeighbor[j] == 1 && warray[j].hedis_isOff(timeFrame) ==false && latency[i][j] == MAX_INT){
							setLatency(i, j, timeFrame);
						}
					}
				}
			}
			for(int i = 0; i < NODENUM; i++){
				onNeighbor[i] = 0;
			}
		}
		
		for(int i = 0; i < NODENUM; i++){
			warray[i].energySupply1(theta0);
		}
		for(int i = 0; i < NODENUM; i++){
			for(int j = 0; j < NODENUM; j++){
				f<<latency[i][j]<<",";
			}
			f<<endl;
		}
		initLatency();
	}
	
	
}

void energy_2(int timeInterval, int arrayLength)
{
	int onNeighbor[NODENUM];

	stringstream ss;
	ss << "hedis/thousand_times_latency_energy2.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);


	initLatency();
	for(int i = 0; i < NODENUM; i++){
		warray[i].reset();
		warray[i].setTheta(theta0);
	}
    initEnergySupply2(theta0);

    for(int i = 0; i < NODENUM; i++){
		onNeighbor[i] = 0;

	} 
	for(int k = 0; k < arrayLength; k++){
		for(int timeFrame = 1; timeFrame <= timeInterval; timeFrame++){
			for(int i = 0; i < NODENUM; i++){
				warray[i].endTime++;
				if(warray[i].hedis_isOff(timeFrame) == false){
					warray[i].energy -= pn;
					for(int j = 0; j < NODENUM; j++){
						if(warray[j].hedis_isOff(timeFrame) == false && neighborMap[i][j] == 1){
							onNeighbor[j]++;
						}
					}
				}
			}

			for(int i = 0; i < NODENUM; i++){
				if(onNeighbor[i] == 1 && warray[i].hedis_isOff(timeFrame) == false){
					for(int j = 0; j < NODENUM; j++){
						if(neighborMap[i][j] == 1 && onNeighbor[j] == 1 && warray[j].hedis_isOff(timeFrame) ==false && latency[i][j] == MAX_INT){
							setLatency(i, j, timeFrame);
						}
					}
				}
			}
			for(int i = 0; i < NODENUM; i++){
				onNeighbor[i] = 0;
			}
		}
		
		for(int i = 0; i < NODENUM; i++){
			warray[i].energySupply2();
		}
		for(int i = 0; i < NODENUM; i++){
			for(int j = 0; j < NODENUM; j++){
				f<<latency[i][j]<<",";
			}
			f<<endl;
		}
		initLatency();
	} 
	
}

int main (int argc, char *argv[])
{
	srand(time(NULL));

	findAllPrimes(10000);
	initMap();

	noModCollision2(100000, 20);
	energy_1(100000, 20); 
	energy_2(100000, 20); 
//	noModCollisionAdjust(100000);
	return 0;
}
