#include <iostream>
using namespace std;

const int N = 7;
const int INF = 1000000000;
int w[N][N];

int main() {
    int e, a, b, c;
    cout << "Enter number of possible cable connections: ";
    cin >> e;
    cout << "Enter each connection as: department1 department2 cost\n";
    for (int i = 0; i < e; i++) {
        cin >> a >> b >> c;
        if (a < 0 || a >= N || b < 0 || b >= N || a == b || c <= 0) {
            cout << "Invalid connection\n";
            i--;
            continue;
        }
        w[a][b] = c;
        w[b][a] = c;
    }

    bool in[N] = {false};
    int key[N], par[N];
    for (int i = 0; i < N; i++) {
        key[i] = INF;
        par[i] = -1;
    }
    key[0] = 0;
    int total = 0;

    cout << "\nSelected connections:\n";
    for (int cnt = 0; cnt < N; cnt++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!in[i] && (u == -1 || key[i] < key[u])) u = i;
        if (key[u] == INF) {
            cout << "Not all departments can be connected\n";
            return 0;
        }
        in[u] = true;
        if (par[u] != -1) {
            cout << par[u] << " - " << u << " : " << key[u] << endl;
            total += key[u];
        }
        for (int v = 0; v < N; v++) {
            if (w[u][v] && !in[v] && w[u][v] < key[v]) {
                key[v] = w[u][v];
                par[v] = u;
            }
        }
    }

    cout << "Minimum total installation cost: " << total << endl;

    return 0;
}
