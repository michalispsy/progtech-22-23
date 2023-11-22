#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Graph {
public:
    Graph(int numNodes) : numNodes(numNodes), graph(numNodes) {}

    void addEdge(int source, int destination) {
        if (source >= 0 && source < numNodes && destination >= 0 && destination < numNodes) {
            graph[source].push_back(destination);
        }
    }

    bool cycle(vector<int>& cycle) {
        for (int node = 0; node < numNodes; ++node) {
            vector<int> currentPath;
            unordered_set<int> visited;

            if (dfs(node, currentPath, visited)) {
                cycle = currentPath;
                return true;
            }
        }

        return false;
    }

private:
    int numNodes;
    vector<vector<int>> graph;

    bool dfs(int node, vector<int>& currentPath, unordered_set<int>& visited) {
        visited.insert(node);
        currentPath.push_back(node);

        for (int neighbor : graph[node]) {
            if (visited.count(neighbor) == 0) {
                if (dfs(neighbor, currentPath, visited)) {
                    return true;
                }
            } else {
                // Cycle detected
                if (visited.size() - visited.count(neighbor) > 1) {
                    return true;
                }
            }
        }

        visited.erase(node);
        currentPath.pop_back();
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
}*/