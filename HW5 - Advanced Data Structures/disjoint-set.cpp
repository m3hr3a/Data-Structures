#include <iostream>
#include <vector>
#include <set>

using namespace std;

class node {
public:
    int size;
    int rank = 0;
    node* parent;
    node() {
        this->rank = 0;
        this->size = 1;
        this->parent = nullptr;
    }
};

node* find(node* x) {
    if (x->parent != nullptr){
        x->parent = find(x->parent);
    }
    if (x->parent == nullptr) {
        return x;
    } else {
        return x->parent;
    }
}

void link(node* x, node* y) {
    if (x->rank < y->rank) {
        x->parent = y;
        y->size = y->size + x->size;
    }
    else {
        y->parent = x;
        x->size = x->size + y->size;
        if (x->rank == y->rank) {
            x->rank = x->rank + 1;
        }
    }
}

void myUnion(node* x, node* y) {
    node* xp = find(x); 
    node* yp = find(y); 
    if (xp != yp) 
        link(xp, yp); 
}

int main() {
    int n, m, f, x, y;
    cin >> n >> m;
    node** vars = new node* [n];
    for (int i = 0; i < n; i++) {
        vars[i] = new node();
    }
    for (int i = 0; i < m; i++) {
        cin >> f;
        if (f == 1) {
            cin >> x >> y;
            myUnion(vars[x-1], vars[y-1]);
        } else {
            cin >> x;
            cout << find(vars[x-1])->size << endl;
        }
    }
}
