#include<thread>
#include <iostream>
#include <unistd.h>
using namespace  std;

/*
void TestThread(int index)
{
    sleep(1);
    std::cout << "Child Thread" << index << " id " << std::this_thread::get_id() << std::endl;
    std::cout << "Child Thread" << index << "Stop" << std::endl;
}
void TestThread2(int index)
{
    //sleep(2);
    std::cout << "Child Thread" << index << " id " << std::this_thread::get_id() << std::endl;
    std::cout << "Child Thread" << index << "Stop" << std::endl;
}
*/
int main()
{
#if 0
    auto TestThread1  = [&](int index)
    {
        //sleep(2);
        std::cout << "Child Thread" << index << " id " << std::this_thread::get_id() << std::endl;
        std::cout << "Child Thread" << index << "Stop" << std::endl;
    };

    auto TestThread2  = [&](int index)
    {
        sleep(2);
        std::cout << "Child Thread" << index << " id " << std::this_thread::get_id() << std::endl;
        std::cout << "Child Thread" << index << "Stop" << std::endl;
    };

    std::thread newThread1(TestThread1, 1);
    sleep(1);
    //sleep(1);
    std::thread newThread2(TestThread2, 2);
    newThread1.join();
    newThread2.join();
    
    std::cout << "Main Thread id " << std::this_thread::get_id() << std::endl;
    std::cout << "Main Thread Stop" << std::endl;
    //if (newThread1.joinable())
    //   newThread1.join();
    //if (newThread2.joinable())
    //    newThread2.join();
#endif
    std::thread t1([]()
    {
        for(int i = 0; i < 100; i++)
        {
            cout<<i<<endl;
            sleep(1);
        }
    });
    t1.detach();
    cout<<"finish"<<endl;
   
}
