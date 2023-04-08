#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <atomic>
using namespace std;
class LockQueue
{
public:
    int pop(int &val);
    int push(const int & val);
private:
    deque<int> _task;
    // int _iWriteIndex = 0;
    // int _iReadIndex = 0;
    mutex _mutex;
    condition_variable _cvProduce;
    condition_variable _cvConsume;
    int _task_limit = 10;
};
int LockQueue::push(const int & val)
{
    unique_lock<mutex> ul(_mutex);
    while(_task.size() >=_task_limit)
    {
        printf("[%llu] %s:%d\n", this_thread::get_id(), "push queue full", _task.size());
        _cvProduce.wait(ul);
    }
    _task.push_back(val);
    _cvConsume.notify_all();
    printf("[%llu] %s:%d\n", this_thread::get_id(), "push", val);
    return true;
}
int LockQueue::pop(int &val)
{
    unique_lock<mutex> ul(_mutex);
    while(_task.size() == 0)
    {
        printf("[%llu] %s:%d\n", this_thread::get_id(), "pop queue empty", 0);
        _cvConsume.wait(ul);
    }
    val = _task.front();
    _task.pop_front();
    _cvProduce.notify_all();
    printf("[%llu] %s:%d\n", this_thread::get_id(), "pop", val);
    return true;
}
int main()
{
    atomic<int> aVal(0);
    LockQueue lockqueue;
    vector<thread> vecThread;
    for(int i = 0; i < 2; i++)
    {
        vecThread.push_back(thread(
            [&]()
            {
                for(int i = 0; i < 6; i++)
                    lockqueue.push(aVal++);
            }
        ));
    }

    for(int i = 0; i < 1; i++)
    {
        vecThread.push_back(thread(
            [&]()
            {
                int val;
                for(int i = 0; i < 5; i++)
                    lockqueue.pop(val);
            }
        ));
    }
    for(int i = 0; i < vecThread.size(); i++)
        vecThread[i].join();
    return 0;
}
