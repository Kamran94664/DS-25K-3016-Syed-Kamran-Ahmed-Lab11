#include <iostream>
using namespace std;

const int N = 8;
const int INF = 1000000000;
int w[N][N];

int main() {
    int choice, a, b, c;

    do {
        cout << "\n1. Add connection\n2. Modify connection cost\n3. Build network (minimum cost)\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            cout << "Enter area 1, area 2 and cost: ";
            cin >> a >> b >> c;
            if (a < 0 || a >= N || b < 0 || b >= N || a == b || c <= 0) {
                cout << "Invalid input\n";
                continue;
            }
            if (choice == 2 && w[a][b] == 0) {
                cout << "Connection does not exist\n";
                continue;
            }
            w[a][b] = c;
            w[b][a] = c;
        }
        else if (choice == 3) {
            bool in[N] = {false};
            int key[N], par[N];
            for (int i = 0; i < N; i++) {
                key[i] = INF;
                par[i] = -1;
            }
            key[0] = 0;
            int total = 0;
            bool ok = true;

            cout << "Selected connections:\n";
            for (int cnt = 0; cnt < N; cnt++) {
                int u = -1;
                for (int i = 0; i < N; i++)
                    if (!in[i] && (u == -1 || key[i] < key[u])) u = i;
                if (key[u] == INF) {
                    ok = false;
                    break;
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

            if (!ok) cout << "Not all areas can be connected with the given connections\n";
            else cout << "Total installation cost: " << total << endl;
        }
    } while (choice != 0);

    return 0;
}
