#include <iostream>
#include <iterator>
#include <map>
#include <string>

using namespace std;

class data {
public:
    int height;
    int position;

    data(int p, int h) {
        this->height = h;
        this->position = p;
    }
};
int main(){

    map <int, data*> monsters;
    map <int, data*>::iterator i;
    map <int, data*> canSee;
    map <int, data*>::iterator j;

    int q;
    char query;
    int x, h;
    cin >> q;
    int l;
    int m = 0; int* out = new int[q];

    for (int k = 0; k < q; k++) {
        cin >> query;
        if (query == '+') {
            cin >> x >> h;
            if (monsters.empty()) {
                canSee.insert(make_pair(x, new data(x, h)));
            } else {
                i = canSee.upper_bound(x);
                if (i == canSee.begin()) {
                    canSee.insert(make_pair(x, new data(x, h)));
                    j = i;
                    while (j!= canSee.end() && j->second->height < h){
                        l = j->first;
                        j++;
                        canSee.erase(l);
                    }
                }
                else if (i == canSee.end()) {
                    j = i; j--;
                    if (h >= j->second->height){
                        canSee.insert(make_pair(x, new data(x, h)));
                    }
                } else {
                    j = i; j--;
                    if (h >= j->second->height){
                        canSee.insert(make_pair(x, new data(x, h)));
                        j = i;
                        while (j!= canSee.end() && j->second->height < h){
                            l = j->first;
                            j++;
                            canSee.erase(l);
                        }
                    }
                }
            }
            monsters.insert(make_pair(x, new data(x, h)));
        }
        if (query == '?') {
            cin >> x;
            if (monsters.find(x) != monsters.end()){
                if (canSee.find(x) != canSee.end()) {
                    out[m++] = 1;
                } else {
                    out[m++] = 2;
                }
            } else {
                out[m++] = 3;
            }
        }
    }


    for (int u = 0; u < m; u++){
        if (out[u] == 1){
            cout << "YES" << endl;
        }
        if (out[u] == 2){
            cout << "NO" << endl;
        }
        if (out[u] == 3){
            cout << "I'M SORRY TOQROL :(" << endl;
        }
    }
}