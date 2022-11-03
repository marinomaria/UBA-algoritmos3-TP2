#include <iostream>
#include <vector>

using namespace std;

#define INF numeric_limits<int>::max()

struct constraint {
    // Represents constraint X[j] - X[i] ≤ b
    int i;
    int j;
    int b;
};

struct fishburnOutput {
    bool satisfiable;
    vector<int> solution;
};

int T;

ostream &operator<<(ostream &out, const vector<int> &vec) {
    for(int i : vec) out << i << ' ';
    return out;
}

vector<int> tail(const vector<int> &v) {
    return {v.begin() + 1, v.end()};
}

int findK(const constraint &c, const vector<int> &D, const vector<int> &X) {
    int k = INF;
    for (int i = D.size() - 1; i >= 1; i--) {
        if (D[i] <= X[c.i] + c.b) {
            k = i; break;
        }
    }

    return k;
}

fishburnOutput fishburnSolver(int &variableCount, vector<constraint> &inequalities, const vector<int> &D) {
    vector<int> X(variableCount + 1, D[D.size() - 1]);
    bool satisfiable = true;

    bool changed;
    do {
        changed = false;
        for (int l = 1; l <= inequalities.size(); l++) {
            constraint c = inequalities[l];
            int k = findK(c, D, X);
            if (X[c.j] > X[c.i] + c.b && k < D.size()) {
                X[c.j] = D[k];
                changed = true;
            }
        }
    } while (changed);

    for (int l = 1; l <= inequalities.size(); l++) {
        constraint c = inequalities[l];
        if (X[c.j] - X[c.i] > c.b) {
            satisfiable = false;
        }
    }

    return {satisfiable, tail(X)};
}

int main() {
    cin >> T;
    for(int i = 0; i < T; i++) {
        int k, n, m;
        cin >> k >> n >> m;

        vector<constraint> constraints;
        constraints.push_back({-1,-1,-1});
        for (int j = 0; j < k; j++) {
            int a, b, c;
            cin >> a >> b >> c;
            constraints.push_back({b, a, c});
        }

        vector<int> D;
        D.push_back(-1);
        for (int l = 0; l < m; l++) {
            int d;
            cin >> d;
            D.push_back(d);
        }

        fishburnOutput s = fishburnSolver(n, constraints, D);
        if (s.satisfiable) {
            cout << s.solution << endl;
        } else {
            cout << "insatisfactible" << endl;
        }

    }
    return 0;
}