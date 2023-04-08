#include <thread>
#include <vector>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <unistd.h>
using namespace std;
// typedef int TaskFun(void);
using Task = function<int(void)>;
//typedef 

class ThreadPool
{
public:
    void SetThreadCnt(int n){_n = n;}
    ThreadPool();
    ~ThreadPool();
    void Run(Task);
    // void Run(function<int(void)>){};
    static ThreadPool* GetPool()
    {
        static ThreadPool pool;
        return &pool;
    }
private:
    int _n = 10;
    vector<thread> _vecThread;
    //deque<int(*)()> _dq;
    deque<Task> _dq;
    mutex _mutex;
    condition_variable _cv;
};
ThreadPool::ThreadPool()
{
    for(int i = 0; i < _n ; i++)
    {
        _vecThread.push_back(thread(
            [&]()
            {
                unique_lock <std::mutex> ul(_mutex);
                while(_dq.size() == 0)
                    _cv.wait(ul);
                    //等待
                auto task = _dq.front();
                _dq.pop_front();
                ul.unlock();

                task();
            }
        ));
        //_vecThread[i].detach();
    }

    for(int i = 0; i < _vecThread.size(); i++)
    {
        printf("[%llu] start\n", _vecThread[i].get_id());
        _vecThread[i].detach();
    }

}

 ThreadPool::~ThreadPool()
 {
    cout<<"~"<<endl;
 }
 
void ThreadPool::Run(Task task)
{
    //加锁
    lock_guard<mutex> lg(_mutex);
    _dq.push_back(task);
    _cv.notify_one();
    
}

int Print()
{
    //sleep(1);
    //cout<<"hello world"<<endl;
    printf("[%llu] %s\n", this_thread::get_id(), "hello world");
}
int main()
{
    ThreadPool* pool = ThreadPool::GetPool();
    // return ;
    for(int i = 0; i < 4; i++)
        pool->Run(Print);
    // pool->Run([&](){
    //     cout<<"hello"<<endl;
    //     return 1;
    // });
    sleep(2);
    cout<<"finish"<<endl;
}