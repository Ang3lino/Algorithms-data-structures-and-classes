// Angel Lopez Manriquez

#include <iostream>
#include <vector>

#include <math.h>
#include <stdint.h>

using namespace std;

// 3 -2 8 1 10
int64_t max_subarr_between(const vector<int64_t> &v, const long l, const long r, 
        const long mid) {
    int64_t leftSum = INTMAX_MIN;
    int64_t rightSum = INTMAX_MIN;
    int64_t sum = 0;

    for (int i = mid; i >= l; --i) {
        sum += v[i];
        if (sum > leftSum) leftSum = sum;
    }

    sum = 0;
    for (int i = mid + 1; i <= r; ++i) {
        sum += v[i];
        if (sum > rightSum) rightSum = sum;
    }

    return leftSum + rightSum;
}

int64_t max_subarr_subseq(const vector<int64_t> &v, const long l, const long r) {
    if (l == r) {
        //cout << l << endl;
        return v[l];
    }
    //cout << l << ", " << r << endl;
    const long mid = (r - l) / 2 + l;
    const int64_t leftSum = max_subarr_subseq(v, l, mid);
    const int64_t rightSum = max_subarr_subseq(v, mid + 1, r);
    const int64_t midSum = max_subarr_between(v, l, r, mid);
    return max(leftSum, max(rightSum, midSum));
}

inline int64_t max_subarr_subseq(vector<int64_t> &v) {
    return max_subarr_subseq(v, 0, v.size() - 1);
}

vector<int64_t> fillVec() {
    long n;
    cin >> n;
    vector<int64_t> v(n); // allocate a vector with n elements
    for (int i = 0; i < n; ++i) cin >> v[i];
    return v;
}

int main(void) {
    // test
    //vector<int64_t> v = {2, -5, 8, 6, -2, 5};
    //vector<int64_t> v = {1, -3, 2, -5, 7, 6, -1, -4, 11, -23};
    
    vector<int64_t> v = fillVec();

    int64_t ans = max_subarr_subseq(v);
    cout << ans;
    return 0;
}
