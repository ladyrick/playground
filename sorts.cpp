#include "playground/common.hpp"

using namespace std;
using namespace playground;

typedef void (*InPlaceSortFunc)(vector<int> &);

vector<InPlaceSortFunc> sort_funcs;

void bubble_sort(vector<int> &v) {}
void g(vector<int> &v) {}
void h(vector<int> &v) {}

EXEC(sort_funcs.push_back(bubble_sort));
EXEC(sort_funcs.push_back(g));
EXEC(sort_funcs.push_back(h));

int main() {
    vector<int> arr = {5, 2, 3, 6, 4, 2, 6, 2, 1, 5};
    for (auto sortfunc : sort_funcs) {
        vector<int> tmp_arr = arr;
        auto start = chrono::high_resolution_clock::now();
        sortfunc(tmp_arr);
        auto end = chrono::high_resolution_clock::now();
        cout << tmp_arr << " time used: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << "ms." << endl;
    }

    map<int, vector<int>> m;
    m[1] = vector<int>{1, 2, 3};
    m[3] = vector<int>{4, 5, 6};
    cout << m << endl;
    return 0;
}
