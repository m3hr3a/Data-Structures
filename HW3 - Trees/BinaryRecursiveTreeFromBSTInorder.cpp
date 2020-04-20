#include <iostream>
#include <string.h>
using namespace std;

int* leftMax;
int* rightMin;
int* rightMax;
int n, c; int len = 0; int* pre;
int maxInserted = -3;

inline int max(int a,int b){
    if (a > b)
        return a;
    else
        return b;
}
inline int min(int a,int b){
    if (a < b)
        return a;
    else
        return b;
}
struct node {
    int key;
    node* left;
    node* right;
    node(int key){
        this->key = key;
        left = nullptr;
        right = nullptr;
    }
};


void inorder(node* tree){
    if (tree == nullptr){
        return;
    }
    inorder(tree->left);
    cout << tree->key << " ";
    inorder(tree->right);
}
void preorder(node* tree){
    if (tree == nullptr){
        return;
    }
    pre[len++] = tree->key;
    preorder(tree->left);
    preorder(tree->right);
}
void buildTree(node* r, int pLow, int pHigh) {
    node* root = r;
    //cout << pLow <<" "<< pHigh << " " << leftMax[pLow] << " " << rightMin[pLow] << " " << rightMax[pLow] <<endl;
    while ((pLow <= pHigh-1) && (rightMin[pLow] == -1) && (rightMin[pLow+1] == -1) &&
           (leftMax[pLow] == -1) && (leftMax[pLow+1] == -1)){
        root->key=pLow; maxInserted = max(maxInserted, pLow); //cout << "max Ins " << maxInserted << endl;
        root->left = new node(-1);
        root = root->left;
        pLow++;
    }
    if (rightMin[pLow] == -1 && leftMax[pLow] == -1){
        root->key = pLow; maxInserted= max(maxInserted, pLow); //cout << "max Ins " << maxInserted << endl;
    }

    if (leftMax[pLow] != -1){
        if (!(((pLow+1)>pLow) && (leftMax[pLow]) <= pHigh)){
            root->key = -1;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
    }
    if (rightMin[pLow] != -1){
        if (!(((rightMin[pLow])>pLow) && (rightMax[pLow]) <= pHigh)){
            root->key = -1;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
    }
    if ((leftMax[pLow] != -1) && (rightMin[pLow] != -1)){
        if (!(leftMax[pLow] < rightMin[pLow])) {

            root->key = -1;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
    }
    if ((pHigh == pLow) && (leftMax[pLow] == -1) && (rightMin[pLow] == -1)) {
        if (maxInserted == -3){
            maxInserted = pLow;
        } else {
            maxInserted = max(maxInserted, pLow); //cout << "max Ins " << maxInserted << endl;
        }
        root->key = pLow;
        root->left = nullptr;
        root->right = nullptr;
        return;
    }

    node* myleft = new node(-1);

    if (rightMin[pLow] == -1) {
        if (((pLow+1) <= pHigh) && ((pLow + 1) <= n) && (pHigh <=n)){
            buildTree(myleft, pLow + 1,pHigh);
        }
    } else {
        if (((pLow+1) <= rightMin[pLow] - 1) && ((pLow + 1) <= n) && (rightMin[pLow] - 1 <=n)) {
            buildTree(myleft, pLow + 1, rightMin[pLow] - 1);
        }
    }

    if (myleft->key == -1){
        maxInserted = pLow; //cout << "max Ins " << maxInserted << endl;
        if (leftMax[pLow] != -1) {
            root->key = -1;
            delete(myleft);
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
    }

    if (leftMax[pLow] != -1){
        if (maxInserted < leftMax[pLow]){
            maxInserted = pLow; //cout << "max Ins " << maxInserted << endl;
            delete(myleft);
            root->key = -1;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
    }

    int maxLeft = maxInserted;
    root->key = pLow; maxInserted = max(maxInserted, pLow); //cout << "max Ins " << maxInserted << endl;

    if (maxLeft == pHigh){
        root->key = pLow;
        root->left = myleft;
        root->right = nullptr;
        return;
    }

    node* myright = new node(-1);

    if (rightMin[pLow] == -1) {
        if (((maxInserted + 1) <= pHigh) && ((maxInserted + 1) <= n) && (pHigh <=n)) {
            //buildTree(myright, maxInserted + 1, pHigh);
        }
    } else {
        if (((maxInserted + 1) <= pHigh) && ((maxInserted + 1) <= n) && (pHigh <=n) && (rightMax[pLow]) <= pHigh) {
            buildTree(myright, maxInserted + 1, pHigh);
        }
    }

    if (myright->key == -1){
        maxInserted = maxLeft; //cout << "max Ins " << maxInserted << endl;
        if (rightMin[pLow] != -1){
            delete(myleft);
            delete(myright);
            root->key = -1;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
    }

    if (rightMin[pLow] != -1){
        if (maxInserted < rightMax[pLow]){
            maxInserted = pLow; //cout << "max Ins " << maxInserted << endl;
            delete(myleft);
            delete(myright);
            root->key = -1;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
    }

    if (pLow == 1){
        if (maxInserted != n){
            delete(myleft);
            delete(myright);
            root->key = -1;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
    }

    if ((myleft->key == -1) && (myright->key == -1)){
        if ((leftMax[pLow] != -1) || (rightMin[pLow]!= -1)){
            delete(myleft);
            delete(myright);
            root->key = -1;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
    }
    if (myleft->key != -1)
        root->left = myleft;
    else
        delete(myleft);

    if (myright->key != -1)
        root->right = myright;
    else
        delete(myright);

    //cout << "sad" << pLow << endl;
}

int main() {


    cin >> n >> c;

    bool poss = true;
    leftMax = new int [n+1];
    rightMin = new int [n+1];
    rightMax = new int [n+1];
    pre = new int[n];
    int a, b;
    string direction ;

    for (int i = 1; i <= n; i++){
        leftMax[i] = -1;
        rightMin[i] = -1;
    }

    for (int i = 0; i < c; i++){
        cin >> a >> b >> direction;
        if ((a >= b) | (a>n) | (b>n) | (a<1) | (b<1)){
            poss = false;
        }
        if (direction == "RIGHT"){
            if (rightMin[a] == -1){
                rightMin[a] = b; rightMax[a] = b;
            } else {
                rightMin[a] = min(b, rightMin[a]);  rightMax[a] = max(b, rightMax[a]);
            }
        }
        if (direction == "LEFT") {
            if (leftMax[a] == -1){
                leftMax[a] = b;
            } else {
                leftMax[a] = max(leftMax[a], b);
            }
        }
        if ((leftMax[a] != -1) && (rightMin[a] != -1)){
            if (leftMax[a] >= rightMin[a]){
                poss = false;
            }
        }
    }

    if (!poss){
        cout << "IMPOSSIBLE";
        return 0 ;
    } else {
        node *tree = new node(-1);
        buildTree(tree, 1, n);
        //cout << "build ended";
        if (tree->key == -1) {
            cout << "IMPOSSIBLE";
        } else {
            preorder(tree);
            if (len != n){
                    cout << "IMPOSSIBLE";
                    return 0;
            }
            
            inorder(tree);

        }
    }
}