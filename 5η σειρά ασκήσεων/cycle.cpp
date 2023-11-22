#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
public:
    
    Graph(int numNodes) : numNodes(numNodes), graph(numNodes), visited(numNodes, 0), recStack(numNodes, 0) {}

    ~Graph(){};

    void addEdge(int u, int v) {
        graph[v].push_back(u);
    }

    bool cycle(vector<int> &path) {
        for (int node = 0; node < numNodes; ++node) {
            if (visited[node] == 0 && containsCycleUtil(node, path)) {
                if(find(path.begin(), path.end(), node) == path.end()) path.push_back(node);
                return true;
            }
        }

        return false;
    }

private:
    int numNodes;
    vector<vector<int>> graph;
    vector<int> visited;
    vector<int> recStack;

    bool containsCycleUtil(int node, vector<int> &cycle) {
        visited[node] = 1;
        recStack[node] = 1;

        for (int neighbor : graph[node]) {
            if (visited[neighbor] == 0) {
                if (containsCycleUtil(neighbor, cycle)) {
                    if(find(cycle.begin(), cycle.end(),neighbor) == cycle.end()) cycle.push_back(neighbor);
                    return true;
                }
            } else if (recStack[neighbor] == 1) {
                if(find(cycle.begin(), cycle.end(),neighbor) == cycle.end()) cycle.push_back(neighbor);
                return true;
            }
        }

        recStack[node] = 0;
        return false;
    }
};

/*
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
*/
