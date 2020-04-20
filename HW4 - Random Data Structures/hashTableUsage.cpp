#include <iostream>
#include <set>
#include <time.h>

using namespace std;

int main () {

    srand (time(NULL));

    int m, n, a, b;

    cin >> n >> m;

    auto* G = new set<int, greater<int>>[n];
    auto* GP = new set<int, greater<int>>[n];
    int* out1 = new int[m];
    int* out2 = new int[m];

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        G[b-1].insert(a-1);
        G[a-1].insert(b-1);
    }

    int start = 0;
    int inserted = 0;
    int dist;

    while (inserted != m) {
        dist = rand() % n;
        if (dist != start) {
            if ((GP[dist].size() < 1) || (inserted == m-1 && GP[dist].size() == 1)) {
                if (GP[dist].find(start) == GP[dist].end() && G[dist].find(start) == G[dist].end()) {
                    out1[inserted] = start+1;
                    out2[inserted] = dist+1;
                    GP[dist].insert(start);
                    GP[start].insert(dist);
                    start = dist;
                    inserted++;
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        cout << out1[i] << " " << out2[i] << endl;
    }

}