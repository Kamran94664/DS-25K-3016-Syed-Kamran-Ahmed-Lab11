#include <iostream>
using namespace std;

const int N = 5;

int main() {
    int adj[N][N] = {0};
    int edges[4][2] = {{0, 1}, {0, 2}, {1, 3}, {2, 4}};

    for (int i = 0; i < 4; i++) {
        adj[edges[i][0]][edges[i][1]] = 1;
        adj[edges[i][1]][edges[i][0]] = 1;
    }

    cout << "Adjacency Matrix:\n   ";
    for (int i = 0; i < N; i++) cout << i << " ";
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << i << ": ";
        for (int j = 0; j < N; j++) cout << adj[i][j] << " ";
        cout << endl;
    }

    int a, b;
    cout << "\nEnter two classrooms (0-4): ";
    cin >> a >> b;
    if (a < 0 || a >= N || b < 0 || b >= N) cout << "Invalid classroom\n";
    else if (adj[a][b]) cout << "Classrooms " << a << " and " << b << " are directly connected\n";
    else cout << "Classrooms " << a << " and " << b << " are not directly connected\n";

    int deg[N];
    cout << "\nDirect connections per classroom:\n";
    for (int i = 0; i < N; i++) {
        deg[i] = 0;
        for (int j = 0; j < N; j++) deg[i] += adj[i][j];
        cout << "Classroom " << i << ": " << deg[i] << endl;
    }

    int best = 0;
    for (int i = 1; i < N; i++)
        if (deg[i] > deg[best]) best = i;
    cout << "\nClassroom with the most direct connections: " << best << " (" << deg[best] << ")\n";

    return 0;
}
