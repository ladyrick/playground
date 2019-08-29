#include "playground/common.hpp"

using namespace std;

template <class InType, class OutType>
class LRUCache {
  private:
    int max_size;
    int cur_size;
    typedef typename list<pair<InType, OutType>>::iterator listiter_t;
    list<pair<InType, OutType>> val_list;
    unordered_map<InType, listiter_t> list_map;

  public:
    LRUCache(int max_size = 100) : max_size(max_size), cur_size(0) {}

    bool hit(const InType &x) { return list_map.find(x) != list_map.end(); }

    OutType &hit_and_get(const InType &x) {
        listiter_t it = list_map[x];
        OutType &y = (*it).second;
        val_list.erase(it);
        val_list.push_front(make_pair(x, y));
        list_map[x] = val_list.begin();
        return y;
    }

    void not_hit_and_push(const InType &x, OutType &y) {
        if (cur_size == max_size) {
            InType xx = val_list.back().first;
            val_list.pop_back();
            list_map.erase(xx);
        }
        val_list.push_front(make_pair(x, y));
        list_map[x] = val_list.begin();
    }
};

uint64_t f(uint64_t x) {
    if (x <= 1)
        return 1;
    return f(x - 1) + f(x - 2);
}

LRUCache<uint64_t, uint64_t> lru_cache(100);

uint64_t g(uint64_t x) {
    // cout << x << endl;
    if (lru_cache.hit(x)) {
        return lru_cache.hit_and_get(x);
    } else {
        uint64_t y = 1;
        if (x > 1)
            y = g(x - 1) + g(x - 2);
        lru_cache.not_hit_and_push(x, y);
        return y;
    }
}

int main() {
    return 0;
}
