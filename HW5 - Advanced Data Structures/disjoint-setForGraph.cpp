#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class node {
public:
    int size;
    int rank;
    node* parent;
};

void make_set(node* x) {
    x->parent = x;
    x->rank = 1;
    x->size = 1;
}

node* find(node* x) {
    if (x->parent != x){
        x->parent = find(x->parent);
    }
    return x->parent;
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

class edge {
public:
    int x, y, f;
    int num;
    edge(int x, int y, int f, int num) {
        this->num = num;
        this->x = x;
        this->y = y;
        this->f = f;
    }
};

int main() {
    int n;
    int x, y, f;
    cin >> n;
    set<int> fs;
    vector<edge*> edges;
    node** vertices =  new node*[n];
    auto* out = new long long [n-1];

    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y >> f;
        edges.push_back(new edge(x, y, f, i));
    }

    sort(edges.begin(), edges.end(), [](const edge* lhs, const edge* rhs) {
        return lhs->f <= rhs->f;
    });

    for (int i = 0; i < n; i++) {
        vertices[i] = new node();
        make_set(vertices[i]);
    }
    
    for (int i = 0; i < n - 1; i++) {
        out[edges[i]->num]  = ((long long)find(vertices[edges[i]->x - 1])->size * (long long)
                find(vertices[edges[i]->y - 1])->size) * 2;
        myUnion(vertices[edges[i]->x - 1], vertices[edges[i]->y - 1]);
    }
    
    for (int i = 0; i < n - 1; i++ ){
        cout << out[i] << " ";
    }

}
