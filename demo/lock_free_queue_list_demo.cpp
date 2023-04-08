#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <unistd.h>
using namespace std;
#define CAS(a_ptr, a_old, a_new)  __sync_bool_compare_and_swap(a_ptr, a_old, a_new)
class Node
{
public:
    int val;
    Node * next;
    Node(int v){val = v; next = NULL;};
};
class ListLockFreeQueue
{
public:
    ListLockFreeQueue();
    void Push(const int & val);
    bool Pop(int & val);
    void Show();
    Node* head = NULL;
    Node* tail = NULL;
    //Node* dummy = NULL;
    int cnt = 0;
};
ListLockFreeQueue::ListLockFreeQueue()
{
    Node* dummy = new Node(-1);
    head = tail = dummy;
}
void ListLockFreeQueue::Push(const int& val)
{
    Node* q = new Node(val);
    Node *p = tail;
    {
        //Node * p = tail;
        while(p->next != NULL)
            p = p->next;
    }while(!CAS(&(p->next), NULL, q));
    CAS(&tail, p, q);
    printf("[%llu] %s:%d\n", this_thread::get_id(), "push", val);
}
bool ListLockFreeQueue::Pop(int & val)
{
    Node*p;
    {
        if(head->next == NULL)
        {
            cout<<"not pop, empty"<<endl;
            return false;
        }
        p = head;
    }while(!CAS(&head, p, head->next));
    val = p->val;
    printf("[%llu] %s:%d\n", this_thread::get_id(), "pop", val);
    delete p;
}

void ListLockFreeQueue::Show()
{
    Node* tempNode = head;
    /*
    if(head->next == nullptr)
    {
        std::cout << "Empty" <<std::endl;
        return;
    } 
    */
    while(tempNode != nullptr)
    {
        std::cout << tempNode->val << " ";
        tempNode = tempNode->next;
    }
    std::cout << std::endl;
}

int main()
{
    ListLockFreeQueue oListQueue;
    atomic<int> aVal(0);
    /*
    oListQueue.Push(1);
    oListQueue.Push(2);
    oListQueue.Push(3);
    oListQueue.Push(4);
    oListQueue.Show();
    int val;
    oListQueue.Pop(val);
    oListQueue.Pop(val);
    oListQueue.Pop(val);
    oListQueue.Pop(val);
    oListQueue.Pop(val);
    oListQueue.Pop(val);
    oListQueue.Show();
    */
    vector<thread> vecThread;
    for(int i = 0; i < 3; i++)
    {
        vecThread.push_back(thread(
            [&]()
            {
                for(int i = 0; i < 4; i++)
                    oListQueue.Push(aVal++);
            }
        ));
    }
    for(int i = 0; i < 2; i++)
    {
        sleep(1);
        vecThread.push_back(thread(
            [&]()
            {
                int val;
                for(int i = 0; i < 4; i++)
                    oListQueue.Pop(val);
            }
        ));
    }
    for(int i = 0 ; i < vecThread.size(); i++)
        vecThread[i].join();
    oListQueue.Show();
}