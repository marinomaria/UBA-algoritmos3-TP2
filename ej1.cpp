#include <iostream>
#include <vector>

using namespace std;

using Graph = vector<vector<int>>;

struct dfsOutput{
    vector<int> connectedComponents;
    Graph bridges;
};

int R, C, Q;

void dfsComponent(const Graph &adj, int source, int c, int &currentTime, vector<int> &timeIn, vector<int> &color, vector<int> &parent) {
    color[source] = c;
    timeIn[source] = currentTime++;

    for (int u : adj[source]) {
        if (color[u] == 0) {
            parent[u] = source;
            color[u] = c;
            dfsComponent(adj, u, c, currentTime, timeIn, color, parent);
        }
    }
}

int bridgeDetection(const Graph &adj, int source, const vector<int> &timeIn, const vector<int> &parents, Graph &bridges) {
    int count = 0;
    for (int u : adj[source]) {
        if (parents[u] == source) {
            count += bridgeDetection(adj, u, timeIn, parents, bridges);
        } else {
            // (source, u) is a back-edge going up
            if (timeIn[source] > timeIn[u] and parents[source] != u) {
                count++;
            }
            // (source, u) is a back-edge ending in source
            if (timeIn[source] < timeIn[u]) {
                count--;
            }
        }
    }
    if (count == 0 and parents[source] != source) {
        // (parents[source], source) is a bridge edge
        bridges[parents[source]].push_back(source);
        bridges[source].push_back(parents[source]);
    }
    return count;
}

dfsOutput dfsGraph(Graph& G) {
    vector<int> nodeTimeIn(R + 1, 0);
    vector<int> nodeColor(R + 1, 0);
    vector<int> nodeParent(R + 1, -1);
    Graph bridges(R + 1);
    int currentTime = 0;
    for (int i = 1; i <= R; i++) {
        if (nodeParent[i] == -1) {
            nodeParent[i] = i;
            dfsComponent(G, i, i, currentTime, nodeTimeIn, nodeColor, nodeParent);
            bridgeDetection(G, i, nodeTimeIn, nodeParent, bridges);
        }
    }

    return {nodeColor, bridges};
}

vector<int> processHedgeMaze(Graph& G) {
    Graph bridges = dfsGraph(G).bridges;
    vector<int> nodeComponent = dfsGraph(bridges).connectedComponents;

    return nodeComponent;
}

int main() {
    while(cin >> R >> C >> Q && (R != 0 or C != 0 or Q != 0)) {
        Graph adjacent = Graph(R + 1);
        for (int i = 0; i < C; i++) {
            int u, v;
            cin >> u >> v;
            adjacent[u].push_back(v);
            adjacent[v].push_back(u);
        }

        vector<int> component = processHedgeMaze(adjacent);

        for (int i = 0; i < Q; i++) {
            int s, t;
            cin >> s >> t;
            cout << ((component[s] == component[t]) ? 'Y' : 'N') << endl;
        }

        cout << '-' << endl;
    }
    return 0;
}