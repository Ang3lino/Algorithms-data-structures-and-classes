// Angel Lopez Manriquez

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include <stdint.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

typedef pair<int64_t, int64_t> int_pair;
typedef pair<double, double> double_pair;

inline double dist(const double_pair p, const double_pair q) { 
    return hypot(abs(p.first - q.first), abs(p.second - q.second)); 
}

inline bool is_close(double x, double y) { return abs(x - y) <= DBL_EPSILON; }

int cmp_x_axis(const double_pair p, const double_pair q) {
    if (is_close(p.first, q.first)) return 0;
    return p.first - q.first; 
}

int cmp_y_axis(const double_pair p, const double_pair q) {
    if (is_close(p.second, q.second)) return 0;
    return p.second - q.second; 
}

double min_dist_brute_force(const vector<double_pair> &pairs) {
    double min = DBL_MAX;
    const int n = pairs.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            const double d = dist(pairs[i], pairs[j]);
            if (d < min) min = d;
        }
    }
    return min;
}

template<typename T> // low < high, sub = v[low, high]
vector<T> slice_vector(const vector<T> &src, const int &low, const int &high) {
    const int len = high - low;
    vector<T> sub(len);
    memcpy(&sub[0], &src[low], len * sizeof(T));
    return sub;
}

double min_middle(const vector<double_pair> &xsorted, const vector<double_pair> &ysorted, 
        const double offset, const double d) {

    double min = DBL_MAX;
    vector<double_pair> center_pairs;
    auto in_limit = [&](const double_pair p) { return abs(p.first) <= offset + d; };
    copy_if(xsorted.begin(), xsorted.end(), center_pairs.begin(), in_limit); // TODO

    for (int j = 0; j < ysorted.size() - 1; ++j) {
        if (abs(center_pairs[j].first - center_pairs[j].second) < d) {
            double curr_dist = dist(center_pairs[j], center_pairs[j + 1]);
            if (curr_dist < min) min = curr_dist;
        }
    }

    return min;
}

// always returns a positive value
double min_dist(const vector<double_pair> &xsort, const vector<double_pair> &ysort) {
    const int n = xsort.size();
    if (n <= 3) return min_dist_brute_force(xsort);
    const double_pair mid_pair = xsort[n / 2];

    vector <double_pair> left;
    vector <double_pair> right;

    for (auto &p: xsort) {
        if (p.first <= mid_pair.first) left.push_back(p);
        if (mid_pair.first <= p.first) right.push_back(p);
    }

    const double min_left = min_dist(left, ysort), min_right = min_dist(right, ysort);
    const double min_sides = min(min_left, min_right);
    const double min_mid = min_middle(xsort, ysort, mid_pair.first, min_sides);

    return min(min_sides, min_mid);
}

double min_dist(const vector<double_pair> &pairs) {
    const int n = pairs.size();
    const vector<double_pair> xsorted(n);
    const vector<double_pair> ysorted(n);
    
    sort(xsorted.begin(), xsorted.end(), cmp_x_axis);
    sort(ysorted.begin(), ysorted.end(), cmp_y_axis);
    
    return min_dist(xsorted, ysorted);
}

void print_pairs(const vector<double_pair> &pairs) {
    for (auto &p: pairs) cout << p.first << ", " <<  p.second << endl;
}

int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
    vector<double_pair> pairs(n);
    for (int i = 0; i < n; ++i) {
        cin >> pairs[i].first >> pairs[i].second;
    }
    print_pairs(pairs);
    cout << min_dist_brute_force(pairs);
    cout << endl;
    return 0;
}
