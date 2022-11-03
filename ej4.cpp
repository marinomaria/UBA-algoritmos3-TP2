#include <iostream>
#include <vector>

using namespace std;

#define INF numeric_limits<int>::max()

struct constraint {
    // Represents constraint X[i] - X[j] ≤ b
    int i;
    int j;
    int b;
};

struct fishburnOutput {
    bool isConsistent;
    vector<int> solution;
};

int T;

ostream &operator<<(ostream &out, const vector<int> &vec) {
    for(int i : vec) out << i << ' ';
    return out;
}

fishburnOutput fishburnSolver(int &n, vector<constraint> &C, const vector<int> &D) {
    vector<int> X(n + 1, D[D.size() - 1]);
    bool consistent = true;

    bool changed = true;
    while (changed) {
        changed = false;
        for (constraint c : C) {
            int k = INF; // TODO: si existe un k tal que D[k] ≤ X[c.i] + c.b elijo el k más grande y lo pongo acá
            if (X[c.i] > X[c.j] + c.b && k != INF) {
                X[c.j] = k;
                changed = true;
            }
        }
    }

    for (constraint c : C) {
        if (X[c.i] - X[c.j] > c.b) {
            consistent = false;
        }
    }

    return {consistent, X};
}

int main() {
    cin >> T;
    for(int i = 0; i < T; i++) {
        int k, n, m;
        cin >> k >> n >> m;

        vector<constraint> constraints;
        for (int j = 0; j < k; j++) {
            int a, b, c;
            cin >> a >> b >> c;
            constraints.push_back({a, b, c});
        }

        vector<int> D;
        for (int l = 0; l < m; l++) {
            int d;
            cin >> d;
            D.push_back(d);
        }

        sort(D.begin(), D.end());
        fishburnOutput s = fishburnSolver(n, constraints, D);
        if (s.isConsistent) {
            cout << s.solution << endl;
        } else {
            cout << "insatisfactible" << endl;
        }

    }
    return 0;
}