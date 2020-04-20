#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    unsigned int n;
    cin >> n;
    int* a = new int[n+2];
    a[0] = -1;
    a[n+1] = -1;

     for (unsigned int i = 1; i <= n; i++)
         cin >> a[i];

    auto* stack1 = new int[n+1];
    auto* smaller = new int[n];
    auto* larger = new int[n];

     stack1[0] = 0;
     int s1Head = 0;
     int topVal1;


     for (unsigned int i = 1; i <= n; i++){
         topVal1 = stack1[s1Head];
         while (a[topVal1] >= a[i]){
             s1Head--;
             topVal1 = stack1[s1Head];
         }
         smaller[i-1] = topVal1;

         stack1[++s1Head] = i;
     }

     s1Head = 0;
     stack1[0] = n+1;

    for (unsigned int i = n; i >= 1; i--){
        topVal1 = stack1[s1Head];
        while (a[topVal1] >= a[i]){
            s1Head--;
            topVal1 = stack1[s1Head];
        }
        if (topVal1 == n+1)
            larger[i-1] = 0;
        else
            larger[i-1] = topVal1;

        stack1[++s1Head] =i;
    }
    for (int i = 0; i < n; i++)
        cout << smaller[i] << " " << larger[i] <<"\n";

}