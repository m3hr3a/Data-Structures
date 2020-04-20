#include <iostream>

using namespace std;

int main() {

    int t;
    int nearLog2 = 0;
    long sum;
    long P = 1000000007;

    long long int np2;
    long long int n;

    cin >> n;
    cin >> t;

    long long int nPrime = n -  (long long)t + 1;
    long long int a, b, MULTab;

    for (np2 = 1; np2 <= nPrime; np2 *= 2) {
        nearLog2++;
    }

    if (nearLog2 == 0)
        nearLog2 = 1;

    long* A = new long[(t + 1) * (t + 1) * (nearLog2)];
    long* f = new long[t + 1];
    long* finalMat = new long [(t + 1) * (t + 1)];
    long* tempMat = new long [(t + 1) * (t + 1)];


    for (int i = 0; i <= t; i++)
        cin >> A[(t - 1) * (t + 1) + t - i];

    for (int i = 0; i < t; i++)
        cin >> f[i];

    f[t] = 1;

    if (n < t){
        cout << f[n];
        return 0;
    }

    for (int i = 0; i < t; i++)
        A[(t) * (t + 1) + t - i - 1] = 0;

    A[t * (t + 1) + t] = 1;

    for (int row = 0; row < (t - 1); row++)
        for (int col = 0; col < (t + 1); col++)
            if ((row  + 1)== col)
                A[row * (t + 1) + col] = 1;
            else
                A[row * (t + 1) + col] = 0;

    for (int row = 0; row < (t + 1); row++) {
        for (int col = 0; col < (t + 1); col++) {
            if (col == row)
                finalMat[row * (t + 1) + col] = 1;
            else
                finalMat[row * (t + 1) + col] = 0;
        }
    }

    for (int matNum = 1; matNum < nearLog2; matNum++) {
        for (int row = 0; row < (t + 1); row++) {
            for (int col = 0; col < (t + 1); col++) {
                sum = 0;
                for (int k = 0; k < (t + 1); k++)
                    if (A[(matNum - 1) * (t + 1) * (t + 1) + row * (t + 1) + k] !=0 |
                        A[(matNum - 1) * (t + 1) * (t + 1) + k * (t + 1) + col] != 0) {
                        a = ((long long) (A[(matNum - 1) * (t + 1) * (t + 1) + row * (t + 1) + k] % P));
                        b = ((long long) (A[(matNum - 1) * (t + 1) * (t + 1) + k * (t + 1) + col] % P));
                        MULTab = (a * b) % P;
                        sum = (long) ((((long long)(sum % P)) + MULTab) % P);
                    }
                A[matNum * (t + 1) * (t + 1) + row * (t + 1) + col] = sum % P;
            }
        }
    }

    while (nPrime >= 1){

        nearLog2 = 0;
        for (np2 = 1; np2 <= nPrime; np2 *= 2){
            nearLog2 ++;
        }

        nPrime = (nPrime - (np2 >> 1));

        for (int row = 0; row < (t + 1); row++) {
            for (int col = 0; col < (t + 1); col++) {
                sum = 0;
                for (int k = 0; k < (t + 1); k++)
                    if (A[(nearLog2 - 1) * (t + 1) * (t + 1) + k * (t + 1) + col] != 0 |
                        finalMat[row * (t + 1) + k] != 0) {
                        a = ((long long) (finalMat[row * (t + 1) + k] % P));
                        b = ((long long) (A[(nearLog2 - 1) * (t + 1) * (t + 1) + k * (t + 1) + col] % P));
                        MULTab = (a * b) % P;
                        sum = (long) ((((long long)(sum % P)) + MULTab) % P);
                    }
                tempMat[row * (t + 1) + col] = sum % P;
            }
        }
        for (int row = 0; row < (t + 1); row++) {
            for (int col = 0; col < (t + 1); col++) {
                finalMat[row * (t + 1) + col] = tempMat[row * (t + 1) + col] % P;
            }
        }
    }
    
    sum = 0;
    for (int i = 0; i < (t + 1); i++){
        a = ((long long) (f[i] % P));
        b = ((long long) (finalMat[(t + 1) * (t - 1) + i]  % P));
        MULTab = (a * b) % P;
        sum = (long) ((((long long)(sum % P)) + MULTab) % P);
    }

    if (sum >= 0)
        cout << sum;
    else
        cout << sum + P;

}