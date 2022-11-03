#include <iostream>
#include <vector>

using namespace std;

struct constraint {
    // Represents constraint X[a] - X[b] ≤ c
    int a;
    int b;
    int c;
};

int T;

ostream &operator<<(ostream &out, const vector<int> &vec) {
    for(int i : vec) out << i << ' ';
    return out;
}

vector<int> fishburnSolver(int &n, vector<constraint> &C, const vector<int> &D) {
    vector<int> X(n + 1);

    return X;
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

        cout << fishburnSolver(n, constraints, D) << endl;

    }
    return 0;
}