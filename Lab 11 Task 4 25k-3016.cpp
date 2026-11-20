#include <iostream>
using namespace std;

const int N = 10;
int adj[N][N];
int comp[N];

void dfs(int u, int id) {
    comp[u] = id;
    for (int v = 0; v < N; v++)
        if (adj[u][v] && comp[v] == -1) dfs(v, id);
}

int main() {
    int e, a, b;
    cout << "Enter number of connections: ";
    cin >> e;
    cout << "Enter each connection (routers 0-9):\n";
    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        if (a < 0 || a >= N || b < 0 || b >= N || a == b) {
            cout << "Invalid connection\n";
            i--;
            continue;
        }
        adj[a][b] = 1;
        adj[b][a] = 1;
    }

    for (int i = 0; i < N; i++) comp[i] = -1;

    int groups = 0;
    for (int i = 0; i < N; i++)
        if (comp[i] == -1) dfs(i, groups++);

    int size[N] = {0};
    for (int i = 0; i < N; i++) size[comp[i]]++;

    for (int g = 0; g < groups; g++) {
        cout << "Group " << g + 1 << ": ";
        for (int i = 0; i < N; i++)
            if (comp[i] == g) cout << i << " ";
        cout << endl;
    }

    cout << "Number of separate networks: " << groups << endl;

    int best = 0;
    for (int g = 1; g < groups; g++)
        if (size[g] > size[best]) best = g;

    cout << "Largest network (Group " << best + 1 << "): ";
    for (int i = 0; i < N; i++)
        if (comp[i] == best) cout << i << " ";
    cout << "\nSize: " << size[best] << endl;

    return 0;
}
