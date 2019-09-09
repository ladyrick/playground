#include "playground/common.hpp"

using namespace std;
using namespace playground;

struct SortBase {
    virtual string method() = 0;
    virtual void sort(vector<int> &) = 0;
};

vector<shared_ptr<SortBase>> sort_funcs;

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

struct QuickSort_Sandwish : SortBase {
    string method() { return "quick sort sandwish"; }
    void qsort(vector<int> &v, int start, int end) {
        if (start >= end) {
            return;
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

int main() {
    vector<int> arr(100000);
    for (int i = 0; i < arr.size(); i++)
        arr[i] = randint(0, arr.size());
    auto sorted_arr = arr;
    sort(sorted_arr.begin(), sorted_arr.end());

    size_t title_width = 0;
    for (auto p : sort_funcs) {
        title_width = max(title_width, p->method().size());
    }
    for (auto p : sort_funcs) {
        cout << setw(title_width) << p->method() << ": ";
        size_t microseconds = 0;
        vector<int> tmp_arr;
        for (int i = 0; i < 10; i++) {
            tmp_arr = arr;
            auto start = chrono::high_resolution_clock::now();
            p->sort(tmp_arr);
            auto end = chrono::high_resolution_clock::now();
            microseconds +=
                chrono::duration_cast<chrono::microseconds>(end - start)
                    .count();
        }
        bool correct = true;
        for (int i = 0; i < tmp_arr.size(); i++) {
            if (tmp_arr[i] != sorted_arr[i]) {
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
    return 0;
}
