/*
 * @lc app=leetcode.cn id=1206 lang=cpp
 *
 * [1206] 设计跳表
 */

// @lc code=start

#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
#if 0
struct Node {
    uint64_t val;
    std::vector<Node*> level;
};
class Skiplist {
private:
    Node* head;
    uint32_t uCurMaxLevel;
    uint32_t uLimitLevel;
public:
    Skiplist() {
        uCurMaxLevel = 0;
        uLimitLevel = 10;
        head = new Node;
        head->level.reserve(uLimitLevel);
        for(int i = 0; i < head->level.size(); i++)
             head->level[i] = NULL;
    }
    
    bool search(int target) {
        Node* tmp = head;
        //cout<<"search cur:"<<uCurMaxLevel<<" "<< tmp->level[1]->val << endl;
        for(int i = uCurMaxLevel; i >= 0; i--)
        {
            while(tmp->level[i] != NULL && tmp->level[i]->val <= target)
            {
                //cout<<"search for:"<< tmp->level[i]->val <<endl;
                tmp = tmp->level[i];
                if(tmp->val == target)
                {
                    cout<<"search succ:"<<target<<endl;
                    return true;
                }
            }
        }
        if(tmp == NULL || tmp->val != target)
        {
            cout<<"search fail:"<<target<<endl;
            return false;
        }
    }
    
    int GetRandomLevel()
    {
        uint32_t uRandomLevel = 0;
        for(int i = 0; i < uLimitLevel; i++)
        {
            int tmp = random()%10;
            if(tmp < 5)
                uRandomLevel++;
            else
                break;
        }
        return uRandomLevel;
    }

    void add(int num) {
         std::vector<Node*> vecUpdate(uCurMaxLevel + 1);
         //cout<<"add : "<<num<<endl;
         Node* tmp = head;
         //从上到下，找到每一个插入点，放到vecUpdate
         for(int i = uCurMaxLevel; i >= 0; i--)
         {
            while(tmp->level[i] != NULL && tmp->level[i]->val < num)
                tmp = tmp->level[i];
            vecUpdate[i] = tmp;
         }
         //cout<<"go"<<endl;
         //生成这次插入节点层数的概率
         uint32_t uRandomLevel = GetRandomLevel();
         //cout<<"rand:"<<uRandomLevel<<endl;
         //生成插入节点
         Node* ptrInsertNode = new Node;
         ptrInsertNode->val = num;
         ptrInsertNode->level.reserve(uRandomLevel+1);
         
         //从下到上到，插入每层节点
         for(int i = 0; i <= uRandomLevel; i++)
         {
            //比现在最高节点还高的时候
            if(i > uCurMaxLevel)
            {
                ptrInsertNode->level[i] = NULL;
                head->level[i] = ptrInsertNode;
                continue;
            }
            ptrInsertNode->level[i] = vecUpdate[i]->level[i];
            vecUpdate[i]->level[i] = ptrInsertNode;
         }
         uCurMaxLevel = std::max(uCurMaxLevel, uRandomLevel);
         cout<<"add succ:"<<num<<endl;
    }
    
    bool erase(int num) {
         std::vector<Node*> vecUpdate(uCurMaxLevel + 1);
         Node* tmp = head;
         Node* res = NULL;
         //从上到下，找到每一个插入点，放到vecUpdate
         for(int i = uCurMaxLevel; i >= 0; i--)
         {
            while(tmp->level[i] != NULL && tmp->level[i]->val < num)
            {
                tmp = tmp->level[i];
            }
            vecUpdate[i] = tmp;
            if(tmp->level[i]->val == num)
                res = tmp;
         }
         //找到节点，则删除
         if(res != NULL)
         {
            // cout<<"erase hit 0:"<<vecUpdate[0]->level[0]->level[0]<<endl;
            // cout<<"erase hit 1:"<<vecUpdate[1]->level[1]->level[1]<<endl;
            // cout<<"erase hit 0:"<<vecUpdate[0]->level[0]<<endl;
            // cout<<"erase hit 1:"<<vecUpdate[1]->level[1]<<endl;

            for(int i = 0; i < vecUpdate.size(); i++)
            {
                vecUpdate[i]->level[i] = vecUpdate[i]->level[i]->level[i];
            }
            cout<<"delete succ:"<<num<<endl;
            delete res;
            return true;
         }
        cout<<"delete fail:"<<num<<endl;
         return false;
    }
};
#endif 

#if 0
struct Node {
    uint64_t val;
    //std::vector<Node*> level;
    Node** level;
};
class Skiplist {
private:
    Node* head;
    uint32_t uCurMaxLevel;
    uint32_t uLimitLevel;
public:
    Skiplist() {
        uCurMaxLevel = 0;
        uLimitLevel = 10;
        head = new Node;
        //head->level.reserve(uLimitLevel);
        head->level = new Node*[uLimitLevel];
        for(int i = 0; i < uLimitLevel; i++)
             head->level[i] = NULL;
    }
    
    bool search(int target) {
        Node* tmp = head;
        //cout<<"search cur:"<<uCurMaxLevel<<" "<< tmp->level[1]->val << endl;
        for(int i = uCurMaxLevel; i >= 0; i--)
        {
            while(tmp->level[i] != NULL && tmp->level[i]->val <= target)
            {
                //cout<<"search for:"<< tmp->level[i]->val <<endl;
                tmp = tmp->level[i];
                if(tmp->val == target)
                {
                    cout<<"search succ:"<<target<<endl;
                    return true;
                }
            }
        }
        if(tmp == NULL || tmp->val != target)
        {
            cout<<"search fail:"<<target<<endl;
            return false;
        }
        return false;
    }
    
    int GetRandomLevel()
    {
        uint32_t uRandomLevel = 0;
        for(int i = 0; i < uLimitLevel; i++)
        {
            int tmp = random()%10;
            if(tmp < 5)
                uRandomLevel++;
            else
                break;
        }
        return uRandomLevel;
    }

    void add(int num) {
         //std::vector<Node*> vecUpdate(uCurMaxLevel + 1);
         Node** vecUpdate = new Node*[uCurMaxLevel + 1];
         for(int i = 0; i < uCurMaxLevel; i++)
             vecUpdate[i] = NULL;
         //cout<<"add : "<<num<<endl;
         Node* tmp = head;
         //从上到下，找到每一个插入点，放到vecUpdate
         for(int i = uCurMaxLevel; i >= 0; i--)
         {
            while(tmp->level[i] != NULL && tmp->level[i]->val < num)
                tmp = tmp->level[i];
            vecUpdate[i] = tmp;
         }
         //cout<<"go"<<endl;
         //生成这次插入节点层数的概率
         uint32_t uRandomLevel = GetRandomLevel();
         //cout<<"rand:"<<uRandomLevel<<endl;
         //生成插入节点
         Node* ptrInsertNode = new Node;
         ptrInsertNode->val = num;
         ptrInsertNode->level = new Node*[uRandomLevel+1];
         
         //从下到上到，插入每层节点
         for(int i = 0; i <= uRandomLevel; i++)
         {
            //比现在最高节点还高的时候
            if(i > uCurMaxLevel)
            {
                ptrInsertNode->level[i] = NULL;
                head->level[i] = ptrInsertNode;
                continue;
            }
            ptrInsertNode->level[i] = vecUpdate[i]->level[i];
            vecUpdate[i]->level[i] = ptrInsertNode;
         }
         uCurMaxLevel = std::max(uCurMaxLevel, uRandomLevel);
         cout<<"add succ:"<<num<<endl;
    }
    
    bool erase(int num) {
         //std::vector<Node*> vecUpdate(uCurMaxLevel + 1);
         Node** vecUpdate = new Node*[uCurMaxLevel + 1];
         for(int i = 0; i < uCurMaxLevel; i++)
             vecUpdate[i] = NULL;
         Node* tmp = head;
         Node* res = NULL;
         //从上到下，找到每一个插入点，放到vecUpdate
         for(int i = uCurMaxLevel; i >= 0; i--)
         {
            while(tmp->level[i] != NULL && tmp->level[i]->val < num)
            {
                tmp = tmp->level[i];
            }
            vecUpdate[i] = tmp;
            if(tmp->level[i]->val == num)
                res = tmp;
         }
         //找到节点，则删除
         if(res != NULL)
         {
            // cout<<"erase hit 0:"<<vecUpdate[0]->level[0]->level[0]<<endl;
            // cout<<"erase hit 1:"<<vecUpdate[1]->level[1]->level[1]<<endl;
            // cout<<"erase hit 0:"<<vecUpdate[0]->level[0]<<endl;
            // cout<<"erase hit 1:"<<vecUpdate[1]->level[1]<<endl;

            for(int i = 0; i < uCurMaxLevel + 1; i++)
            {
                vecUpdate[i]->level[i] = vecUpdate[i]->level[i]->level[i];
            }
            cout<<"delete succ:"<<num<<endl;
            delete res;
            return true;
         }
         return false;
    }
};

#endif

int MAX_LEVEL = 32;
struct Node {
    uint64_t val;
    std::vector<Node*> level;
    Node(int _val, int _maxLevel = MAX_LEVEL) : val(_val), level(_maxLevel, nullptr) {
}
};
class Skiplist {
private:
    Node* head;
    uint32_t uCurMaxLevel;
    uint32_t uLimitLevel;
public:
    Skiplist() {
        uCurMaxLevel = 0;
        uLimitLevel = MAX_LEVEL;
        head = new Node(-1);
        head->level.reserve(uLimitLevel);
        for(int i = 0; i < head->level.size(); i++)
             head->level[i] = NULL;
    }
    
    bool search(int target) {
        Node* tmp = head;
        cout<<"search cur:"<<uCurMaxLevel<<" "<< tmp->level[1]->val << endl;
        for(int i = uCurMaxLevel; i >= 0; i--)
        {
            while(tmp->level[i] != NULL && tmp->level[i]->val <= target)
            {
                cout<<"search for:"<< tmp->level[i]->val <<endl;
                tmp = tmp->level[i];
                if(tmp->val == target)
                {
                    cout<<"search succ:"<<target<<endl;
                    return true;
                }
            }
        }
        if(tmp == NULL || tmp->val != target)
        {
            cout<<"search fail:"<<target<<endl;
            return false;
        }
        return false;
    }
    
    int GetRandomLevel()
    {
        uint32_t uRandomLevel = 0;
        for(int i = 0; i < uLimitLevel; i++)
        {
            int tmp = random()%10;
            if(tmp < 5)
                uRandomLevel++;
            else
                break;
        }
        cout<<"-------uRandomLevel:"<<uRandomLevel<<endl;
        return uRandomLevel;
    }

    void add(int num) {
         std::vector<Node*> vecUpdate(uCurMaxLevel + 1, NULL);
         cout<<"add : "<<num<<endl;
         Node* tmp = head;
         //从上到下，找到每一个插入点，放到vecUpdate
         for(int i = uCurMaxLevel; i >= 0; i--)
         {
            while(tmp->level[i] != NULL && tmp->level[i]->val < num)
                tmp = tmp->level[i];
            vecUpdate[i] = tmp;
         }
         cout<<"go"<<endl;
         //生成这次插入节点层数的概率
         uint32_t uRandomLevel = GetRandomLevel();
         cout<<"rand:"<<uRandomLevel<<endl;
         //生成插入节点
         Node* ptrInsertNode = new Node(num, uRandomLevel+1);
         //从下到上到，插入每层节点
         for(int i = 0; i <= uRandomLevel; i++)
         {
            //比现在最高节点还高的时候
            if(i > uCurMaxLevel)
            {
                ptrInsertNode->level[i] = NULL;
                head->level[i] = ptrInsertNode;
                continue;
            }
            ptrInsertNode->level[i] = vecUpdate[i]->level[i];
            vecUpdate[i]->level[i] = ptrInsertNode;
         }
         uCurMaxLevel = std::max(uCurMaxLevel, uRandomLevel);
         cout<<"add succ:"<<num<<endl;
    }
    
    bool erase(int num) {
         std::vector<Node*> vecUpdate(uCurMaxLevel + 1);
         Node* tmp = head;
         Node* res = NULL;
         //从上到下，找到每一个插入点，放到vecUpdate
         for(int i = uCurMaxLevel; i >= 0; i--)
         {
            while(tmp->level[i] != NULL && tmp->level[i]->val < num)
            {
                tmp = tmp->level[i];
            }
            vecUpdate[i] = tmp;
            if(tmp->level[i]->val == num)
                res = tmp;
         }
         //找到节点，则删除
         if(res != NULL)
         {
            cout<<"erase hit 0:"<<vecUpdate[0]->level[0]->level[0]<<endl;
            cout<<"erase hit 1:"<<vecUpdate[1]->level[1]->level[1]<<endl;
            cout<<"erase hit 0:"<<vecUpdate[0]->level[0]<<endl;
            cout<<"erase hit 1:"<<vecUpdate[1]->level[1]<<endl;

            for(int i = 0; i < vecUpdate.size(); i++)
            {
                vecUpdate[i]->level[i] = vecUpdate[i]->level[i]->level[i];
            }
            cout<<"delete succ:"<<num<<endl;
            delete res;
            return true;
         }
         cout<<"delete fail:"<<num<<endl;
         return false;
    }
};

int main()
{
    /*
    Skiplist oskiplist;
    //oskiplist.add(1);
    oskiplist.add(2);
    oskiplist.erase(2);
    oskiplist.add(2);
    //oskiplist.add(2);
    //oskiplist.add(3);
    bool bres = oskiplist.search(2);
    cout<<"search res:"<<bres<<endl;;
    */
   
    //Skiplist skiplist = new Skiplist();
    Skiplist skiplist;
    skiplist.add(1);
    skiplist.add(2);
    skiplist.add(3);
    skiplist.search(0);   // 返回 false
    skiplist.add(4);
    //skiplist.add(5);
    skiplist.search(1);   // 返回 true
    skiplist.erase(0);    // 返回 false，0 不在跳表中
    skiplist.erase(1);    // 返回 true
    //skiplist.erase(2);    // 返回 true
    skiplist.search(1);   // 返回 false，1 已被擦除
    //skiplist.search(2);   // 返回 false，1 已被擦除
}
