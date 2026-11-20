#include <iostream>
using namespace std;

const int N = 7;
const int INF = 1000000000;
int w[N][N];

void printPath(int par[], int v) {
    if (par[v] == -1) {
        cout << v;
        return;
    }
    printPath(par, par[v]);
    cout << " -> " << v;
}

int main() {
    int edges[9][3] = {
        {0, 1, 4}, {0, 2, 2}, {1, 2, 1}, {1, 3, 5}, {2, 3, 8},
        {2, 4, 10}, {3, 4, 2}, {3, 5, 6}, {4, 5, 3}
    };

    for (int i = 0; i < 9; i++) {
        w[edges[i][0]][edges[i][1]] = edges[i][2];
        w[edges[i][1]][edges[i][0]] = edges[i][2];
    }

    int s;
    cout << "Enter starting city (0-6): ";
    cin >> s;
    if (s < 0 || s >= N) {
        cout << "Invalid city\n";
        return 0;
    }

    int dist[N], par[N];
    bool done[N];
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        par[i] = -1;
        done[i] = false;
    }
    dist[s] = 0;

    for (int c = 0; c < N; c++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!done[i] && (u == -1 || dist[i] < dist[u])) u = i;
        if (dist[u] == INF) break;
        done[u] = true;
        for (int v = 0; v < N; v++) {
            if (w[u][v] && dist[u] + w[u][v] < dist[v]) {
                dist[v] = dist[u] + w[u][v];
                par[v] = u;
            }
        }
    }

    cout << "\nShortest distances from city " << s << ":\n";
    for (int i = 0; i < N; i++) {
        cout << "City " << i << ": ";
        if (dist[i] == INF) cout << "unreachable\n";
        else cout << dist[i] << endl;
    }

    cout << "\nShortest routes:\n";
    for (int i = 0; i < N; i++) {
        if (i == s) continue;
        cout << "City " << i << ": ";
        if (dist[i] == INF) cout << "no route\n";
        else {
            printPath(par, i);
            cout << "  (distance " << dist[i] << ")\n";
        }
    }

    int far = -1;
    for (int i = 0; i < N; i++) {
        if (i == s || dist[i] == INF) continue;
        if (far == -1 || dist[i] > dist[far]) far = i;
    }

    if (far == -1) cout << "\nNo reachable destination\n";
    else cout << "\nFarthest destination: City " << far << " (distance " << dist[far] << ")\n";

    return 0;
}
