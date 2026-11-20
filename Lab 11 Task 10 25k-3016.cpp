#include <iostream>
using namespace std;

const int N = 6;

struct Node {
    int v;
    Node* next;
};

Node* adj[N];

void addEdge(int a, int b) {
    Node* n = new Node;
    n->v = b;
    n->next = NULL;
    if (adj[a] == NULL) adj[a] = n;
    else {
        Node* t = adj[a];
        while (t->next != NULL) t = t->next;
        t->next = n;
    }
}

int main() {
    int edges[5][2] = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}};

    for (int i = 0; i < N; i++) adj[i] = NULL;

    for (int i = 0; i < 5; i++) {
        addEdge(edges[i][0], edges[i][1]);
        addEdge(edges[i][1], edges[i][0]);
    }

    cout << "Adjacency List:\n";
    for (int i = 0; i < N; i++) {
        cout << i << " -> ";
        Node* t = adj[i];
        while (t != NULL) {
            cout << t->v << " ";
            t = t->next;
        }
        cout << endl;
    }

    bool visited[N] = {false};
    int q[N], front = 0, rear = 0;
    int order[N], count = 0;

    visited[0] = true;
    q[rear++] = 0;

    while (front < rear) {
        int u = q[front++];
        order[count++] = u;
        Node* t = adj[u];
        while (t != NULL) {
            if (!visited[t->v]) {
                visited[t->v] = true;
                q[rear++] = t->v;
            }
            t = t->next;
        }
    }

    cout << "\nTraversal sequence: ";
    for (int i = 0; i < count; i++) cout << order[i] << " ";
    cout << "\nTotal sections visited: " << count << endl;

    return 0;
}
