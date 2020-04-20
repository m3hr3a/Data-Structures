#include <iostream>
#include <bitset>
using namespace std;

class trie {
public:
    trie* child[2];

    trie(){
        for (int i = 0; i < 2; i++){
            this->child[i] = nullptr;
        }
    }

    void insert(bitset<32> x){
        trie* curr = this;

        for (int i = 31; i >= 0; i--){
            if (curr->child[x[i]] == nullptr){
                curr->child[x[i]] = new trie();
            }
            curr = curr->child[x[i]];
        }
    }
    int giveMax(bitset<32> x){

        trie* curr = this;
        int max = 0;
        for (int i = 31; i >= 0; i--){
            if (curr->child[1-x[i]] != nullptr){
                max = (1<<i) + max;
                curr = curr->child[1-x[i]];
            } else
                curr = curr->child[x[i]];
        }
        return max;
    }
};

int main() {


    int q;
    int length = 0;
    cin >> q;
    int* out = new int[q];
    int f;
    unsigned int x;
    bitset<32> xVal = bitset<32> (0);
    bitset<32> bx;
    trie* myTrie = new trie;
    myTrie->insert(bitset<32> (0));
    for (int i = 0; i < q; i++){
        cin >> f;
        if (f == 3) {
            out[length] = myTrie->giveMax(xVal); length++;
        }
        else {
            cin >> x;
            bx  = bitset<32> (x);
            if (f == 1)
                myTrie->insert(bx ^ xVal);
            else {
                xVal = bx ^ xVal;
            }
        }
    }

    for (int i = 0; i < length; i++){
        cout << out[i] << endl;
    }
}