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
#define INF    (~(0x1<<31))
const int STARTRANGE = 1000;
const int SCOPE = 100;
const int Pmax = 100000;
const int Pmin = 200;
const int pn = 1;
const int pc = 0.5;
const int CYCLENUM = 20;
const int T = 100000;
const int m = 30;
const int dc = 80;
const int NODENUM=100;
const int theta0 = 0.3;
const int RATE = 100;

int latency[NODENUM][NODENUM];
double neighborMap[NODENUM][NODENUM];
std::vector<int> primeset;
int P[m];
double the[m];


void Dijkstra(int vs, int prev[], int dist[])
{
    int i,j,k;
    int min;
    int tmp;
    int flag[NODENUM];      
    
    for (i = 0; i < NODENUM; i++)
    {
        flag[i] = 0;              
        prev[i] = 0;             
        dist[i] = (latency[vs][i] == INF) ? INF : 1;
    }

    flag[vs] = 1;
    dist[vs] = 0;

    for (i = 1; i < NODENUM; i++)
    {
        min = INF;
        for (j = 0; j < NODENUM; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        flag[k] = 1;

        for (j = 0; j < NODENUM; j++)
        {
            tmp = (latency[k][j]==INF ? INF : (min + 1));
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

  
}


int main (int argc, char *argv[])
{
	srand(time(NULL));

//	findAllPrimes(10000);
//	initMap();

//	noModCollision2(10000, 1);
//	energy_1(100000, 20); 
//	energy_2(100000, 20); 
//	noModCollisionAdjust(100000);
	for(int i=0; i<NODENUM; i++){
	 	for(int j = 0; j<NODENUM;j++){
	 		latency[i][j]=INF;
		 }
	}
	int mom=0;
	int son=0;
//	for(int i = 0; i < NODENUM; i++){
//		int prev[NODENUM] = {0};
//		int dist[NODENUM] = {0};
//		Dijkstra(i, prev, dist);
//		for(int j = 0; j < NODENUM; j++){
//			if(dist[j] != INF){
//				son++;
//				mom+=dist[i];
//				if(mom!=0)  cout<<"mom:"<<i<<","<<son<<","<<mom<<endl;
//				
//			}
//		}
////				}
//		
//	}
	latency[10][11]=5;
	latency[11][12]=6;
	int prev[NODENUM] = {0};
	int dist[NODENUM] = {0};
	Dijkstra(10,prev,dist);
	for(int j = 0; j < NODENUM; j++){
		if(dist[j] != INF){
			son++;
			mom+=dist[j];
			if(mom!=0)  cout<<"mom:"<<i<<","<<son<<","<<mom<<endl;
			
		}
	}
	cout<<son<<","<<mom;
	return 0;
}

