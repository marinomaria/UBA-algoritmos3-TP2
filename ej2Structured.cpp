#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

#define INF numeric_limits<int>::max()

using Matrix = vector<vector<int>>;
Matrix weight;

struct edge {
    int u;
    int v;

    bool operator > (const edge &other) const {
        return (weight[u][v] < weight[other.u][other.v]);
    }
};


struct unionFind {
    vector<int> parent, size, minEdge;
    vector<list<int>> descendants;

    explicit unionFind(int n): parent(n, -1), size(n, 1), minEdge(n, INF), descendants(n) {}

    void unite(int v, int w) {
        v = find(v); w = find(w);
        //  if(v == w) return;
        // No need to make it robust as unite() will be called if and only if v and w are from different sets
        if (size[v] < size[w]) swap(v, w);
        parent[w] = v;
        size[v] += size[w];
        descendants[v].splice(descendants[v].end(), descendants[w]);

        int newMinEdge = INF;
        for (auto i : descendants[v]) {
            for (auto j : descendants[w]){
                if (weight[i][j] < newMinEdge) newMinEdge = weight[i][j];
            }
        }
        minEdge[v] = min({newMinEdge, minEdge[v], minEdge[w]});

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

int solveTourBelt(int &n, vector<edge> m) {
    int sumTourBeltSize = 0;

    sort(m.begin(), m.end(), greater<edge>());

    return sumTourBeltSize;
}

int main() {
    cin >> T;
    for(int i = 0; i < T; i++) {
        cin >> N >> M;
        vector<edge> edges;
        weight = Matrix(N, vector<int>(N, -1));
        for (int j = 0; j < M; j++) {
            int v, w, k;
            cin >> v >> w >> k;
            edges.push_back({v, w});
            weight[v][w] = k;
        }


        cout << solveTourBelt(N, edges) << endl;

    }
    return 0;
}