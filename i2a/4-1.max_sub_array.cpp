#include "../playground/vector.hpp"

using namespace std;
using playground::Color;

pair<pair<int, int>, int> method1(const vector<int> &array, int start, int end) {
    // 暴力求解
    if (start >= end) {
        return {{start, start}, -999999999};
    }
    int max_s = start, max_e = start + 1;
    int max_sum = array[start];
    for (int i = start; i < end; i++) {
        int tmp_sum = 0;
        for (int j = i; j < end; j++) {
            tmp_sum += array[j];
            if (tmp_sum > max_sum) {
                max_s = i;
                max_e = j + 1;
                max_sum = tmp_sum;
            }
        }
    }
    return {{max_s, max_e}, max_sum};
}

pair<pair<int, int>, int> method2(const vector<int> &array, int start, int end) {
    // 分治法
    if (start >= end) {
        return {{start, start}, -999999999};
    }
    int mid = (start + end) / 2;
    auto l_res = method2(array, start, mid);
    auto r_res = method2(array, mid + 1, end);
    int max_sum_s = array[mid];
    int tmp_sum = array[mid];
    int max_s = mid;
    for (int i = mid - 1; i >= start; i--) {
        tmp_sum += array[i];
        if (tmp_sum > max_sum_s) {
            max_s = i;
            max_sum_s = tmp_sum;
        }
    }
    int max_e = mid + 1;
    int max_sum_e = array[mid];
    tmp_sum = array[mid];
    for (int i = mid + 1; i < end; i++) {
        tmp_sum += array[i];
        if (tmp_sum > max_sum_e) {
            max_e = i + 1;
            max_sum_e = tmp_sum;
        }
    }
    int max_sum = max_sum_s + max_sum_e - array[mid];
    if (l_res.second >= max_sum && l_res.second >= r_res.second) {
        return l_res;
    }
    if (r_res.second >= max_sum && r_res.second >= l_res.second) {
        return r_res;
    }
    return {{max_s, max_e}, max_sum};
}

pair<pair<int, int>, int> method3(const vector<int> &array, int start, int end) {
    // 线性解法
    if (start >= end) {
        return {{start, start}, -999999999};
    }
    int max_s = start, max_e = end, max_till_now_s = start;
    int max_sum = array[start], max_sum_till_now = array[start];
    for (int i = start + 1; i < end; i++) {
        max_sum_till_now += array[i];
        if (array[i] > max_sum_till_now) {
            max_sum_till_now = array[i];
            max_till_now_s = i;
        }
        if (max_sum_till_now > max_sum) {
            max_s = max_till_now_s;
            max_e = i + 1;
            max_sum = max_sum_till_now;
        }
    }
    return {{max_s, max_e}, max_sum};
}

int main() {
    for (int i = 0; i < 100; i++) {
        auto array = playground::generateRandomVector();
        auto a1 = method1(array, 0, array.size());
        auto a2 = method2(array, 0, array.size());
        auto a3 = method3(array, 0, array.size());
        cout << Color().fore(Color::F::Magenta) << array << endl;
        cout << Color().fore(Color::F::Blue) << a1 << endl;
        cout << Color().fore(Color::F::Green) << a2 << endl;
        cout << Color().fore(Color::F::Cyan) << a3 << endl;
    }
}
