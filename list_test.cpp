#include "playground/list.hpp"

using namespace playground::list;
using namespace std;

int main() {
    ListNode *head = generateRandomList();
    printList(head);  
}
