#include <iostream>
struct  ListNode
{
    int val;
    ListNode * next;
};
ListNode* reverse(ListNode* head)
{
    ListNode*pre = NULL, cur = head;
    while(cur != NULL)
    {
        ListNode* tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    return pre;
}
int main()
{

}