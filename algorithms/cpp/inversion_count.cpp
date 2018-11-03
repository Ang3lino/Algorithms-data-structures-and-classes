
#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <stack>

#include <stdint.h>

using namespace std;

long inversion_count;

template<typename t>
void merge(vector<t> &dst, vector<t> &left, vector<t> &right) {
    int i = 0, j = 0, k = 0;
    const int nleft = left.size(), nright = right.size();
    while (i < nleft && j < nright) {
        if (left[i] <= right[j]) dst[k] = left[i++];
        else {
            dst[k] = right[j++];
            ++inversion_count;
        }
        ++k;
    }
    while (i < nleft) {
        dst[k] = left[i++];
        ++k;
    }
    while (j < nright) {
        dst[k] = right[j++];
        ++k;
    }
}

// v = { 2, 4, 1, 6, 8, 5, 3, 7 };
//       0  1  2  3  4  5  6  7  8
// v = { 2, 4, 1, 6, 8, 5, 3, 7, 9 };

template<typename t>
void mergesort(vector<t> &v) {
    const int n = v.size();
    if (n < 2) return;

    int mid = n / 2;

    // split the vector in two halves
    vector<t> left(v.begin(), v.begin() + mid), right(v.begin() + mid, v.end());    

    mergesort(left);
    mergesort(right);
    merge(v, left, right);

}

vector<long> scanv() {
    int n;
    cin >> n;
    vector<long> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    return v;
}

int main(int argc, char const *argv[])
{
    int t;
    
    cin >> t;
    vector<long> counts;
    while (t--) {
        vector<long> v = scanv();
        inversion_count = 0;
        mergesort(v);
        counts.push_back(inversion_count);
    }    
    //vector<long> v = { 2, 4, 1, 6, 8, 5, 9 };
    cout << endl;
    for (auto &l: counts) cout << l << endl;
    cout << endl;
    return 0;

}
