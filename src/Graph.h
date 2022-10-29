#include<iostream>
#include <list>
#include <stack>
#include <cstdlib> //use rand()
#define UNVISITED false
#define VISITED true
#define UNSTACKED false
#define STACKED true
#define NONE -1
using namespace std;

class Graph{
    int V;
    list<int>* adj;
    public:
    //Headers related to Graph itself
    Graph(int V);
    void addEdge(int v,int w);

    //Customize cout to print the graph
    friend auto operator<<(std::ostream& os, Graph const& g) -> std::ostream&;
    friend Graph generateRandomGraph(int nbV,int nbE);
    //Headers related to Kosaraju's Algorithm
  
    void sortOnTime(int v, stack<int> &stk, bool visited[]);//Sorting all vertices in term of finishing time O(V)
    Graph getTranspose(); //reverse the direction of all edges ex. 0->1 become 1->0 O(V+E)
    void dfs_for_kosaraju(int v,bool visited[]);//DFS according to the finishing time O(V+E)
    void findSCC_Kosaraju();

    //Headers related to Tarjan
    void dfs_for_tarjan(int u,int num,int dfsnum[],int lowLink[],bool visited[],stack<int> &stk);
    void findSCC_Tarjan();

    };

Graph::Graph(int V){
    this->V=V;
    this->adj=new list<int>[V];
}

void Graph::addEdge(int v,int w){
    if(v!=w) this->adj[v].push_back(w);
}


std::ostream& operator<<(std::ostream& os, Graph const& g) { 
    string str="";
    for (int v = 0; v < g.V; v++) {
        str+=to_string(v);
        list<int>::iterator i;
        for (i = g.adj[v].begin();i != g.adj[v].end(); ++i){
                 str+=" -> "+to_string(*i);
        }
        str+="\n";
    }
    return os<<str;
}

//Kosaraju's Algorithm Below:
void Graph::sortOnTime(int v, stack<int> &stk, bool visited[]){
    visited[v]=VISITED;

    list<int>::iterator itr;
    for(itr=this->adj[v].begin();itr!=this->adj[v].end();itr++){
        if(!visited[*itr]) sortOnTime(*itr,stk,visited);
    }
    stk.push(v);
};

Graph Graph::getTranspose(){
    Graph gT(this->V);
    for(int v=0;v<this->V;v++){
        list<int>::iterator itr;
        for(itr=this->adj[v].begin();itr!=this->adj[v].end();itr++){
           gT.adj[*itr].push_back(v);
        }
    }
    return gT;
}

void Graph::dfs_for_kosaraju(int v,bool visited[]){
    visited[v]=VISITED;
    cout<<v<<" ";
    list<int>::iterator itr;
    for(itr=this->adj[v].begin();itr!=this->adj[v].end();itr++){
        if(!visited[*itr]) dfs_for_kosaraju(*itr,visited);
    }  
}

void Graph::findSCC_Kosaraju(){
    stack<int> stk;
    bool *visited=new bool[this->V];

    for (int i=0;i<this->V;i++) visited[i]=UNVISITED;
    
    for(int v=0;v<this->V;v++) if(!visited[v]) sortOnTime(v,stk,visited);

    Graph gT=this->getTranspose();

    for (int i=0;i<this->V;i++) visited[i]=UNVISITED;

    while(!stk.empty()){
      int V=stk.top();
      stk.pop();
      if(!visited[V]) {gT.dfs_for_kosaraju(V,visited);
       cout<<endl;
       }
    }
}

//Tarjan's Algorithm Below:
void Graph::dfs_for_tarjan(int v,int num,int dfsnum[],int lowLink[],bool inStack[],stack<int> &stk){
 
    dfsnum[v]=lowLink[v]=++num;
    inStack[v]=STACKED;
    stk.push(v);

    list<int>::iterator itr;
    for (itr=this->adj[v].begin();itr!=this->adj[v].end();itr++){
        int u=*itr;
        if(dfsnum[u]==NONE){ // or visted[u]==UNVISITED
            dfs_for_tarjan(u,num,dfsnum,lowLink,inStack,stk);
            lowLink[v]=lowLink[v]>lowLink[u]? lowLink[u]:lowLink[v];
        }
        else if(inStack[u])  lowLink[v]=lowLink[v]>dfsnum[u]? dfsnum[u]:lowLink[v];
    }

    int x;

	if (dfsnum[v]==lowLink[v]) {
		// Until stack st is empty
		while (stk.top() != v) {
			x = (int)stk.top();
            stk.pop();
			// Print the node
			cout << x << " ";
			inStack[x] = UNSTACKED;
		}
		x = (int)stk.top();
        stk.pop();
		cout << x << "\n";
		inStack[x] = UNSTACKED;
	}

}

 void Graph::findSCC_Tarjan(){
     int* dfsnum=new int[this->V];
     int* lowLink=new int[this->V];
     bool* inStack=new bool[this->V];

     stack<int> stk;

     for (int i=0;i<this->V;i++){
         dfsnum[i]=NONE;
         lowLink[i]=NONE;
         inStack[i]=UNSTACKED;
     }
     
     for (int i=0;i<this->V;i++){
         int num=0;
         if (dfsnum[i]==NONE) dfs_for_tarjan(i,num,dfsnum,lowLink,inStack,stk);
     }

 };

Graph generateRandomGraph(int nbV,int nbE){
    Graph g(nbV);
    int i=nbE,x=0,y=0;
    while(i>0){
        int d=rand()%nbE;
        list<int>::iterator itr;
        int k=0;
        
        while( k<d ){
            x=0;
        y=0;
            while(x==y){
            x=rand()%nbV;
            y=rand()%nbV;
            // cout<<x<<"-"<<y<<"."<<endl;
            if(!g.adj[x].empty()){
            for (itr=g.adj[x].begin();itr!=g.adj[x].end();itr++){
                // cout<<*itr<<endl;
                if(*itr==y) {y=x;break;}
            }}
            }
        k++;
        g.addEdge(x,y);
        }  
        i-=d;
    
    }
    return g;
}