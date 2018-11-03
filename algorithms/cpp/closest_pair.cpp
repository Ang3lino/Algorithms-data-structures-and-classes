// Angel Lopez Manriquez

#include <iostream>
#include <vector>
#include <algorithm> 
#include <functional> // copy_if
#include <iomanip> // fixed, setprecision

#include <stdint.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

typedef pair<double, double> double_pair;

template<typename T> // low < high, sub = v[low, high]
vector<T> slice_vector(const vector<T> &src, const int &low, const int &high) {
    const int len = high - low;
    vector<T> sub(len);
    memcpy(&sub[0], &src[low], len * sizeof(T));
    return sub;
}
inline bool is_close(double x, double y) { return abs(x - y) <= DBL_EPSILON; }

inline double dist(const double_pair p, const double_pair q) { 
    return hypot((p.first - q.first), (p.second - q.second)); 
}


int cmp_x_axis(const double_pair &p, const double_pair &q) {
    if (is_close(p.first, q.first)) return false;
    return p.first - q.first; 
}

int cmp_y_axis(const double_pair &p, const double_pair &q) {
    return p.second < q.second;
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


double min_middle(const vector<double_pair> &xsorted, const vector<double_pair> &ysorted, 
        const double offset, const double d) {

    double min = DBL_MAX;
    vector<double_pair> center_pairs;
    auto in_limit = [&](const double_pair p) { return abs(p.first - offset) <= d; };
    copy_if(xsorted.begin(), xsorted.end(), back_inserter(center_pairs), in_limit); // it may be optimized

    const int n = center_pairs.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) {
            if (abs(center_pairs[i].second - center_pairs[j].second) < d) {
                double curr_dist = dist(center_pairs[j], center_pairs[i]);
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
        else right.push_back(p);
    }

    const double min_left = min_dist(left, ysort), min_right = min_dist(right, ysort);
    const double min_sides = min(min_left, min_right);
    const double min_mid = min_middle(xsort, ysort, mid_pair.first, min_sides);
    
    return min(min_sides, min_mid);
}

double min_dist(const vector<double_pair> &pairs) {
    vector<double_pair> xsorted(pairs.begin(), pairs.end());
    vector<double_pair> ysorted(pairs.begin(), pairs.end());
    
    sort(xsorted.begin(), xsorted.end()); // it'll sort by the first element by default
    sort(ysorted.begin(), ysorted.end(), cmp_y_axis); // we must pass a custom function for sorting
    
    return min_dist(xsorted, ysorted);
}

void print_pairs(const vector<double_pair> &pairs) {
    for (auto &p: pairs) cout << p.first << ", " <<  p.second << endl;
}

vector<double_pair> scanv() {
    int n;
    cin >> n;
    vector<double_pair> pairs(n);
    for (int i = 0; i < n; ++i) {
        cin >> pairs[i].first >> pairs[i].second;
    }
    //print_pairs(pairs);
    return pairs;
}

int main(int argc, char const *argv[]) {
    vector<double_pair> pairs = scanv();
    /*
    vector<double_pair> pairs = {
        make_pair(10.8, 142.5),
        make_pair(20.2, 14.05),
        make_pair(112.4, 0.2),
        make_pair(24.2, 17.05),
        make_pair(0.0, 512.3)
    };
    */
    cout << fixed << setprecision(3);
    cout << min_dist(pairs);
    return 0;
}

// g++ -g closest_pair.cpp -std=c++11
