#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int to;
    int weight;
};

using Graph = vector<vector<edge>>;

#define INF numeric_limits<int>::max()
int T, C, P;

int dijkstra(const Graph &adj, int source, int target) {
    struct node {
        int n;
        int dist;

    };
    bool operator>(const node &u, const node &v) {
        return u.dist > v.dist;
    }

    vector<int> nodeDistance(adj.size(), INF);
    nodeDistance[source] = 0;
    priority_queue<node, vector<node>> Q(nodeDistance.begin(), nodeDistance.end());

    while (!Q.empty()) {
        int u = Q.top();
        Q.pop();
        for (edge e : adj[u]) {
            int v = e.to;
            if (nodeDistance[v] > nodeDistance[u] + e.weight) {
                nodeDistance[v] = nodeDistance[u] + e.weight;
            }
        }
    }

    return nodeDistance[target];
}

int solveUsher(const Graph &G, int &boxCapacity) {

    int n = dijkstra(G, 0, G.size() - 1);

    return boxCapacity / (n - 1);
}

int main() {
    cin >> T;
    for(int i = 0; i < T; i++) {
        cin >> C >> P;
        // node 0 is the light usher, node P + 1 is the shadow usher
        Graph G(P + 2);
        int q;
        cin >> q;
        for (int j = 0; j < q; j++) {
            int t;
            cin >> t;
            G[0].push_back({t, 0});
        }
        for (int j = 1; j <= P; j++) {
            int n;
            cin >> n;
            for (int k = 0; k < n; k++) {
                int t, w;
                cin >> w >> t;
                if (t == 0) t = P + 1;
                G[j].push_back({t, w});
            }
        }

        cout << solveUsher(G, C) << endl;
    }
    return 0;
}