#include <iostream>
#include <string>
using namespace std;

struct FriendNode {
    string name;
    FriendNode* next;
};

struct User {
    string name;
    FriendNode* friends;
    User* next;
};

User* head = NULL;

User* findUser(string name) {
    User* t = head;
    while (t != NULL) {
        if (t->name == name) return t;
        t = t->next;
    }
    return NULL;
}

User* addUser(string name) {
    User* u = findUser(name);
    if (u != NULL) return u;
    u = new User;
    u->name = name;
    u->friends = NULL;
    u->next = head;
    head = u;
    return u;
}

bool isFriend(User* u, string name) {
    FriendNode* f = u->friends;
    while (f != NULL) {
        if (f->name == name) return true;
        f = f->next;
    }
    return false;
}

void addOneWay(User* u, string name) {
    FriendNode* f = new FriendNode;
    f->name = name;
    f->next = u->friends;
    u->friends = f;
}

void removeOneWay(User* u, string name) {
    FriendNode* cur = u->friends;
    FriendNode* prev = NULL;
    while (cur != NULL) {
        if (cur->name == name) {
            if (prev == NULL) u->friends = cur->next;
            else prev->next = cur->next;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

int countFriends(User* u) {
    int c = 0;
    FriendNode* f = u->friends;
    while (f != NULL) {
        c++;
        f = f->next;
    }
    return c;
}

void addFriendship(string a, string b) {
    if (a == b) {
        cout << "Cannot befriend yourself\n";
        return;
    }
    User* ua = addUser(a);
    User* ub = addUser(b);
    if (isFriend(ua, b)) {
        cout << "Already friends\n";
        return;
    }
    addOneWay(ua, b);
    addOneWay(ub, a);
}

void removeFriendship(string a, string b) {
    User* ua = findUser(a);
    User* ub = findUser(b);
    if (ua == NULL || ub == NULL || !isFriend(ua, b)) {
        cout << "Friendship does not exist\n";
        return;
    }
    removeOneWay(ua, b);
    removeOneWay(ub, a);
}

void displayFriends(string name) {
    User* u = findUser(name);
    if (u == NULL) {
        cout << "User not found\n";
        return;
    }
    cout << name << "'s friends: ";
    FriendNode* f = u->friends;
    if (f == NULL) cout << "none";
    while (f != NULL) {
        cout << f->name << " ";
        f = f->next;
    }
    cout << endl;
}

void largestNetwork() {
    if (head == NULL) {
        cout << "No users\n";
        return;
    }
    User* best = head;
    int bestCount = countFriends(head);
    User* t = head->next;
    while (t != NULL) {
        int c = countFriends(t);
        if (c > bestCount) {
            bestCount = c;
            best = t;
        }
        t = t->next;
    }
    cout << best->name << " has the largest network: " << bestCount << " friends\n";
}

void displayAll() {
    User* t = head;
    if (t == NULL) {
        cout << "No users\n";
        return;
    }
    while (t != NULL) {
        displayFriends(t->name);
        t = t->next;
    }
}

int main() {
    int choice;
    string a, b;

    do {
        cout << "\n1. Add friendship\n2. Remove friendship\n3. Display friends of a user\n4. User with largest network\n5. Display all users and friends\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter two usernames: ";
            cin >> a >> b;
            addFriendship(a, b);
        }
        else if (choice == 2) {
            cout << "Enter two usernames: ";
            cin >> a >> b;
            removeFriendship(a, b);
        }
        else if (choice == 3) {
            cout << "Enter username: ";
            cin >> a;
            displayFriends(a);
        }
        else if (choice == 4) {
            largestNetwork();
        }
        else if (choice == 5) {
            displayAll();
        }
    } while (choice != 0);

    return 0;
}
