#include <iostream>
#include <string.h>
#include<bits/stdc++.h>
#include <map>

using namespace std;

inline int index(char w) {
    return (int) w - 97;
}

class trie {
public:
    trie* children[3];

    trie() {
        for (int i = 0; i < 3; i++) {
            this->children[i] = nullptr;
        }
    }

    void insert(string word){
        trie* curr = this;
        for (int i = 0; i < word.length(); i++){
            if (curr->children[index(word[i])] == nullptr){
                curr->children[index(word[i])] = new trie();
            }
            curr = curr->children[index((word[i]))];
        }
    }

    trie* search(string word) {

        trie* curr = this;
        int l = 0;
        for (int i = 0; i < word.length(); i++){
            if (curr->children[index(word[i])] != nullptr){
                curr = curr->children[index((word[i]))];
                l++;
            } else {
                break;
            }
        }

        if (l == word.length()) {
            return curr;
        } else {
            return nullptr;
        }

    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    map <string, string> BST;
    trie* myTrie = new trie();
    trie* reverseTrie = new trie;
    string str, revStr;

    int m, n;
    cin >> n >> m;
    string* out = new string[m];

    for (int i = 0; i < n; i++) {
        cin >> str;
        revStr = str;
        myTrie->insert(str);
        reverse(revStr.begin(), revStr.end());
        reverseTrie->insert(revStr);
        BST.insert(make_pair(str, str));
    }

    trie* p;
    trie* s;
    string temp;
    bool poss = false;

    for (int i = 0; i < m; i++) {
        cin >> str;
        revStr = str;
        reverse(revStr.begin(), revStr.end());
        for (int j = 0; j < str.length(); j++) {
            p = myTrie->search(str.substr(0, j));
            if (p != nullptr) {
                s = reverseTrie->search(revStr.substr(0, str.length() - j - 1));
                if (s != nullptr) {
                    if (s->children[0] != nullptr) {
                        temp = str.substr(0,j) + "a" + str.substr(j+1, str.length() - j - 1);
                        if (temp != str && BST.find(temp) != BST.end()){
                            poss = true;
                            break;
                        }
                    }
                    if (s->children[1] != nullptr) {
                        temp = str.substr(0,j) + "b" + str.substr(j+1, str.length() - j - 1);
                        if (temp != str && BST.find(temp) != BST.end()){
                            poss = true;
                            break;
                        }
                    }
                    if (s->children[2] != nullptr) {
                        temp = str.substr(0,j) + "c" + str.substr(j+1, str.length() - j - 1);
                        if (temp != str && BST.find(temp) != BST.end()){
                            poss = true;
                            break;
                        }
                    }
                }
            }
        }

        if (poss) {
            out[i] = "YES";
        } else {
            out[i] = "NO";
        }

        poss = false;
    }

    for (int i = 0; i < m; i++){
        cout << out[i] << endl;
    }
}