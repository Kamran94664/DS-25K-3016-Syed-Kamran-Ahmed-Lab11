#include <iostream>
using namespace std;

const int N = 8;

int main() {
    int adj[N][N] = {0};
    int visited[N] = {0};
    int dist[N];
    int parent[N];
    int queue[N];
    int order[N];
    int front = 0, rear = 0, orderCount = 0;

    int e, u, v;
    cout << "Enter number of roads: ";
    cin >> e;
    cout << "Enter each road as two locations (0-7):\n";
    for (int i = 0; i < e; i++) {
        cin >> u >> v;
        if (u < 0 || u >= N || v < 0 || v >= N) {
            cout << "Invalid road\n";
            i--;
            continue;
        }
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    for (int i = 0; i < N; i++) {
        dist[i] = -1;
        parent[i] = -1;
    }

    visited[0] = 1;
    dist[0] = 0;
    queue[rear++] = 0;

    while (front < rear) {
        int cur = queue[front++];
        order[orderCount++] = cur;
        for (int i = 0; i < N; i++) {
            if (adj[cur][i] == 1 && !visited[i]) {
                visited[i] = 1;
                dist[i] = dist[cur] + 1;
                parent[i] = cur;
                queue[rear++] = i;
            }
        }
    }

    cout << "\nVisiting order: ";
    for (int i = 0; i < orderCount; i++) cout << order[i] << " ";
    cout << endl;

    cout << "\nMinimum roads from location 0:\n";
    for (int i = 0; i < N; i++) {
        if (dist[i] == -1) cout << "Location " << i << ": unreachable\n";
        else cout << "Location " << i << ": " << dist[i] << endl;
    }

    int dest;
    cout << "\nEnter destination: ";
    cin >> dest;

    if (dest < 0 || dest >= N || dist[dest] == -1) {
        cout << "Destination unreachable\n";
        return 0;
    }

    int path[N];
    int len = 0;
    for (int x = dest; x != -1; x = parent[x]) path[len++] = x;

    cout << "Route: ";
    for (int i = len - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;

    return 0;
}
