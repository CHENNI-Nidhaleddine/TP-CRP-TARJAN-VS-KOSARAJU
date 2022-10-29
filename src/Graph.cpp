#include<iostream>
#include <list>
#include <stack>
#include <chrono>
#include "Graph.h"
using namespace std;

// Note: when using time calculation 
// we have to remove cout instructions in both algorithms
int main()
{
 
   
    int nbV=10000;
    int nbE=10000;
    Graph g1=generateRandomGraph(nbV,nbE);
    Graph g2=generateRandomGraph(nbV,nbE);
    Graph g3=generateRandomGraph(nbV,nbE);
    Graph g4=generateRandomGraph(nbV,nbE);
    Graph g5=generateRandomGraph(nbV,nbE);
    Graph g6=generateRandomGraph(nbV,nbE);
   
    auto start = chrono::high_resolution_clock::now();
    g1.findSCC_Kosaraju();
    g2.findSCC_Kosaraju();
    g3.findSCC_Kosaraju();
    g4.findSCC_Kosaraju();
    g5.findSCC_Kosaraju();
    g6.findSCC_Kosaraju();
    cout<<(double)(sizeof(int)*(2*nbV+nbE*nbV))/(1024*1024) <<endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << (double)(duration.count()/6) << endl;


    auto start1 = chrono::high_resolution_clock::now();
    g1.findSCC_Tarjan();
    g2.findSCC_Tarjan();
    g3.findSCC_Tarjan();
    g4.findSCC_Tarjan();
    g5.findSCC_Tarjan();
    g6.findSCC_Tarjan();
    auto stop1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(stop1 - start1);
    cout << (double)(duration1.count()/6) << endl;
    
     
}