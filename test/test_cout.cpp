#include "../playground/vector.hpp"
using namespace std;

int main() {
    cout << deque<int>{1, 2, 3, 4, 5, 6} << endl;
    cout << forward_list<int>{1, 2, 3, 4, 5, 6} << endl;
    cout << list<int>{1, 2, 3, 4, 5, 6} << endl;
    cout << multiset<int>{1, 2, 3, 4, 5, 6} << endl;
    cout << set<int>{1, 2, 3, 4, 5, 6} << endl;
    cout << unordered_multiset<int>{1, 2, 3, 4, 5, 6} << endl;
    cout << unordered_set<int>{1, 2, 3, 4, 5, 6} << endl;
    cout << vector<int>{1, 2, 3, 4, 5, 6} << endl;
    cout << make_pair(123, "abc") << endl;
    cout << map<int, int>{{1, 1}, {2, 4}, {3, 9}, {4, 16}} << endl;
    cout << multimap<int, int>{{1, 1}, {1, 2}, {1, 3}, {1, 4}} << endl;
    cout << unordered_map<int, int>{{1, 1}, {2, 4}, {3, 9}, {4, 16}} << endl;
    cout << unordered_multimap<int, int>{{1, 1}, {1, 2}, {1, 3}, {1, 4}} << endl;
    return 1;
}
