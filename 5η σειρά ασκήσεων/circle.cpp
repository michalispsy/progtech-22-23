#include <iostream>
#include <list>
#include <vector>
#include <algorithm> 
using namespace std;

class Graph{
  private:
    int numv; 
    list<int> *ptr;
    vector<int> a;
    vector<int> root;
    int start, end;

    bool DFS(int v) {
        
        a[v]=1;
        for(int u: ptr[v]){
        if(a[u] == 0) {
            root[u] = v;
            if(DFS(u))
            return true;
        }
        else if(a[u]==1) {
            end=v;
            start=u;
            return true;
        }
        } 
        a[v]=2;
        return false;
    }

    bool print_path(vector<int> &cycle)
    {
      vector<int> reverse_cycle;
      reverse_cycle.push_back(start);
      for( int v=end; v!=start; v=root[v]) reverse_cycle.push_back(v);
      
      while(!reverse_cycle.empty())
      {
        cycle.push_back(reverse_cycle.back());
        reverse_cycle.pop_back();
      }
      return true;
    }
  
  public:

  Graph(int V): numv(V) { ptr=new list<int>[numv]; }

  ~Graph() { delete [] ptr;}

  void addEdge (int u, int v) {
    ptr[u].push_back(v);
  }

  bool cycle(vector<int> &cycle) {
    //root.assign(numv, -10);
    a.assign(numv, 0);
    root.assign(numv, -1);
    start=-1;

    for(int v=0; v<numv; v++) {
      if(a[v]==0 && DFS(v))
      break;
    }

    if(start==-1)return false;
    return print_path(cycle);
  }
};

#ifndef CONTEST
int main() {
    int V, E;
    cin >> V >> E;
    Graph g(V);
    for (int i = 0; i < E; ++i) { int u, v; cin >> u >> v; g.addEdge(u, v); }
    vector<int> path;
    bool c = g.cycle(path); 
    if (c) {
        cout << "CYCLE: ";
        for (int i = 0; i < path.size(); ++i)
        cout << path[i] << (i == path.size()-1 ? "\n" : " ");
    } else {
        cout << "NO CYCLE" << endl;
    }
}
#endif