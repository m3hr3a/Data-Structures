#include <iostream>
#include <math.h>
unsigned int* A;
unsigned int z, bmid , bmidp1, bmidm1;
using namespace std;

int findPeak(int start, int end, int n) {
    int mid = floor(((double) start + (double) end) / 2);
    //  cout << mid;
    z = 1;
    for (int j = 0; j < n; j++) {

        if (mid != j) {
            //cout << j;
            z = (unsigned int) (((unsigned long) z * (unsigned long) A[j]) % A[mid]);
        }
    }

    bmid = z;
    if (mid != n - 1) {
        z = 1;
        // cout << bmid;
        for (int j = 0; j < n; j++) {
            if ((mid + 1) != j) {
                z = (unsigned int) (((unsigned long) z * (unsigned long) A[j]) % A[mid + 1]);
            }
        }
        bmidp1 = z;
    }
    else {
        bmidp1 = 0;
    }
    if(mid != 0) {
        z = 1;

        for (int j = 0; j < n; j++) {
            if ((mid - 1) != j) {
                z = (unsigned int) (((unsigned long) z * (unsigned long) A[j]) % A[mid - 1]);
            }
        }
        bmidm1 = z;
    }
    else {
        bmidm1 = 0;
    }
    if ((bmid> bmidp1) && (bmid> bmidm1)) {
        return mid;
    }
    else if (bmid < bmidp1){
        if (mid == (n - 2))
            return (n - 1);
        return findPeak(mid + 1, end, n);
    }
    else {
        if (mid == 0)
            return 0;
        return findPeak(start, mid - 1, n);
    }
}

int main() {
    unsigned int n;

    cin>>n;
    A = new unsigned int[n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    cout << findPeak(0, n-1, n) + 1;
}

