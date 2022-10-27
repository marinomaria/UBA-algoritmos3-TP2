#include <iostream>
#include <vector>

using namespace std;
int R, C, Q;
vector<vector<int>> adjacent;
vector<int> nodeComponent;

void dfsTimerParent(const vector<vector<int>> &adj, const int source,
                    int &currentTime, vector<int> &timeIn, vector<int> &color, vector<int> &parent) {
    color[source] = 1;
    timeIn[source] = currentTime++;
    for (int u : adj[source]) {
        if (color[u] == 0) {
            parent[u] = source;
            dfsTimerParent(adj, u, currentTime, timeIn, color, parent);
        }
    }
    color[source] = 2;
}

int bridgeDetection(const vector<vector<int>> &adj, int source, const vector<int> &timeIn,
                     const vector<int> &parents, vector<vector<int>> &bridges) {
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

void connectedComponents(vector<vector<int>> &adj, vector<int> &parents, vector<int> &cc) {
    int currentComponent = 0;
    for (int i = 1; i < R + 1; i++) {
        if (parents[i] == -1) {
            parents[i] = i;
            cc[i] = currentComponent;
            int startTime = 0; vector<int> timeIn(R + 1, -1); vector<int> color(R + 1, 0);
            dfsTimerParent(adj, 1, startTime, timeIn, color, parents);
            currentComponent++;
        }
    }

    for (int i = 1; i < R + 1; i++) {
        if (cc[i] == -1) {
            int u = i;
            while (parents[u] != u) {
                u = parents[u];
            }
            cc[i] = cc[u];
        }
    }
}

void processHedgeMaze(vector<int> &component) {
    vector<int> nodeTimeIn(R + 1, 0);
    vector<int> nodeColor(R + 1, 0);
    vector<int> nodeParent(R + 1, -1);
    nodeParent[1] = 1;
    int currentTime = 0;
    dfsTimerParent(adjacent, 1, currentTime, nodeTimeIn, nodeColor, nodeParent);

    vector<vector<int>> bridges(R + 1, vector<int>());
    bridgeDetection(adjacent, 1, nodeTimeIn, nodeParent, bridges);

    nodeParent = vector<int>(R + 1, -1);
    connectedComponents(bridges, nodeParent, component);
}

int main() {
    while(cin >> R >> C >> Q && (R != 0 or C != 0 or Q != 0)) {
        adjacent = vector<vector<int>>(R + 1, vector<int>());
        for (int i = 0; i < C; i++) {
            int u;
            int v;
            cin >> u >> v;
            adjacent[u].push_back(v);
            adjacent[v].push_back(u);
        }

        nodeComponent = vector<int>(R + 1, -1);
        processHedgeMaze(nodeComponent);

        for (int i = 0; i < Q; i++) {
            int s;
            int t;
            cin >> s >> t;
            cout << ((nodeComponent[s] == nodeComponent[t]) ? 'Y' : 'N') << endl;
        }

        cout << '-' << endl;
    }
    return 0;
}