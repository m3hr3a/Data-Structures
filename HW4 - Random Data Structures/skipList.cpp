#include <iostream>

using namespace std;

class node {
public:
    int key;
    int level;
    node* next;
    node * up;
    node* down;

    node(int val, int l){
        this->key = val;
        this->level = l;
        this->next = nullptr;
        this->down = nullptr;
        this->up = nullptr;
    }
};


class skipList {
public:
    int maxL = 1;
    node* sential = new node(-1000000007, 1) ;

     void insert(int val, int l) {
         int r = l - maxL;
         for (int i = 0; i < r; i++) {
             if (sential->up == nullptr) {
                 sential->up = new node(-1000000007, maxL + 1);
                 sential->up->down = sential;
                 sential = sential->up; maxL++;
             }
         }

         node* currS = sential;
         node* temp;
         for (int i = 0; i < maxL - l; i++) {
             currS = currS->down;
         }

         node* nodes[l];
         for (int i = 0; i < l; i++) {
             nodes[i] = new node(val, i);
         }

         for (int i = 1; i < l; i++) {
             nodes[i]->down = nodes[i - 1];
         }

         while (true) {
             if (currS->next == nullptr) {
                 currS->next = nodes[l-1];
                 currS = currS->down; l--;
             } else {
                 if (currS->next->key > val) {
                     temp = currS->next;
                     currS->next = nodes[l-1];
                     currS->next->next = temp;
                     currS = currS->down; l--;
                 } else {
                     currS = currS->next;
                 }
             }

             if (l == 0) {
                 break;
             }
         }
     }

    int search(int val) {
         int pathLength = 0;
         int l = maxL;
         node * curr = sential;

         while (true) {
             if (curr->key == val) {
                 return pathLength + l - 1;
             }
             if (curr->next != nullptr) {
                 if (curr->next->key > val) {
                     pathLength++;
                     if (curr->down != nullptr) {
                         curr = curr->down; l--;
                     }
                     else {
                         return -1;
                     }
                 } else {
                     pathLength++;
                     curr = curr->next;
                 }
             } else {
                 if (curr->down != nullptr) {
                     curr = curr->down; l--; pathLength++;
                 }
                 else {
                     return -1;
                 }
             }
         }
     }


    void remove(int val) {

         node* temp;

         while (sential->next!= nullptr && sential->next->key == val && sential->next->next == nullptr) {
             if (sential->down == nullptr) {
                 break;
             }
             sential = sential->down;
             sential->up = nullptr;
             maxL--;
         }

         node* curr = sential;
         while (true) {
             if (curr->next != nullptr) {
                 if (curr->next->key == val) {
                     curr->next = curr->next->next;
                     curr = curr->down;
                 } else {
                     if (curr->next->key > val) {
                         curr = curr->down;
                     }
                     if (curr->next->key < val) {
                         curr = curr->next;
                     }
                 }
             } else {
                 curr = curr->down;
             }
             if (curr == nullptr) {
                 return;
             }
         }
    }
};
int main() {
    skipList sList;
    int q, func, x, level;
    cin >> q;
    int k = 0;
    int* out = new int[q];

    for (int i = 0; i < q; i++) {
        cin >> func;
        if (func == 2) {
            cin >> x >> level;
            sList.insert(x, level);
        }
        if (func == 1) {
            cin >> x;
            sList.remove(x);
        }
        if (func == 3) {
            cin >> x;
            out[k++] = sList.search(x);
        }
    }

    for (int i = 0; i < k; i++) {
        cout << out[i] << endl;
    }
}