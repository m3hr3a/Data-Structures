#include <iostream>
#include <iterator>
#include <map>

using namespace std;

class interval {
public:
    int start;
    int end;
    bool last;

    interval(int s, int e, bool l) {
        this->start = s;
        this->end = e;
        this->last = l;
    }
};
int main(){
    /*ios_base::sync_with_stdio(false);
    cin.tie(NULL);*/
    map <int, interval*> intervals;
    map <int, interval*>::iterator i;
    int myInf = 2147483647;
    int k, m;
    intervals.insert(make_pair(-myInf, new interval(-1*myInf, 0, false)));
    intervals.insert(make_pair(0, new interval(0, myInf, true)));
    int input;
    int n;
    cin >> n;
    int* output = new int[n];
    for (int j = 0; j < n; j++) {
        cin >> input;
        i =  intervals.upper_bound(input);
        i--;
        if (i->second->last){
            output[j] =  i->second->start;
        } else {
            output[j] = i->second->end;
        }
        k = i->second->start;
        m = i->second->end;
        intervals.erase(k);
        intervals.insert(make_pair(k, new interval(k, input, false)));
        intervals.insert(make_pair(input, new interval(input, m, true)));
    }

    for (int p = 0; p < n; p++) {
        cout << output[p] << endl;
    }
}