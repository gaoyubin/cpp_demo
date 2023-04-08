#include <iostream>
#include <vector>
#include <thread>
#include <sstream>
#include <unistd.h>
#include <atomic>
#include <iterator>
using namespace std;
#define CAS(a_ptr, a_oldval, a_newval) __sync_bool_compare_and_swap(a_ptr, a_oldval, a_newval)
class ArrayLockFreeQueue
{
public:
    ArrayLockFreeQueue(int n)
    {
        _n = n;
        _array.resize(_n);
    }
    bool Push(const int& val);
    bool Pop(int &val);
    
    int CountIndex(const int & index){return index % _n;}
public:
    int _iReadIndex = 0;
    int _iWriteIndex = 0;
    int _iMaxReadIndex = 0;
    vector<int> _array;
    int _n;
};

bool ArrayLockFreeQueue::Pop(int & val)
{
    val = -1;
    int p;
    {
        //如果空了
        if(CountIndex(_iMaxReadIndex) == CountIndex(_iReadIndex))
        {
            printf("[%llu] %s:%d %d|%d|%d\n", this_thread::get_id(), "pop queue empty", val , _iReadIndex, _iMaxReadIndex, _iWriteIndex);
            return false;
        }
        p = _iReadIndex;
        //要先读出去来，否则cas后,_iReadIndex往后移了，这个位置有可能就被覆盖了
        val = _array[p];
    }while(!CAS(&_iReadIndex, p, p + 1));
    
    printf("[%llu] %s:%d %d|%d|%d\n",  this_thread::get_id(), "pop", val , _iReadIndex, _iMaxReadIndex, _iWriteIndex);
    return true;
}
bool ArrayLockFreeQueue::Push(const int & val)
{
    int p;
    {
        //如果满了
        if(CountIndex(_iWriteIndex + 1) == CountIndex(_iReadIndex))
        {
            printf("[%llu] %s:%d %d|%d|%d\n",  this_thread::get_id(), "push queue full", val , _iReadIndex, _iMaxReadIndex, _iWriteIndex);
            return false;
        }
        p = _iWriteIndex;
    }while(!CAS(&_iWriteIndex, p,  p + 1));
    _array[CountIndex(p)] = val;
    //val已经放好，标记这个位可读，这步串行的
    while(!CAS(&_iMaxReadIndex, p, p + 1));
    printf("[%llu] %s:%d %d|%d|%d\n", this_thread::get_id(), "push", val , _iReadIndex, _iMaxReadIndex, _iWriteIndex);
    return true;
}

int main()
{
    std::atomic<int> aVal(0);
    ArrayLockFreeQueue oArrayQueue(10);
    vector<thread> vecThread;
    for(int i = 0; i < 4; i++)
    {
       vecThread.push_back(std::thread(
       [&]()
       {
            for(int i = 0; i < 5; i++)
            {
                //usleep(1000);
                oArrayQueue.Push(aVal++);
            }
            printf("[%llu] end\n",std::this_thread::get_id());
        }));
    }

    for(int i = 0; i < 1; i++)
    {
        vecThread.push_back(std::thread(
        [&]()
        {
            sleep(1);
            for(int i = 0; i < 14; i++)
            //while(1)
            {
                //usleep(1000);
                int val;
                oArrayQueue.Pop(val);
            }
           printf("[%llu] end\n",std::this_thread::get_id());
        }
        ));
    }
    for(int i = 0; i < vecThread.size(); i++)
        vecThread[i].join();
    copy(oArrayQueue._array.begin(), oArrayQueue._array.end(), ostream_iterator<int>(cout, " "));
    cout<<endl;
    cout<<oArrayQueue._iReadIndex<<"|"<<oArrayQueue._iMaxReadIndex<<"|"<<oArrayQueue._iWriteIndex<<endl;
    printf("finish\n");
    return 0;
}