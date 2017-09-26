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
const int pe = 0.5;
const int MAX_INT = -1;
const int CYCLENUM = 20;
const int T = 100000;
const int m = 30;
const int dc = 50;
const double PROB = 0.1;
const int TIMES = 55;
const int NODENUM = 5;

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
	void resetStartTime(){
		startTime = rand()%(STARTRANGE+1);
	}
	
	//Energy Module Algorithm 1
	void energySupply1(double theta0){
		theta = theta0 / Pmax * this->energy;
		hedis_generate_anchor();
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
		hedis_init_output();
	}
	
	void hedis_init_output(){
		stringstream ss;
    	ss << "hedis1/Prime_Time_pset.txt";
    	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
    	f << "Node " << ID << ", start at "<<startTime<<", anchor: " << anchor <<std::endl;
	}
	
	bool hedis_isOff(int time){
		if( time - startTime > 0){	
      		if ( (time - startTime) % this->anchor == 0 || (time - startTime - 1) % ( anchor + 1 ) == 0 ){
          		return false;
          		
      		}
    	}
    	return true;
	}
	
};

wifiContainer w[NODENUM];

void initEnergySupply2(double theta0){
	stringstream ss;
	ss << "hedis1/energy_theta_table.txt";
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


//double dutycycle[TIMES];
//double percent[TIMES];
//int late[TIMES];

void energy_0(int timeInterval)
{
	int findNeighborTime[NODENUM];
	int find[NODENUM];
	int onNeighbor = 0;
	double theta0 = 0.3;
	int flag = true;
	int count = 0;
//	double dutycycle[TIMES];
//	double percent[TIMES];
//	int late[TIMES];
	int bound = 0;
	int a;
	
	for(int i = 0; i < NODENUM; i++){
		wifiContainer tempw(i);
		w[i] = tempw;
		findNeighborTime[i] = 0;
		find[i] = 0;
	}
	
	
	
	stringstream ss,s1;
	ss << "hedis1/energy_notchange.txt";
	s1<<"hedis1/lifetime.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	fstream fs (s1.str().c_str(), std::ios::out | std::ios::app);
	
	w[0].setTheta(theta0);
	w[0].resetStartTime();
	w[0].endTime = w[0].startTime;
	
	for(int k=0; k < TIMES && w[0].alive == true; k++){
		bound = k;
		for(int timeFrame=0; timeFrame <= timeInterval && w[0].alive == true; timeFrame ++){
			w[0].endTime ++;
			for(int e = 1; e < NODENUM; e++){
				if(find[e] == 1){
					w[0].energy -= pe;
					count++; 
				}
			}
			if(w[0].hedis_isOff(timeFrame) == false && w[0].alive == true){
				w[0].energy -= pn;
				
				if(w[0].energy <= 0 && flag == true){
					w[0].alive = false;
					flag = false;
					cout<<"+++++++++++++++++++++++++++++++++++++++++++"<<endl;
					break;
				}
				for(int j = 1; j < NODENUM; j++){
					if(w[j].hedis_isOff(timeFrame) == false && w[j].alive == true){
						onNeighbor++;
					}
				}
				if(onNeighbor == 1){
					for(int j = 1; j < NODENUM; j++){
						if(w[j].hedis_isOff(timeFrame) == false && findNeighborTime[j] == 0 && w[j].alive == true){
							findNeighborTime[j] = timeFrame;
							find[j] = 1;
						}
					}
				}
			}
//			f<<k<<","<<timeFrame<<","<<count<<endl;
			f<<count<<endl;
			onNeighbor = 0;
			count=0;
			a=timeFrame;
		}

		for(int l = 1; l < NODENUM; l++){
			findNeighborTime[l] = 0;
		}
		
	}
//	f<<bound<<","<<a<<",0"<<endl;
	f<<"0"<<endl;
	cout<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
	fs<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
	
}


void energy_1(int timeInterval)
{
	
	int findNeighborTime[NODENUM];
	int find[NODENUM];
	int onNeighbor = 0;
	double theta0 = 0.3;
	int flag = true;
	int count = 0;
	int bound = 0;
	
	for(int i = 0; i < NODENUM; i++){
		wifiContainer tempw(i);
		w[i] = tempw;
		findNeighborTime[i] = 0;
		find[i] = 0;
	}
	
	
	stringstream ss,s1;
	ss << "hedis1/energy1.txt";
	s1<<"hedis1/lifetime.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	fstream fs (s1.str().c_str(), std::ios::out | std::ios::app);
	
	w[0].setTheta(theta0);
	w[0].resetStartTime();
	
	
	for(int k = 0; k < TIMES && w[0].alive == true; k++){
		bound = k;
		for(int timeFrame = w[0].startTime; timeFrame <= timeInterval && w[0].alive == true; timeFrame ++){
			w[0].endTime ++;
			for(int e = 1; e < NODENUM; e++){
				if(find[e] == 1){
					w[0].energy -= pe;
					count++;
				}
			}
			if(w[0].hedis_isOff(timeFrame) == false  && w[0].alive == true){
				w[0].energy -= pn;
				if(w[0].energy <= 0 && flag == true){
					w[0].alive = false;
//					w[0].endTime = k * timeInterval + timeFrame;
					flag = false;
					cout<<"+++++++++++++++++++++++++++++++++++++++++++"<<endl;
					break;
				}
				for(int j = 1; j < NODENUM; j++){
					if(w[j].hedis_isOff(timeFrame) == false && w[j].alive == true){
						onNeighbor++;
					}
				}
				if(onNeighbor == 1){
					for(int j = 1; j < NODENUM; j++){
						if(w[j].hedis_isOff(timeFrame) == false && findNeighborTime[j] == 0 && w[j].alive == true){
							findNeighborTime[j] = timeFrame;
							find[j] = 1;
						}
					}
				}
			}
			f<<count<<endl;
			count=0;
			onNeighbor = 0;
		}
		
		w[0].energySupply1(theta0);
		
		for(int l = 1; l < NODENUM; l++){
			findNeighborTime[l] = 0;
		}
		
	}
	f<<"0"<<endl;
	cout<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
	fs<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
}

void energy_2(int timeInterval)
{
	
	int findNeighborTime[NODENUM];
	int find[NODENUM];
	int onNeighbor = 0;
	int count = 0;
	double theta0 = 0.3;
	int flag = true;
	
	int bound = 0;
	
	for(int i = 0; i < NODENUM; i++){
		wifiContainer tempw(i);
		w[i] = tempw;
		findNeighborTime[i] = 0;
		find[i] = 0;
	}
	
	
	initEnergySupply2(theta0); 
	
	stringstream ss, s1;
	ss << "hedis1/energy2.txt";
	s1<<"hedis1/lifetime.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	fstream fs (s1.str().c_str(), std::ios::out | std::ios::app);
//	f<<"*********************************************************************"<<endl;
	
	w[0].setTheta(theta0);
	w[0].resetStartTime();
	
	
	for(int k = 0; k < TIMES && w[0].alive == true; k++){
		bound = k;
		for(int timeFrame = w[0].startTime; timeFrame <= timeInterval && w[0].alive == true; timeFrame ++){
			w[0].endTime ++;
			for(int e = 1; e < NODENUM; e++){
				if(find[e] == 1){
					w[0].energy -= pe;
					count++; 
				}
			}
			if(w[0].hedis_isOff(timeFrame) == false  && w[0].alive == true){
				w[0].energy -= pn;
				if(w[0].energy <= 0 && flag == true){
					w[0].alive = false;
					flag = false;
					cout<<"+++++++++++++++++++++++++++++++++++++++++++"<<endl;
					break;
				}
				for(int j = 1; j < NODENUM; j++){
					if(w[j].hedis_isOff(timeFrame) == false && w[j].alive == true){
						onNeighbor++;
					}
				}
				if(onNeighbor == 1){
					for(int j = 1; j < NODENUM; j++){
						if(w[j].hedis_isOff(timeFrame) == false && findNeighborTime[j] == 0 && w[j].alive == true){
							findNeighborTime[j] = timeFrame;
							find[j] = 1;
						}
					}
				}
			}
			f<<count<<endl;
			count=0;
			onNeighbor = 0;
		}
		
		w[0].energySupply2();
	
		for(int l = 1; l < NODENUM; l++){
			findNeighborTime[l] = 0;
		}
		
	}
	f<<"0"<<endl;
	cout<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
	fs<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
//	f<<"*********************************************************************"<<endl;
}
/*
void multi0(){
	stringstream ss;
	ss << "hedis1/ave_energy0.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	int HOW = 20;
//	double a[Times],b[TIMES],c[TIMES];
	
	for(int k = 0; k < TIMES; k++){
		dutycycle[k] = 0;
		percent[k] = 0;
		late[k] = 0;
	}
	
	for(int k = 0; k < HOW; k++){
		energy_0(100000);
		
	}
	for(int k = 0; k < 20; k++){
		cout<<"k="<<k<<" "<<dutycycle[k]/HOW<<","<<percent[k]/HOW<<","<<late[k]/HOW<<endl;
		f<<dutycycle[k]/HOW<<","<<percent[k]/HOW<<","<<late[k]/HOW<<endl;
		
	}
	cout<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
	f<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
	f<<"*********************************************************************"<<endl;
}
/*
void multi1(){
	stringstream ss;
	ss << "hedis1/ave_energy1.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	int HOW = 20;
//	double a[Times],b[TIMES],c[TIMES];
	
	for(int k = 0; k < TIMES; k++){
		dutycycle[k] = 0;
		percent[k] = 0;
		late[k] = 0;
	}
	
	for(int k = 0; k < HOW; k++){
		energy_1(100000);
		
	}
	for(int k = 0; k < 20; k++){
		cout<<"k="<<k<<" "<<dutycycle[k]/HOW<<","<<percent[k]/HOW<<","<<late[k]/HOW<<endl;
		f<<dutycycle[k]/HOW<<","<<percent[k]/HOW<<","<<late[k]/HOW<<endl;
		
	}
	cout<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
	f<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
	f<<"*********************************************************************"<<endl;
} 

void multi2(){
	stringstream ss;
	ss << "hedis1/ave_energy2.txt";
	fstream f (ss.str().c_str(), std::ios::out | std::ios::app);
	int HOW = 20;
//	double a[Times],b[TIMES],c[TIMES];
	
	for(int k = 0; k < TIMES; k++){
		dutycycle[k] = 0;
		percent[k] = 0;
		late[k] = 0;
	}
	
	for(int k = 0; k < HOW; k++){
		energy_2(100000);
		
	}
	for(int k = 0; k < 20; k++){
		cout<<"k="<<k<<" "<<dutycycle[k]/HOW<<","<<percent[k]/HOW<<","<<late[k]/HOW<<endl;
		f<<dutycycle[k]/HOW<<","<<percent[k]/HOW<<","<<late[k]/HOW<<endl;
		
	}
	cout<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
	f<<"life Cycle = "<<w[0].endTime - w[0].startTime<<endl;
	f<<"*********************************************************************"<<endl;
} 
*/
int main (int argc, char *argv[])
{
	srand(time(NULL));
	
	findAllPrimes(10000);

//  	energy_notchange(100000);
//	energy_1(100000);
//	energy_2(100000);
//	multi0();
//	multi1();
//	multi2();
	energy_0(100000);
	energy_1(100000);
	energy_2(100000);
	return 0;
}
