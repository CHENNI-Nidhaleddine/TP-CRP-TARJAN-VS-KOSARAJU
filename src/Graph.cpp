#include "Graph.h"

// Note: when using time calculation 
// we have to remove cout instructions in both algorithms
// the cout intructions are in lines 94, 117, 146, 151 in graph.h


#define N 6
int main(int argc, char** argv)
{
 
    int nbV=5000;
    int nbE=1000;
    if(nbE>nbV*(nbV-1)) return EXIT_FAILURE;

    cout<<"Creation of "<<N<<" random graphs of same size ("<<nbV<<","<<nbE<<"):"<<endl;
    Graph gs[N];
    for(int i=0;i<N;++i){
        gs[i]=generateRandomGraph(nbV,nbE);
        // cout<<gs[i]<<endl;
    }

    cout<<"Applying Kosarju on the generated graphs"<<endl;
    auto start = chrono::high_resolution_clock::now();
    //Apply Kosaraju on N generated graphs
    for(int i=0;i<N;++i){
        gs[i].findSCC_Kosaraju();
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout <<"Duration:"<<(double)(duration.count()/N)<<" us"<<endl<<endl;
    
    cout<<"Applying Tarjan on the generated graphs"<<endl;
    auto start1 = chrono::high_resolution_clock::now();
    //Apply Tarjan on N generated graphs
    for(int i=0;i<N;++i){
        gs[i].findSCC_Tarjan();
    }
    auto stop1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(stop1 - start1);
    cout <<"Duration:"<<(double)(duration1.count()/N)<<" us"<< endl;
    
    return EXIT_SUCCESS; 
}