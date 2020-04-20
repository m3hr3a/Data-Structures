#include <iostream>
#include <set>
#include <math.h>
#include<bits/stdc++.h>

using namespace std;

int main () {

    string input;
    cin >> input;

    int m =  input.length();
    int t1, t2;
    auto* hash = new unsigned long long int[m];
    auto* powers = new unsigned long long int[m];
    long long unsigned int a, b, c, x;

    hash[0] = (unsigned  int) input[0] - 48;
    powers[0] = 1;
    for (int p = 11; p >= 10; p--) {
        for (int i = 1; i < m; i++) {
            hash[i] = (hash[i - 1] * p + (unsigned int) input[i] - 48);
            powers[i] = (p * powers[i - 1]);
        }

        for (int i = 1; i <= (int) ceil(m / 2); i++) {
            if (i < (int) floor(m / 3)) {
                t1 = (int) floor((m - i) / 2);
                t2 = m - t1 - i;
                a = hash[i - 1];
                b = (hash[i + t1 - 1] - a * powers[t1]);
                c = (hash[m - 1] - hash[i + t1 - 1] * powers[t2]);
                x = (a + b);
                if (x == c) {
                    cout << i << " " << t1 << " " << t2;
                    return 0;
                }
            } else {
                t2 = i;
                t1 = m - 2 * i;
                if (t1 > 0) {
                    a = hash[i - 1];
                    b = (hash[i + t1 - 1] - a * powers[t1]);
                    c = (hash[m - 1] - hash[i + t1 - 1] * powers[t2]);
                    x = a + b;
                    if (x == c) {
                        cout << i << " " << t1 << " " << t2;
                        return 0;
                    }
                }
                t2 = i + 1;
                t1 = m - 2 * i - 1;
                if (t1 > 0) {
                    a = hash[i - 1];
                    b = (hash[i + t1 - 1] - a * powers[t1]);
                    c = (hash[m - 1] - hash[i + t1 - 1] * powers[t2]);
                    x = (a + b);
                    if (x == c) {
                        cout << i << " " << t1 << " " << t2;
                        return 0;
                    }
                }
            }

        }
    }
}