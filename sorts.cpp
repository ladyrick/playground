#include "playground/common.hpp"

using namespace std;
using namespace playground;

const size_t TITLE_WIDTH = 15;
const size_t RUN_TIMES = 10000;

struct SortFunc {
    virtual string method() = 0;
    virtual void operator()(vector<int> &) = 0;
};

vector<shared_ptr<SortFunc>> sort_funcs;

namespace insert_sort {
struct Sort : SortFunc {
    string method() { return "insert sort"; }
    void operator()(vector<int> &v) {
        for (int i = 1; i < v.size(); i++) {
            int ii = i - 1;
            while (ii >= 0 && v[ii] > v[ii + 1]) {
                swap(v[ii], v[ii + 1]);
                ii--;
            }
        }
    }
};
EXEC(sort_funcs.push_back(make_shared<Sort>()));
} // namespace insert_sort

namespace bubble_sort {
struct Sort : SortFunc {
    string method() { return "bubble sort"; }
    void operator()(vector<int> &v) {
        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                if (v[i] > v[j]) {
                    swap(v[i], v[j]);
                }
            }
        }
    }
};
EXEC(sort_funcs.push_back(make_shared<Sort>()));
} // namespace bubble_sort

int main() {
    vector<int> arr(40);
    for (int i = 0; i < arr.size(); i++)
        arr[i] = randint(0, arr.size());
    cout << setw(TITLE_WIDTH) << "input"
         << ": ";
    cout << arr << endl;
    for (auto p : sort_funcs) {
        cout << setw(TITLE_WIDTH) << p->method() << ": ";
        auto start = chrono::high_resolution_clock::now();
        vector<int> tmp_arr;
        for (int i = 0; i < 10000; i++) {
            tmp_arr = arr;
            (*p)(tmp_arr);
        }
        auto end = chrono::high_resolution_clock::now();
        cout << tmp_arr << " time used: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << "ms." << endl;
    }
    return 0;
}
