#include <iostream>
#include <vector>
#include <set>

using namespace std;

class node {
public :
    int key;
    node* parent;
    vector<node*> children;
    int subtreeSize = 0;
    explicit node(int key) {
        this->key = key;
        this->parent = nullptr;
        this->subtreeSize = 1;
    }
};

class tree {
public:
    node** nodes;

    explicit tree(int n) {
        nodes = new node* [n];
        for (int i = 0; i < n; i++) {
            nodes[i] = new node(i + 1);
        }
    }

    void addNode(int i, int p) {
        nodes[p-1]->children.push_back(nodes[i-1]);
        nodes[i-1]->parent = nodes[p-1];
    }

    long long LCA(int a, int b, int n) {

        if (a == b) {
            return n;
        }
        a = a - 1;
        b = b - 1;

        node* aN = nodes[a];
        node* bN = nodes[b];
        vector<int> aL;
        vector<int> bL;
        set<int> aP;

        int n1 = 0, n2 = 0;
        aP.insert(aN->key);
        while (aN->parent != nullptr) {
            aP.insert(aN->parent->key);
            aN = aN->parent;
        }

        int x;
        x = bN->key;
        if (aP.find(x) != aP.end()) {
            bL.push_back(bN->key); n2++;
        }
        else {
            bL.push_back(bN->key);
            n2++;
            while (bN->parent != nullptr) {
                x = bN->parent->key;
                if (aP.find(x) == aP.end()) {
                    bL.push_back(x);
                    n2++;
                } else {
                    break;
                }
                bN = bN->parent;
            }
            bL.push_back(x); n2++;
        }
        int ind;

        aN = nodes[a];

        if (x!=a+1) {
            aL.push_back(aN->key);
            n1++;
            while (aN->parent != nullptr && aN->parent->key != x) {
                n1++;
                aL.push_back(aN->parent->key);
                aN = aN->parent;
            }
        }



        int a1, a2;
        for (int i = 0; i < n2; i++) {
            aL.push_back(bL[n2 - i - 1]);
        }

        /*
         * for (int i = 0; i < n1+n2; i++) {
            cout << aL[i] << " ";
        } cout << endl;*/
        int mid = (n1 + n2) / 2 + 1;
        if ((n1 + n2) % 2 == 0) {
            return 0;
        }
        if (n2 == n1 + 1) {
            a1 = aL[n1 - 1];
            a2 = aL[n1 + 1];
            return ((long long)n - (long long)nodes[a1-1]->subtreeSize - (long long)nodes[a2-1]->subtreeSize);
        }
        else {
            if (mid <= n1) {
                a1 = aL[mid - 1];
                a2 = aL[mid - 2];
                return ((long long)nodes[a1-1]->subtreeSize - (long long)nodes[a2 - 1]->subtreeSize);
            } else {
                a1 = aL[mid - 1];
                a2 = aL[mid];//cout << endl << a1 << " " << a2 << endl;
                //cout << nodes[a1-1]->subtreeSize << " " << nodes[a2 - 1]->subtreeSize << endl;
                return ((long long)nodes[a1-1]->subtreeSize - (long long)nodes[a2 - 1]->subtreeSize);
            }
        }
    }
};

int dfs(node* s) {
    for (auto itr:s->children) {
        s->subtreeSize += dfs(itr);
    }
    return s->subtreeSize;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, p, m, a, b;
    cin >> n;
    tree* myTree = new tree(n);
    for (int i = 2; i <= n; i++) {
        cin >> p;
        myTree->addNode(i, p);
    }
    dfs(myTree->nodes[0]);
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        //myTree->LCA(a, b, n);
       cout << myTree->LCA(a, b, n) << endl;
    }
}
