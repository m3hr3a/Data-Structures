#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m , r;
    long temp1, temp2 = 0;
    int wCol, wRow;

    cin >> n >> m >> r;

    auto* A = new long [n * m];
    auto* B = new long [m * r];
    auto* C = new long [n * r];

    for (int row = 0; row < n; row++)
        for (int col = 0; col < m; col++)
            cin >> A[row * m + col];

    for (int row = 0; row < m; row++)
        for (int col = 0; col < r; col++)
            cin >> B[row * r + col];

    for (int row = 0; row < n; row++)
        for (int col = 0; col < r; col++)
            cin >> C[row * r + col];

    int* sigmaA = new int [m];
    int* sigmaB = new int [m];

    for (int i = 0; i < m ; i++) {
        sigmaA[i] = 0;
        sigmaB[i] = 0;
    }

    for (int row = 0; row < n; row++)
        for (int i = 0; i < m ; i++)
            sigmaA[i] = sigmaA[i] + A[row * m + i];

    for (int col = 0; col < r; col++)
        for (int i = 0; i < m ; i++)
            sigmaB[i] = sigmaB[i] + B[i * r + col];

    for (int row = 0; row < n; row ++){
        temp1 = 0;
        temp2 = 0;
        for  (int k = 0; k < m; k++){
            temp1 = temp1 + sigmaB[k] * A[row * m+ k];
        }
        for (int k = 0; k < r; k++)
            temp2 = temp2 + C[row * r + k];

        if (temp2 != temp1) {
            cout << row + 1 << " ";
            break;
        }
    }

    for (int col = 0; col < r; col++){
        temp1 = 0;
        temp2 = 0;
        for  (int k = 0; k < m; k++){
            temp1 = temp1 + sigmaA[k] * B[k * r+ col];
        }
        for (int k = 0; k < n; k++)
            temp2 = temp2 + C[k * r + col];
        
        if (temp2 != temp1) {
            cout << col + 1;
            break;
        }
    }



}