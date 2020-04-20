#include <iostream>

using namespace std;

int main() {
    int a;
    long int b;
	long int np2;
    int nearlog2 = 0;
    int multResult1 = a;
    int multResult2 = 1;
	
    cin >> a;
    cin >> b;
    
    while (b > 1){
        nearlog2 = 0;
        for (np2 = 1; np2 <= b; np2 *= 2){
            nearlog2 ++;
        }
        b = (b - (np2 >> 1));
        multResult1 = a;
        for (int i = 1; i < nearlog2 ; i++) {
            multResult1 = (int) (((long)multResult1 * (long)multResult1) % (1000000007));

        }
        multResult2 = (int)(((long)multResult2 * (long)multResult1) % (1000000007));
    }

    if (b == 1)
        multResult2 = (int)(((long)multResult2 * (long)a) % (1000000007));

    cout << multResult2;

}