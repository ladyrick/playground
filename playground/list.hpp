#include "common.hpp"

#ifndef __PLAYGROUND_LIST__
#define __PLAYGROUND_LIST__

namespace playground {

struct ListNode : public playground::__::AutoFree {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

namespace __ {
void trimLeftTrailingSpaces(std::string &input) {
    input.erase(input.begin(),
                std::find_if(input.begin(), input.end(),
                             [](int ch) { return !std::isspace(ch); }));
}

void trimRightTrailingSpaces(std::string &input) {
    input.erase(std::find_if(input.rbegin(), input.rend(),
                             [](int ch) { return !std::isspace(ch); })
                    .base(),
                input.end());
}

std::vector<int> stringToIntegerVector(std::string input) {
    std::vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    std::stringstream ss;
    ss.str(input);
    std::string item;
    char delim = ',';
    while (std::getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}
} // namespace __

bool isSame(ListNode *list1, ListNode *list2) {
    while (list1 && list2) {
        if (list1->val != list2->val) {
            return false;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return list1 == list2;
}

ListNode *stringToListNode(std::string input) {
    // Generate list from the input
    std::vector<int> list = __::stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode *head;
    ListNode **pcur = &head;
    for (int i : list) {
        *pcur = new ListNode(i);
        pcur = &((*pcur)->next);
    }
    return head;
}

void printList(ListNode *head) {
    while (head && head->next) {
        std::cout << head->val << "->";
        head = head->next;
    }

    if (head) {
        std::cout << head->val << std::endl;
    } else {
        std::cout << "Empty LinkedList" << std::endl;
    }
}

ListNode *generateRandomList(int num_nodes = 0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    if (!num_nodes) {
        std::uniform_int_distribution<> idis(1, 30);
        num_nodes = idis(gen);
    }
    std::vector<int> arr(num_nodes);
    for (int i = 0; i < num_nodes; i++) {
        arr[i] = i + 1;
    }
    // shuffle
    for (int i = 0; i < num_nodes - 1; i++) {
        std::uniform_int_distribution<> idis(i, num_nodes - 1);
        std::swap(arr[i], arr[idis(gen)]);
    }
    // turn array to list
    ListNode *head;
    ListNode **pcur = &head;
    for (int i : arr) {
        *pcur = new ListNode(i);
        pcur = &((*pcur)->next);
    }
    return head;
}
} // namespace playground

#endif
