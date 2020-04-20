#include <iostream>

using namespace std;
int n1, n2;

class node {
public:
    int key;
    node* parent, * right, * left;

    explicit node (int key) {
        this->key =  key;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};
void inorder(node* r) {
    if (r == nullptr) {
        return;
    }
    inorder(r->left);
    cout << r->key << " ";
    inorder(r->right);
}
void preorder(node* r) {
    if (r == nullptr) {
        return;
    }
    cout << r->key << " ";
    preorder(r->left);
    preorder(r->right);
}
class splayTree {
public:
    node* root = nullptr;

    static void rightRotate(node* y) {
        node * x = y->left;
        node * B = x->right;
        node * yP = y->parent;
        if (yP != nullptr) {
            if (y == yP->right) {
                yP->right = x;
            } else {
                yP->left = x;
            }
        }
        x->right = y;
        y->left = B;
        if (B != nullptr) {
            B->parent = y;
        }
        y->parent = x;
        x->parent = yP;
    }

    static void leftRotate(node* y) {
        node* x = y->right;
        node* B = x->left;
        node* yP = y->parent;
        if (yP != nullptr) {
            if (y == yP->right) {
                yP->right = x;
            } else {
                yP->left = x;
            }
        }
        x->left = y;
        y->right = B;
        if (B != nullptr) {
            B->parent = y;
        }
        y->parent = x;
        x->parent = yP;
    }

    static void splay(node* xNode) {
        while (xNode->parent != nullptr) {
            node* P = xNode->parent;
            node* gP = xNode->parent->parent;

            if (xNode == P->left) {
                if (gP == nullptr) {
                    rightRotate(xNode->parent);
                } else {
                    if (P == gP->left) {
                        rightRotate(gP);
                        rightRotate(xNode->parent);
                        n1++;
                    } else {
                        rightRotate(xNode->parent);
                        leftRotate(xNode->parent);
                        n2++;
                    }
                }
            }

            if (xNode == P->right) {
                if (gP == nullptr) {
                    leftRotate(P);
                } else {
                    if (P == gP->right) {
                        leftRotate(gP);
                        leftRotate(xNode->parent);
                        n1++;
                    } else {
                        leftRotate(xNode->parent);
                        rightRotate(xNode->parent);
                        n2++;
                    }
                }
            }
        }
    }

    static node* max(node* r) {
        while (r->right != nullptr){
            r = r->right;
        }
        return r;
    }

    static node* search(node* root, int x) {
        if (root->key == x){
            return root;
        }
        if (x < root->key) {
            if (root->left == nullptr) {
                return root;
            } else {
                return search(root->left, x);
            }
        } else {
            if (root->right == nullptr) {
                return root;
            } else {
                return search(root->right, x);
            }
        }
    }

    static node* searchI(node* root, int x) {
        if (x < root->key) {
            if (root->left == nullptr) {
                return root;
            } else {
                return searchI(root->left, x);
            }
        } else {
            if (root->right == nullptr) {
                return root;
            } else {
                return searchI(root->right, x);
            }
        }
    }

    void access(int x) {
        if (this->root == nullptr) {
            return;
        }
        node* xNode = search(this->root, x);
        splay(xNode);
        this->root = xNode;
    }


    void accessI(int x) {
        if (this->root == nullptr) {
            return;
        }
        node* xNode = searchI(this->root, x);
        splay(xNode);
        this->root = xNode;
    }

    node* join(node* t1, node* t2) {
        if (t1 == nullptr) {
            return t2;
        }
        node* s = max(t1);
        splay(s);
        s->right = t2;
        if (t2 != nullptr) {
            t2->parent = s;
        }
        return s;
    }

    void split(node* &t1, node* &t2, int x) {
        accessI(x);
        if (x <= this->root->key) {
            t2 = this->root;
            t1 = t2->left;
            t2->left = nullptr;
            if (t1 != nullptr) {
                t1->parent = nullptr;
            }
        } else {
            t1 = this->root;
            t2 = t1->right;
            t1->right = nullptr;
            if (t2 != nullptr) {
                t2->parent = nullptr;
            }
        }
    }

    void insert(int x) {
        if (this->root  == nullptr) {
            this->root = new node(x);
            return;
        }
        node* t1,  *t2;
        split(t1, t2, x);
        this->root = new node(x);
        this->root->left = t1;
        this->root->right = t2;
        if (t2 != nullptr) {
            t2->parent = this->root;
        }
        if (t1 != nullptr) {
            t1->parent = this->root;
        }
    }

    void remove(int x) {
        if (this->root->key == x) {
            node* t1 = this->root->left;
            node* t2 = this->root->right;
            if (t1) {
                t1->parent = nullptr;
            }
            if (t2) {
                t2->parent = nullptr;
            }
            this->root = join(t1, t2);
        } else {
            access(x);
            node* t1 = this->root->left;
            node* t2 = this->root->right;
            if (t1) {
                t1->parent = nullptr;
            }
            if (t2) {
                t2->parent = nullptr;
            }
            this->root = join(t1, t2);
        }
    }

};


int main() {
    auto* tree = new splayTree;
    int m, f, x;
    cin >> m;
    int* o1 = new int[m];
    int* o2 = new int [m];
    for (int i = 0; i < m; i++) {
        n1 = 0;
        n2 = 0;
        cin >> f >> x;

        if (f==1) {
            tree->insert(x);
        } else if (f == 2) {
            tree->remove(x);
        } else if (f == 3) {
            tree->access(x);
        }

        o1[i] = n1;
        o2[i] = n2;
        //inorder(tree->root); cout  << endl;
    }

    for (int i = 0; i < m; i++) {
        cout << o1[i] << " " << o2[i] << endl;
    }

}
