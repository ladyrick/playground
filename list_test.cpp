#include "playground/list.hpp"
using namespace playground::list;

int main() {
    ListNode *head = generateRandomList();
    printList(head);
}
