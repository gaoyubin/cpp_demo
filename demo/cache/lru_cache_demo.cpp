#include <string>
#include <iostream>
#include <map>
#include <list>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <chrono>
using namespace std;
class Node
{
public:
    string key;
    int val;
    time_t expire_ts;
    Node(string k, int v, int expire_sec = 0):key(k), val(v)
    {
        if(expire_sec != 0)
            expire_ts = time(NULL) + expire_sec;
    };
};


class LruCache
{
public:
    LruCache(int c);
    int get(string key);
    int put(string key, int val, int expire_sec = 0);
private:
    void thread_expire_prune();
    map<string, list<Node*>::iterator> _cache;
    list<Node*> _l;
    int _max_cap = 0;
    int _cur_cap = 0;
    mutex _cache_mutex;

    thread _expire_prune;
    priority_queue<pair<time_t, string>> _expire_pq;
    condition_variable _expire_cv;
    mutex _expire_mutex;
};

void LruCache::thread_expire_prune()
{
    while(1)
    {
        // cout<<"begin thread_expire_prune"<<endl;
        while(_expire_pq.size() == 0)
        {
            unique_lock<mutex> ul(_expire_mutex);
            _expire_cv.wait(ul);
        }
        
        auto pair = _expire_pq.top();
        cout<<"_expire_pq.top:"<<pair.first<<"|"<<pair.second<<"|"<<time(NULL)<<endl;
        if(pair.first > time(NULL))
        {
            auto now  = chrono::system_clock::now();
            auto util_time = now + chrono::seconds(pair.first - time(NULL));
            unique_lock<mutex> ul(_expire_mutex);
            _expire_cv.wait_until(ul, util_time);
            // _expire_cv.wait_until(ul, time(NULL));
        }
        else
        {
            //处理掉过期的node
            _expire_pq.pop();
            if(_cache.find(pair.second) != _cache.end())
            {
                cout<<"expire_prune:"<<pair.second<<"|"<<pair.first<<"|"<<time(NULL)<<endl;
                auto it = _cache[pair.second];
                _cache.erase(pair.second);
                _l.erase(it);
                delete *it;
                _cur_cap--;
            }
        }
    }
}

LruCache::LruCache(int c):_max_cap(c)
{
    //启动超时
    thread t(&LruCache::thread_expire_prune, this);
    t.detach();
}
int LruCache::put(string key, int val, int expire_sec /*= 0*/)
{
    time_t expire_ts;
    if(_cache.find(key) != _cache.end())
    {
        lock_guard<mutex> lg(_cache_mutex);
        auto it = _cache[key];
        _l.erase(it);
        _l.push_front(*it);
        (*it)->val = val;
        if(expire_sec > 0)
        {
            expire_ts = time(NULL) + expire_sec;
            (*it)->expire_ts = expire_ts;
            _expire_pq.push(pair<time_t, string>(expire_ts, key));
            _expire_cv.notify_all();
        }

    }
    else
    {
        //cout<<"put new:"<<key<<"|"<<val<<endl;
        lock_guard<mutex> lg(_cache_mutex);
        Node* n = new Node(key, val);
        _l.push_front(n);
        _cache[key] = _l.begin();
        _cur_cap++;
        
        if(expire_sec > 0)
        {
            expire_ts = time(NULL) + expire_sec;
            n->expire_ts = expire_ts;
            _expire_pq.push(pair<time_t, string>(expire_ts, key));
            _expire_cv.notify_all();
        }

        if(_cur_cap >= _max_cap)
        {
            Node* n = _l.back();
            _l.pop_back();
            _cache.erase(n->key);
            delete n;
            _cur_cap--;
        }
        cout<<"put:"<<key<<"|"<<val<<"|"<<expire_ts<<endl;
    }
    return 0;
}
int LruCache::get(string key)
{
    lock_guard<mutex> lg(_cache_mutex);
    if(_cache.find(key) != _cache.end())
    {
        auto it = _cache[key];
        int val = (*it)->val;
        cout<<"get:"<<key<<"|"<<val<<endl;
        return val;
    }
    cout<<"get:"<<key<<"|-1"<<endl;
    return -1;
}
int main()
{
    LruCache lru_cache(4);
    lru_cache.put("1", 1);
    lru_cache.put("2", 2);
    lru_cache.put("3", 3);
    //int val;
    lru_cache.get("1");
    lru_cache.put("4", 4);
    lru_cache.get("1");
    cout<<"this"<<endl;
    while(1)
    {
        int type;
        cin>>type;
        if(type == 1)
        {
            string key;
            int val, sec;
            cin>>key>>val>>sec;
            lru_cache.put(key, val, sec);
        }
        else if(type == 2)
        {
            string key;
            cin>>key;
            lru_cache.get(key);
        }
    }
    
    auto t = chrono::system_clock::now();
    auto t1 = t  + chrono::seconds(2);
    //cout<<t<<"|"<<t1<<endl;
  
    return 0;
}