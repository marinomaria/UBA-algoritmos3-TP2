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

#define INF numeric_limits<int>::max()
int T, C, P;

vector<int> dijkstra(const Graph &adj, int source) {
    struct node {int n; int dist;};
    class nodeGreater {
    public:
        bool operator() (const node &u, const node &v) {
            return u.dist >= v.dist;
        }
    };

    vector<int> nodeDistance(adj.size(), INF);
    nodeDistance[source] = 0;
    priority_queue<node, vector<node>, nodeGreater> Q;
    Q.push({0,0});
    for (int i = 1; i < adj.size(); i++) {
        Q.push({i, INF});
    }

    while (!Q.empty()) {
        node u = Q.top();
        Q.pop();
//      If this node's distance is outdated better distance has been previously found, ignore
        if (u.dist > nodeDistance[u.n]) {
            continue;
        }
        for (edge e : adj[u.n]) {
            int v = e.to;
            if (nodeDistance[v] > nodeDistance[u.n] + e.weight) {
                int newDist = nodeDistance[u.n] + e.weight;
                nodeDistance[v] = newDist;
                Q.push({v, newDist});
            }
        }

    }

    return nodeDistance;
}

int solveUsher(const Graph &G, int &boxCapacity) {
    int minDonationRound = dijkstra(G, 0)[G.size() - 1];
    int usherProfit = 0;
    int box = minDonationRound;
    while(box < boxCapacity) {
        usherProfit++;
        box += (minDonationRound - 1);
        }
    return usherProfit;
}

int main() {
    cin >> T;
    for(int i = 0; i < T; i++) {
        cin >> C >> P;
        // We'll use the node 0 as a source usher and the node P + 1 as a target usher
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
