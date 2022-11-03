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
    bool satisfiable;
    vector<int> solution;
};

int T;

ostream &operator<<(ostream &out, const vector<int> &vec) {
    for(int i : vec) out << i << ' ';
    return out;
}

fishburnOutput fishburnSolver(int &variableCount, vector<constraint> &inequalities, const vector<int> &D) {
    vector<int> X(variableCount + 1, D[D.size() - 1]);
    bool satisfiable = true;

    bool changed = true;
    while (changed) {
        changed = false;
        for (constraint c : inequalities) {
            int k = INF; // TODO: si existe un k tal que D[k] ≤ X[c.i] + c.b elijo el k más grande y lo pongo acá
            if (X[c.i] > X[c.j] + c.b && k != INF) {
                X[c.j] = k;
                changed = true;
            }
        }
    }

    for (constraint c : inequalities) {
        if (X[c.i] - X[c.j] > c.b) {
            satisfiable = false;
        }
    }

    return {satisfiable, X};
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
        if (s.satisfiable) {
            cout << s.solution << endl;
        } else {
            cout << "insatisfactible" << endl;
        }

    }
    return 0;
}