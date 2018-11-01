
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
    for (int i = mid; i <= r; ++i) {
        sum += v[i];
        if (sum > rightSum) rightSum = sum;
    }

    return leftSum + rightSum;
}

int64_t max_subarr_subseq(const vector<int64_t> &v, const long l, const long r) {
    if (abs(r - l) == 1) return v[l];
    //cout << l << r << endl;
    const long mid = (r - l) / 2 + l;
    const int64_t leftSum = max_subarr_subseq(v, l, mid - 1);
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
    vector<int64_t> v;
    int64_t data;
    for (int i = 0; i < n; ++i) {
        cin >> data;
        v.push_back(data);
    }
    return v;
}

int main(void) {
    vector<int64_t> v = {2, -5, 8, 6, -2, 5};

    int64_t ans = max_subarr_subseq(v);
    cout << ans;
    return 0;
}
