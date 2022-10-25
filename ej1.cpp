#include <iostream>
#include <vector>

using namespace std;
using query = pair<int, int>;
int R, C, Q;
vector<vector<int>> adjacent;
vector<query> queries;

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

void bridgeDetection(const vector<vector<int>> &adj, int source, const vector<int> &timeIn,
                     const vector<int> &parents, const vector<bool> &bridgeWithParent) {
    for (int u : adj[source]) {
        if (parents[u] == source) {
            bridgeDetection(adj, u, timeIn, parents, bridgeWithParent);
        } else {
            if (timeIn[source] > timeIn[u] && parents[source] != u) {
                // TODO
            }
        }
    }
}

bool hedgeMazeSolver() {
    vector<int> nodeTimeIn(R);
    vector<int> nodeColor(R);
    vector<int> nodeParent(R);
    int currentTime = 0;
    dfsTimerParent(adjacent, 0, currentTime, nodeTimeIn, nodeColor, nodeParent);
    // TODO
    return true;
}

int main() {
    while(cin >> R >> C >> Q) {
        queries = vector<query>(Q, make_pair(0,0));
        adjacent = vector<vector<int>>(R);
        for (int i = 0; i < C; i++) {
            int u;
            int v;
            cin >> u >> v;
            adjacent[u].push_back(v);
            adjacent[v].push_back(u);
        }
        for (int i = 0; i < Q; i++) {
            int s;
            int t;
            cin >> s >> t;
            queries[i].first = s;
            queries[i].second = t;
        }

        cout << hedgeMazeSolver() << endl;
    }
    return 0;
}