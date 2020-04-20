#include <iostream>
#include "cmath"

using namespace std;

int parent(int i){
    return floor((i - 1)/2);
}

int left(int i){
    return 2 * i + 1;
}

int right(int i){
    return 2 * i + 2;
}

void exchange(int* heap, int i, int j){
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void insertMax(int* heap, int x, int hSize){
    hSize++;
    heap[hSize] = x;
    int i = hSize;
    while (parent(i) >= 0 and heap[i] > heap[parent(i)]){
        exchange(heap, i, parent(i));
        i = parent(i);
    }
}

void insertMin(int* heap, int x, int hSize){
    hSize++;
    heap[hSize] = x;
    int i = hSize;
    while (parent(i) >= 0 and heap[i] < heap[parent(i)]){

        exchange(heap, i, parent(i));
        i = parent(i);
    }
}

int extractMax(int* heap, int hSize){
    int maxVal = heap[0];
    int l , r, max;
    heap[0] = heap[hSize];
    hSize--;
    int i = 0;
    while (left(i) <= hSize){
        l = left(i);
        r = right(i);
        max = i;
        if(heap[l] > heap[max])
            max = l;
        if (heap[r] > heap[max] & r <= hSize)
            max = r;
        if (max != i){
            exchange(heap, i, max);
            i = max;
        }
        else
            break;
    }
    return maxVal;
}

int extractMin(int* heap, int hSize){
    int minVal = heap[0];
    int l , r, min;
    heap[0] = heap[hSize];
    hSize--;
    int i = 0;
    while (left(i) <= hSize){
        l = left(i);
        r = right(i);
        min = i;
        if(heap[l] < heap[min])
            min = l;
        if (heap[r] < heap[min] & r <= hSize)
            min = r;
        if (min != i){
            exchange(heap, i, min);
            i = min;
        }
        else
            break;
    }
    return minVal;
}

int main() {
    unsigned int n;
    int hSize1 = -1;
    int hSize2 = -1;

    int func, x, m1, m2;
    unsigned int nx = 1,nm = 0;
    int currentMed;

    cin >> n;
    int* median= new int[n];
    int* heap1 = new int [n];
    int* heap2 = new int [n];

    cin >> func >> x;

    insertMax(heap1, x, hSize1);
    hSize1++;

    for (int i = 1; i < n; i++){
        cin >> func;
        if (func == 1) {
            if (hSize1 >= hSize2) {
                currentMed = heap1[0];
            }
            else if (hSize2 > hSize1) {
                currentMed = heap2[0];
            }
            cin >> x;

            if (x >= currentMed) {
                insertMin(heap2, x, hSize2);
                hSize2++;
                if (hSize2 - hSize1 > 1) {
                    m1 = extractMin(heap2, hSize2);
                    hSize2--;
                    insertMax(heap1, m1, hSize1);
                    hSize1++;
                }
            } else {
                insertMax(heap1, x, hSize1);
                hSize1++;
                if (hSize1 - hSize2 > 1) {
                    m2 = extractMax(heap1, hSize1);
                    hSize1--;
                    insertMin(heap2, m2, hSize2);
                    hSize2++;
                }
            }

        } else {
            if (hSize1 >= hSize2) {
                median[nm] = extractMax(heap1, hSize1);
                hSize1--;
                nm++;
            }
            else if (hSize2 > hSize1) {
                median[nm] = extractMin(heap2, hSize2);
                hSize2--;
                nm++;
            }
        }
    }

    for (int i = 0; i < nm; i++)
        cout << median[i] << endl;
}