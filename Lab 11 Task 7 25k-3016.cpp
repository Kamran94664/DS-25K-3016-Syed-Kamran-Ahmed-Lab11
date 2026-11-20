#include <iostream>
using namespace std;

const int N = 8;
const int INF = 1000000000;
int w[N][N];
bool vis[N];
int ru[N * N], rv[N * N], rw[N * N], rc;
int dsu[N];

void displayNetwork() {
    bool any = false;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (w[i][j]) {
                cout << i << " - " << j << " : " << w[i][j] << endl;
                any = true;
            }
        }
    }
    if (!any) cout << "No roads\n";
}

void bfsLevels(int s) {
    int level[N], q[N], f = 0, r = 0;
    for (int i = 0; i < N; i++) level[i] = -1;
    level[s] = 0;
    q[r++] = s;
    while (f < r) {
        int u = q[f++];
        for (int v = 0; v < N; v++) {
            if (w[u][v] && level[v] == -1) {
                level[v] = level[u] + 1;
                q[r++] = v;
            }
        }
    }
    int maxL = level[q[r - 1]];
    for (int l = 0; l <= maxL; l++) {
        cout << "Level " << l << ": ";
        for (int i = 0; i < r; i++)
            if (level[q[i]] == l) cout << q[i] << " ";
        cout << endl;
    }
}

void dfs(int u) {
    vis[u] = true;
    cout << u << " ";
    for (int v = 0; v < N; v++)
        if (w[u][v] && !vis[v]) dfs(v);
}

bool cycleDfs(int u, int p) {
    vis[u] = true;
    for (int v = 0; v < N; v++) {
        if (w[u][v]) {
            if (!vis[v]) {
                if (cycleDfs(v, u)) return true;
            }
            else if (v != p) return true;
        }
    }
    return false;
}

bool hasCycle() {
    for (int i = 0; i < N; i++) vis[i] = false;
    for (int i = 0; i < N; i++)
        if (!vis[i] && cycleDfs(i, -1)) return true;
    return false;
}

void dijkstra(int s, int dist[], int par[]) {
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
}

void printPath(int par[], int v) {
    if (par[v] == -1) {
        cout << v;
        return;
    }
    printPath(par, par[v]);
    cout << " -> " << v;
}

int primMST() {
    bool in[N] = {false};
    int key[N], par[N];
    for (int i = 0; i < N; i++) {
        key[i] = INF;
        par[i] = -1;
    }
    key[0] = 0;
    rc = 0;
    int total = 0;
    for (int c = 0; c < N; c++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!in[i] && (u == -1 || key[i] < key[u])) u = i;
        if (key[u] == INF) return -1;
        in[u] = true;
        if (par[u] != -1) {
            ru[rc] = par[u];
            rv[rc] = u;
            rw[rc] = key[u];
            rc++;
            total += key[u];
        }
        for (int v = 0; v < N; v++) {
            if (w[u][v] && !in[v] && w[u][v] < key[v]) {
                key[v] = w[u][v];
                par[v] = u;
            }
        }
    }
    return total;
}

int findSet(int x) {
    while (dsu[x] != x) {
        dsu[x] = dsu[dsu[x]];
        x = dsu[x];
    }
    return x;
}

int kruskalMST() {
    int eu[N * N], ev[N * N], ew[N * N], ec = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (w[i][j]) {
                eu[ec] = i;
                ev[ec] = j;
                ew[ec] = w[i][j];
                ec++;
            }
        }
    }
    for (int i = 0; i < ec - 1; i++) {
        for (int j = 0; j < ec - i - 1; j++) {
            if (ew[j] > ew[j + 1]) {
                int t = ew[j]; ew[j] = ew[j + 1]; ew[j + 1] = t;
                t = eu[j]; eu[j] = eu[j + 1]; eu[j + 1] = t;
                t = ev[j]; ev[j] = ev[j + 1]; ev[j + 1] = t;
            }
        }
    }
    for (int i = 0; i < N; i++) dsu[i] = i;
    rc = 0;
    int total = 0;
    for (int k = 0; k < ec; k++) {
        int a = findSet(eu[k]);
        int b = findSet(ev[k]);
        if (a != b) {
            dsu[a] = b;
            ru[rc] = eu[k];
            rv[rc] = ev[k];
            rw[rc] = ew[k];
            rc++;
            total += ew[k];
        }
    }
    if (rc != N - 1) return -1;
    return total;
}

void printMST(int total) {
    if (total == -1) {
        cout << "Network is not fully connected\n";
        return;
    }
    for (int i = 0; i < rc; i++)
        cout << ru[i] << " - " << rv[i] << " : " << rw[i] << endl;
    cout << "Total cost: " << total << endl;
}

int main() {
    int e, a, b, c;
    cout << "Enter number of roads: ";
    cin >> e;
    cout << "Enter each road as: location1 location2 distance\n";
    for (int i = 0; i < e; i++) {
        cin >> a >> b >> c;
        if (a < 0 || a >= N || b < 0 || b >= N || a == b || c <= 0) {
            cout << "Invalid road\n";
            i--;
            continue;
        }
        w[a][b] = c;
        w[b][a] = c;
    }

    int choice, s, d;

    do {
        cout << "\n1. Display road network\n2. Explore level by level (BFS)\n3. Explore deeply (DFS)\n4. Check for cycle\n5. Shortest distances from a source\n6. Shortest route between two locations\n7. Minimum cost network (Prim)\n8. Minimum cost network (Kruskal)\n9. Compare both approaches\n10. Display final selected connections\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            displayNetwork();
        }
        else if (choice == 2) {
            cout << "Enter start location: ";
            cin >> s;
            if (s < 0 || s >= N) cout << "Invalid location\n";
            else bfsLevels(s);
        }
        else if (choice == 3) {
            cout << "Enter start location: ";
            cin >> s;
            if (s < 0 || s >= N) cout << "Invalid location\n";
            else {
                for (int i = 0; i < N; i++) vis[i] = false;
                dfs(s);
                cout << endl;
            }
        }
        else if (choice == 4) {
            if (hasCycle()) cout << "The road network contains a cycle\n";
            else cout << "The road network has no cycle\n";
        }
        else if (choice == 5) {
            cout << "Enter source location: ";
            cin >> s;
            if (s < 0 || s >= N) cout << "Invalid location\n";
            else {
                int dist[N], par[N];
                dijkstra(s, dist, par);
                for (int i = 0; i < N; i++) {
                    cout << "To " << i << ": ";
                    if (dist[i] == INF) cout << "unreachable\n";
                    else cout << dist[i] << endl;
                }
            }
        }
        else if (choice == 6) {
            cout << "Enter source and destination: ";
            cin >> s >> d;
            if (s < 0 || s >= N || d < 0 || d >= N) cout << "Invalid location\n";
            else {
                int dist[N], par[N];
                dijkstra(s, dist, par);
                if (dist[d] == INF) cout << "No route exists\n";
                else {
                    cout << "Route: ";
                    printPath(par, d);
                    cout << "\nDistance: " << dist[d] << endl;
                }
            }
        }
        else if (choice == 7) {
            printMST(primMST());
        }
        else if (choice == 8) {
            printMST(kruskalMST());
        }
        else if (choice == 9) {
            int p = primMST();
            int k = kruskalMST();
            if (p == -1 || k == -1) cout << "Network is not fully connected\n";
            else {
                cout << "Prim total cost: " << p << endl;
                cout << "Kruskal total cost: " << k << endl;
                if (p == k) cout << "Both approaches give the same minimum cost\n";
                else cout << "Costs differ\n";
            }
        }
        else if (choice == 10) {
            printMST(primMST());
        }
    } while (choice != 0);

    return 0;
}
