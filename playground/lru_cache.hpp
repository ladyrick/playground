#include "common.hpp"

#ifndef __PLAYGROUND_LRU_CACHE__
#define __PLAYGROUND_LRU_CACHE__

namespace playground {
template <class InType, class OutType>
class LRUCache {
  private:
    const size_t max_size;
    size_t cur_size;
    typedef typename std::list<std::pair<InType, OutType>>::iterator listiter_t;
    std::list<std::pair<InType, OutType>> val_list;
    std::unordered_map<InType, listiter_t> list_map;

  public:
    LRUCache(int max_size = 100) : max_size(max_size), cur_size(0) {}

    bool hit(const InType &x) { return list_map.find(x) != list_map.end(); }

    OutType hit_and_get(InType x) {
        listiter_t it = list_map[x];
        val_list.emplace_front(std::move(x), it->second);
        val_list.erase(it);
        list_map[x] = val_list.begin();
        return val_list.begin()->second;
    }

    void not_hit_and_push(InType x, OutType y) {
        if (cur_size == max_size) {
            const InType &xx = val_list.back().first;
            val_list.pop_back();
            list_map.erase(xx);
        }
        val_list.emplace_front(std::move(x), std::move(y));
        list_map[x] = val_list.begin();
    }
};
} // namespace playground

#endif
