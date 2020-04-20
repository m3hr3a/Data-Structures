#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
bool *visited = new bool[26];
bool *stack = new bool[26];

inline int index(char x){
    return (int) x - 97;
}

bool haveCycle(int v, list<int> p[]) // used DFS Algorithm 
{
    if(!visited[v])
    {
        visited[v] = true;
        stack[v] = true;

        list<int>::iterator i;
        for(i = p[v].begin(); i != p[v].end(); ++i)
        {
            if (!visited[*i] && haveCycle(*i, p))
                return true;
            else if (stack[*i])
                return true;
        }

    }
    stack[v] = false;
    return false;
}

class trie {
public:
    trie* child[27];

    trie(){
        for (int i = 0; i < 27; i++){
            this->child[i] = nullptr;
        }
    }

    void insert(string word){
        trie* curr = this;
        for (int i = 0; i < word.length(); i++){
            if (curr->child[index(word[i])] == nullptr){
                curr->child[index(word[i])] = new trie();
            }
            curr = curr->child[index((word[i]))];
        }
        curr->child[26] = new trie;
    }

    bool canBeFirst(string word){
        if (word.length() == 1){
            return true;
        }

        list<int> priority[26];

        trie* curr = this;

        for (int j = 0; j < word.length(); j++){
            if (curr->child[26] != nullptr){
                return false;
            }
            for (int i = 0; i < 26 ; i++) {
                if (i != index(word[j])) {
                    if (curr->child[i] != nullptr) {
                        priority[index(word[j])].push_back(i);
                        priority[index(word[j])].unique();
                    }
                }
            }
            curr= curr->child[index((word[j]))];
        }

        for(int i = 0; i < 26; i++)
        {
            visited[i] = false;
            stack[i] = false;
        }
        for(int i = 0; i < 26; i++) {
            if (haveCycle(i, priority))
                return false;
        }

        return true;
    }
};

int main() {
    int n;
    trie* myTrie = new trie;
    cin >> n;
    auto* words = new string[n];
    vector<string> accepted;
    for (int i = 0; i < n; i++){
        cin >> words[i];
        myTrie->insert(words[i]);
    }
    int k = 0;
    for (int i = 0; i < n; i++){
        if (myTrie->canBeFirst(words[i])){
            accepted.push_back(words[i]); k++;
        }
    }
    cout << k << endl;
    sort(accepted.begin(), accepted.end());
    for (int i = 0; i < k; i++){
        cout << accepted[i] << endl;
    }
}