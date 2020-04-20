#include <iostream>
using namespace std;



int main() {
    unsigned int n;
    int k;
    cin >> n >> k;

    auto* value = new unsigned int[n + 1];
    auto* next = new unsigned int[n + 1];
    auto* previous = new unsigned int[n + 1];

    value[1] = 1;
    value[n] = n;
    next[1]  = 2;
    next[n] = 1;
    previous[1] = n;
    previous[n] = n - 1;

    for (unsigned int i = 2; i <= n - 1; i++){
        value[i] = i;
        next[i] = i + 1;
        previous[i] = i - 1;
    }
    int current = 1;
    int destination;

    for (unsigned int deleteRound = 1; deleteRound < n; deleteRound++){
        if (k >= 0) {
            for (int i = 1; i <= k; i++) {
                current = next[current];
            }
        }
        if (k < 0){
            k = -k;
            for (int i = 1; i <= k; i++) {
                current = previous[current];
            }
        }
        next[previous[current]] = next[current];
        previous[next[current]] = previous[current];

        current = next[current];

        if(current % 2 == 0){
            k = -k;
        }

    }

    cout << current;
}