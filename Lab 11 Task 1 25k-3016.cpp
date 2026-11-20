#include <iostream>
using namespace std;

const int N = 6;

int main() {
    int adj[N][N] = {0};
    int choice, a, b;

    do {
        cout << "\n1. Add connection\n2. Remove connection\n3. Display connectivity\n4. Department with most connections\n5. Total connections\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            cout << "Enter two departments (0-5): ";
            cin >> a >> b;
            if (a < 0 || a >= N || b < 0 || b >= N || a == b) {
                cout << "Invalid input\n";
                continue;
            }
            int val = (choice == 1) ? 1 : 0;
            adj[a][b] = val;
            adj[b][a] = val;
        }
        else if (choice == 3) {
            cout << "   ";
            for (int i = 0; i < N; i++) cout << i << " ";
            cout << endl;
            for (int i = 0; i < N; i++) {
                cout << i << ": ";
                for (int j = 0; j < N; j++) cout << adj[i][j] << " ";
                cout << endl;
            }
        }
        else if (choice == 4) {
            int maxDeg = -1, maxDept = 0;
            for (int i = 0; i < N; i++) {
                int deg = 0;
                for (int j = 0; j < N; j++) deg += adj[i][j];
                if (deg > maxDeg) {
                    maxDeg = deg;
                    maxDept = i;
                }
            }
            cout << "Department " << maxDept << " has the most connections: " << maxDeg << endl;
        }
        else if (choice == 5) {
            int total = 0;
            for (int i = 0; i < N; i++)
                for (int j = i + 1; j < N; j++)
                    total += adj[i][j];
            cout << "Total connections: " << total << endl;
        }
    } while (choice != 0);

    return 0;
}
