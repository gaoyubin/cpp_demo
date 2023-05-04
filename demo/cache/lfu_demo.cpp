#include <iostream>
#include <map>
#include <set>
using namespace std;


class Node
{
public:
    int key;
    int val;
    int cnt;
    int time;
    Node(int k, int v, int c, int t)
    {
        val = v;
        key = k;
        cnt = c;
        time = t;
    }

};
struct CmpNodePtr
{
    bool operator()(const Node* a, const Node* b)
    {
        if(a->cnt < b->cnt)
            return true;
        else if(a->cnt == b->cnt)
        {
            return a->time < b->time;
        }
        return false;
    }
};
class LFUCache {
private:
    map<int, set<Node*>::iterator> m;
    set<Node*, CmpNodePtr> s;
    int cap = 0;
    int size = 0;
    int time = 0;
public:
    LFUCache(int capacity) {
        cap = capacity;
        time = 0;
        size = 0;
    }
    
    int get(int key) {
        if(m.find(key) != m.end())
        {
            auto it = m[key];
            Node* n = *it;
            n->cnt++;
            n->time = time++;
            s.erase(it);
            auto pos = s.insert(s.begin(), n);
            m[key] = pos;
            cout<<"get :"<<key<<"|"<<(*pos)->val<<"|"<<size<<endl;
            return (*pos)->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(m.find(key) == m.end())
        {
            if(size >= cap)
            {
                auto it = s.begin();
                cout<<"del old:"<<(*it)->val<<"--";
                m.erase((*it)->key);
                s.erase(it);
                size--;
            }
            Node* n = new Node(key, value, 1, time++);
            auto pos = s.insert(s.begin(), n);
            m[key] = pos;
            size++;
            cout<<"put new:"<<key<<"|"<<value<<"|"<<size<<endl;
        }
        else
        {
            auto it = m[key];
            Node* n = *it;
            n->cnt++;
            n->val = value;
            n->time = time++;
            s.erase(it);
            auto pos = s.insert(s.begin(), n);
            m[key] = pos;
            cout<<"put old:"<<key<<"|"<<value<<"|"<<size<<endl;
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
int main()
{
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    cout<<lfu.get(1)<<endl;;
    lfu.put(3,3);
    cout<<lfu.get(2)<<endl;;


    return 0;
}