
#include <iostream>
#include <vector>
#include <array>
#include <functional>

#include <stdint.h>

using namespace std;

template<typename t>
void merge(vector<t> &dst, vector<t> &left, vector<t> &right) {
    int i = 0, j = 0, k = 0;
    const int ndst = dst.size(), nleft = left.size(), nright = right.size();
    while (i < nleft && j < nright) {
        ( (left[i] <= right[j]) ? dst[k] = left[i++] : dst[k] = right[j++] );
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

long inversion_count(vector<long> v) {
    int count;

    return count;
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
    //cin >> t;

    /*
    while (t--) {
        vector<long> v = scanv();
        cout << inversion_count(v) << endl;
    }    
    */

    vector<long> v = { 2, 4, 1, 6, 8, 5, 9 };
    mergesort(v);

    cout << endl;
    return 0;
}
