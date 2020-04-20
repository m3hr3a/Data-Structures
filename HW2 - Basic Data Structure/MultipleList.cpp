#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int* mQueue = new int[n*n];
    int * endQ = new int[n];
    int * startQ = new int[n];
    int* enterQ = new int [n];
    bool* full = new bool[n];

    int m = 0;
    mQueue[0] = a[0];
    endQ[0] = 0;
    enterQ[0] = 0;
    int inserted = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= m; j++){
            if(a[i] >= mQueue[endQ[j] + j * n]) {
                mQueue[endQ[j] + 1 +j * n] = a[i];
                endQ[j]++;
                inserted = 1;
                enterQ[i] = j;
                break;
            }
        }
        if (inserted == 0){
            m= m + 1;
            mQueue[m*n] = a[i];
            endQ[m] = 0;
            enterQ[i] = m;
        }
        inserted = 0;
    }

    for(int i = 0; i <=m; i++){
        full[i] = true;
    }

   /* for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= endQ[i]; j++) {
            cout << mQueue[j + i * n] << " ";
        }
        cout << '\n';
    }*/

    for (int i = 0; i <=m; i++)
        startQ[i] = 0;
    cout<< m+1 << " " << 2 * n << endl;
    int minExit;
    int exitIndex;
    for (int i = 0; i < n; i++)
        cout << 1 << " " << enterQ[i]+1 << endl;
    int j;
    for (int i = 0; i < n; i++){
        for (j = 0; j <= m; j++){
            if (full[j]) {
                minExit = mQueue[j * n + startQ[j]];
                exitIndex = j;
                break;
            }
        }
        for (int k = j+1; k<= m; k++){
            if (full[k]){
                if (minExit > mQueue[k * n + startQ[k]]){
                    minExit = mQueue[k * n + startQ[k]];
                    exitIndex = k;
                }
            }
        }
        cout << 2 << " " << exitIndex + 1 << endl;
        startQ[exitIndex]++;
        if(startQ[exitIndex] > endQ[exitIndex])
            full[exitIndex] = false;
    }

}