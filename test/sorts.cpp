#include "../playground/common.hpp"

using namespace std;
using namespace playground;

struct SortBase {
    virtual string method() = 0;
    virtual void sort(vector<int> &) = 0;
    int midPivot(const vector<int> &v, int start, int end) {
        int mid = (start + end) / 2;
        pair<int, int> tmp[] = {{start, v[start]}, {mid, v[mid]}, {end, v[end]}};
        if (tmp[1].second < tmp[0].second) {
            swap(tmp[0], tmp[1]);
        }
        if (tmp[2].second < tmp[1].second) {
            swap(tmp[1], tmp[2]);
            if (tmp[1].second < tmp[0].second) {
                swap(tmp[0], tmp[1]);
            }
        }
        return tmp[1].first;
    }
};
vector<shared_ptr<SortBase>> sort_funcs;

struct STLSort : SortBase {
    string method() { return "STL sort"; };
    void sort(vector<int> &v) { ::sort(v.begin(), v.end()); };
};
EXEC(sort_funcs.push_back(make_shared<STLSort>()));

struct InsertSort : SortBase {
    string method() { return "insert sort"; }
    void sort(vector<int> &v) {
        for (int i = 1; i < v.size(); i++) {
            int ii = i - 1;
            while (ii >= 0 && v[ii] > v[ii + 1]) {
                swap(v[ii], v[ii + 1]);
                ii--;
            }
        }
    }
};
// EXEC(sort_funcs.push_back(make_shared<InsertSort>()));

struct BubbleSort : SortBase {
    string method() { return "bubble sort"; }
    void sort(vector<int> &v) {
        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                if (v[i] > v[j]) {
                    swap(v[i], v[j]);
                }
            }
        }
    }
};
// EXEC(sort_funcs.push_back(make_shared<BubbleSort>()));

struct QuickSort : SortBase {
    string method() { return "quick sort"; }
    void qsort(vector<int> &v, int start, int end) {
        if (start >= end) {
            return;
        }
        int pivot_ind = midPivot(v, start, end);
        if (pivot_ind != end) {
            swap(v[pivot_ind], v[end]);
        }
        int pivot = v[end];
        int partition = start;
        for (int i = start; i <= end; i++) {
            if (v[i] < pivot) {
                if (i != partition) {
                    swap(v[i], v[partition]);
                }
                partition++;
            }
        }
        swap(v[end], v[partition]);
        qsort(v, start, partition - 1);
        qsort(v, partition + 1, end);
    }
    void sort(vector<int> &v) { qsort(v, 0, v.size() - 1); }
};
EXEC(sort_funcs.push_back(make_shared<QuickSort>()));

struct QuickSort2 : SortBase {
    string method() { return "quick sort v2"; }
    void qsort(vector<int> &v, int start, int end) {
        if (start >= end) {
            return;
        }
        int pivot_ind = midPivot(v, start, end);
        if (pivot_ind != end) {
            swap(v[pivot_ind], v[end]);
        }
        int pivot = v[end];
        int l = start, r = end;
        while (l < r) {
            while (l < r && v[l] <= pivot) {
                l++;
            }
            while (l < r && v[r] >= pivot) {
                r--;
            }
            if (l != r)
                swap(v[l], v[r]);
        }
        swap(v[l], v[end]);
        qsort(v, start, l - 1);
        qsort(v, l + 1, end);
    }
    // 3,5,2,1,3,2,7,6,6,8,5
    void sort(vector<int> &v) { qsort(v, 0, v.size() - 1); }
};
EXEC(sort_funcs.push_back(make_shared<QuickSort2>()));

struct QuickSort_Sandwish : SortBase {
    string method() { return "quick sort sandwish"; }
    void qsort(vector<int> &v, int start, int end) {
        if (start >= end) {
            return;
        }
        int pivot_ind = midPivot(v, start, end);
        if (pivot_ind != end) {
            swap(v[pivot_ind], v[end]);
        }
        int pivot = v[end];
        int partition1 = start;
        int partition2 = start;
        for (int i = start; i <= end; i++) {
            if (v[i] < pivot) {
                if (i != partition2) {
                    swap(v[i], v[partition2]);
                }
                if (partition2 != partition1) {
                    swap(v[partition2], v[partition1]);
                }
                partition1++;
                partition2++;
            } else if (v[i] == pivot) {
                if (i != partition2) {
                    swap(v[i], v[partition2]);
                }
                partition2++;
            }
        }
        qsort(v, start, partition1 - 1);
        qsort(v, partition2, end);
    }
    void sort(vector<int> &v) { qsort(v, 0, v.size() - 1); }
};
EXEC(sort_funcs.push_back(make_shared<QuickSort_Sandwish>()));

struct MergeSort : SortBase {
    string method() { return "merge sort"; }
    void mergesort(vector<int> &v, int start, int end) {
        if (end - start < 1) {
            return;
        }
        int mid = (start + end) / 2;
        mergesort(v, start, mid);
        mergesort(v, mid + 1, end);

        vector<int> front_part(v.begin() + start, v.begin() + mid + 1);

        int front = 0;
        int back = mid + 1;
        for (int i = start; i <= end; i++) {
            if (front > mid - start) {
                v[i] = v[back++];
            } else if (back > end || front_part[front] < v[back]) {
                v[i] = front_part[front++];
            } else {
                v[i] = v[back++];
            }
        }
    }
    void sort(vector<int> &v) { mergesort(v, 0, v.size() - 1); }
};
EXEC(sort_funcs.push_back(make_shared<MergeSort>()));

struct HeapSort : SortBase {
    string method() { return "heap sort"; }
    void adjust(vector<int> &v, int root, int end) {
        int lc = root * 2 + 1;
        int rc = lc + 1;
        int largest = root;
        if (lc <= end && v[lc] > v[largest]) {
            largest = lc;
        }
        if (rc <= end && v[rc] > v[largest]) {
            largest = rc;
        }
        if (largest != root) {
            swap(v[largest], v[root]);
            adjust(v, largest, end);
        }
    }
    void sort(vector<int> &v) {
        for (int i = v.size() / 2; i >= 0; i--) {
            adjust(v, i, v.size() - 1);
        }
        for (int i = v.size() - 1; i > 0; i--) {
            swap(v[0], v[i]);
            adjust(v, 0, i - 1);
        }
    }
};
EXEC(sort_funcs.push_back(make_shared<HeapSort>()));

int main() {
    size_t title_width = 0;
    for (auto p : sort_funcs) {
        title_width = max(title_width, p->method().size());
    }

    const size_t array_size = 100000;

    vector<tuple<string, shared_ptr<vector<int>>, shared_ptr<vector<int>>>> testbenchs;

    auto normal_arr = make_shared<vector<int>>(array_size);
    for (int i = 0; i < array_size; i++)
        (*normal_arr)[i] = randint(0, array_size);
    auto sorted_normal_arr = make_shared<vector<int>>(*normal_arr);
    sort(sorted_normal_arr->begin(), sorted_normal_arr->end());
    testbenchs.push_back({"normal", normal_arr, sorted_normal_arr});

    auto many_dup_arr = make_shared<vector<int>>(array_size);
    for (int i = 0; i < array_size; i++)
        (*many_dup_arr)[i] = randint(0, array_size / 100);
    auto sorted_many_dup_arr = make_shared<vector<int>>(*many_dup_arr);
    sort(sorted_many_dup_arr->begin(), sorted_many_dup_arr->end());
    testbenchs.push_back({"many duplicated elements", many_dup_arr, sorted_many_dup_arr});

    auto almost_sorted_arr = make_shared<vector<int>>(array_size);
    for (int i = 0; i < array_size; i++)
        (*almost_sorted_arr)[i] = randint(0, array_size);
    sort(almost_sorted_arr->begin(), almost_sorted_arr->end());
    auto sorted_almost_sorted_arr = make_shared<vector<int>>(*almost_sorted_arr);
    for (int i = 0; i < 50; i++) {
        int j = randint(0, array_size);
        int k = randint(0, array_size);
        swap((*almost_sorted_arr)[j], (*almost_sorted_arr)[k]);
    }
    testbenchs.push_back({"almost sorted", almost_sorted_arr, sorted_almost_sorted_arr});

    for (auto tb : testbenchs) {
        cout << "========== " << get<0>(tb) << " ==========" << endl << endl;
        for (auto p : sort_funcs) {
            cout << setw(title_width) << p->method() << ": ";
            size_t microseconds = 0;
            vector<int> tmp_arr;
            for (int i = 0; i < 10; i++) {
                tmp_arr = *get<1>(tb);
                auto start = chrono::high_resolution_clock::now();
                p->sort(tmp_arr);
                auto end = chrono::high_resolution_clock::now();
                microseconds += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }
            bool correct = true;
            for (int i = 0; i < tmp_arr.size(); i++) {
                if (tmp_arr[i] != (*get<2>(tb))[i]) {
                    correct = false;
                    break;
                }
            }
            if (correct) {
                cout << microseconds / 1000 << "ms." << endl;
            } else {
                cout << "wrong answer." << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
