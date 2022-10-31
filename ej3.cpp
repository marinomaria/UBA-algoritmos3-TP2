#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct edge {
    int to;
    int weight;
};

using Graph = vector<vector<edge>>;

//#define INF numeric_limits<int>::max()
int INF = 10000;
int T, C, P;

int dijkstra(const Graph &adj, int source, int target) {
    struct node {
        int n;
        int dist;
    };
    class Compare
    {
    public:
        bool operator() (const node &u, const node &v)
        {
            return u.dist >= v.dist;
        }
    };

    vector<int> nodeDistance(adj.size(), INF);
    nodeDistance[source] = 0;
    priority_queue<node, vector<node>, Compare> Q;
    Q.push({0,0});
    for (int i = 1; i < adj.size(); i++) {
        Q.push({i, INF});
    }

    while (!Q.empty()) {
        int u = Q.top().n;

        for (edge e : adj[u]) {
            int v = e.to;
            if (nodeDistance[v] > nodeDistance[u] + e.weight) {
                int newDist = nodeDistance[u] + e.weight;
                nodeDistance[v] = newDist;
                Q.push({v, newDist});
            }
        }
        Q.pop();
    }

    return nodeDistance[target];
}

int solveUsher(const Graph &G, int &boxCapacity) {

    int n = dijkstra(G, 0, G.size() - 1);
    // Cree este codigo para contar bien los casos.
    int usherProfit = 0;
    int box = n;
    while(box<boxCapacity){
        usherProfit ++;
        box+=(n-1);
        }
    return usherProfit  ;

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
        //cout << "RESULTADO:" << endl;
        cout << solveUsher(G, C) << endl;

    }
    return 0;
}