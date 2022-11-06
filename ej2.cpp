#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <limits>

using namespace std;

#define INF numeric_limits<int>::max()

using Matrix = vector<vector<int>>;
Matrix weight;

struct edge {
    int u;
    int v;

    bool operator > (const edge &other) const {
        return (weight[u][v] > weight[other.u][other.v]);
    }
};


struct unionFind {
    vector<int> parent, size, minEdge;
    vector<list<int>> descendants;

    explicit unionFind(int n): parent(n, -1), size(n, 1), minEdge(n, INF) {
        // Initialize each descendants list with each node as its descendant.
        for (int i = 0; i < n; i++) descendants.push_back({i});
    }

    ;
    void unite(int v, int w) {
        v = find(v); w = find(w);
        if (size[v] < size[w]) swap(v, w); // Make sure w is always 'smaller' than v
        parent[w] = v;
        size[v] += size[w];

        int newMinEdge = INF;
        for (auto i : descendants[v]) {
            for (auto j : descendants[w]){
                if (weight[i][j] < newMinEdge) newMinEdge = weight[i][j];
            }
        }
        minEdge[v] = min({newMinEdge, minEdge[v], minEdge[w]});

        descendants[v].splice(descendants[v].end(), descendants[w]);
    }

    int find(int v) {
        return parent[v] == -1 ? v : parent[v] = find(parent[v]);
    }

    int getMinEdge(int v) {
        v = find(v);
        return minEdge[v];
    }

    int getSize(int v) {
        v = find(v);
        return size[v];
    }

};

int T, N, M;

int solveTourBelt(int &n, vector<edge> &m) {
    int sumTourBeltSize = 0;

    sort(m.begin(), m.end(), greater<edge>());

    unionFind sets(n + 1);

    vector<int> modifiedTrees;
    for (int i = 0; i < m.size(); i++) {
        edge e = m[i];
        if (sets.find(e.u) != sets.find(e.v)) {
            sets.unite(e.u, e.v);
        }
        modifiedTrees.push_back(sets.find(e.u));

        // If this is the last edge of weight weight[e.u][e.v] (i.e. the following one is smaller)
        if (i == m.size() - 1 ||  weight[e.u][e.v] > weight[m[i + 1].u][m[i + 1].v]) {

            // Grab unique trees
            set<int> uniqueModifiedTrees;
            for (int t : modifiedTrees) {
                uniqueModifiedTrees.emplace(sets.find(t));
            }

            set<int>::iterator it;
            for (it = uniqueModifiedTrees.begin(); it != uniqueModifiedTrees.end(); it++) {
                // Tree is Tour Belt <=> the weight of its minimum edge matches this level's weight
                if (sets.getMinEdge(*it) == weight[e.u][e.v]) {
                    sumTourBeltSize += sets.getSize(*it);
                }
            }
            modifiedTrees.clear();
        }
    }

    return sumTourBeltSize;
}

int main() {
    cin >> T;
    for(int i = 0; i < T; i++) {
        cin >> N >> M;
        vector<edge> edges;
        weight = Matrix(N + 1, vector<int>(N + 1, INF));
        for (int j = 0; j < M; j++) {
            int v, w, k;
            cin >> v >> w >> k;
            edges.push_back({v, w});
            weight[v][w] = k;
            weight[w][v] = k;
        }


        cout << solveTourBelt(N, edges) << endl;

    }
    return 0;
}