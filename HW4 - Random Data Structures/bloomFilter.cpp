#include <iostream>
#include <bitset>

using  namespace std;

inline int g(int i, int x, int m) {
    int h1 = x % m;
    if (h1 < 0) {
        h1 = h1 + m;
    }
    int h2 = x % (m - 1);
    if (h2 < 0) {
        h2 = h2 + m - 1;
    }
    h2 = 1 + h2;
    int g = (h1 + i * h2) % m;
    if (g < 0) {
        g = g + m;
    }
    return g;
}

inline int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}
int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q, k, m, func, x;
    int gMin = 1000000007, currG;
    bool isThere = true;
    cin >> q >> m >> k;
    bitset<100000000> table;
    /*for (int i = 0; i < m; i++) {
        table[i] = false;
    }*/
    auto* out = new string[q];

    for (int i = 0; i < q; i++) {
        cin >> func >> x;
        if (func == 1) {
            for (int j = 0; j < k; j++) {
                currG = g(j, x, m);
                if (table[currG] == false) {
                    table[currG] = true;
                    gMin = min(gMin, currG);
                }
            }
            if (gMin != 1000000007){
                out[i] = to_string(gMin);
                gMin = 1000000007;
            } else {
                out[i] = "-1";
            }

        }
        if (func == 2) {
            for (int j = 0; j < k; j++) {
                currG = g(j, x, m);
                isThere = isThere & table[currG];
                if (!isThere) {
                    break;
                }
            }
            if (isThere) {
                out[i] = "Y";
            } else {
                out[i] = "N";
            }
            isThere = true;
        }
    }

    for (int i = 0; i < q; i++) {
        cout << out[i] << endl;
    }

}