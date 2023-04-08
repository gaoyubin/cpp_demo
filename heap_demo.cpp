#include<iostream>
#include<vector>
#include<queue>
#include <functional>
#include <map>
#include <set>
using namespace std;
#define N 4

struct cmpPairSecondFloatGreat{
    bool operator() (const std::pair<uint64_t, uint32_t>&a, const std::pair<uint64_t, uint32_t>& b) {
        return a.second > b.second;
    }
};

int main()
{
#if 0
    //小堆
    vector<int> v{1, 3, 2, 6, 5, 7, 10, 8, 9};
    priority_queue<pair<int,int>,vector<pair<int,int> >, greater<pair<int,int> > > coll;
    /*
    pair<int,int> a(3,4);
    pair<int,int> b(3,5);
    pair<int,int> c(4,3);
    coll.push(c);
    coll.push(b);
    coll.push(a);

    while(!coll.empty())
    {
        cout<<coll.top().first<<"\t"<<coll.top().second<<endl;
        coll.pop();
    }
    */
    for(const auto id : v)
    {
        if(coll.size() < N)
            coll.push(pair<int,int>(id, id));
        else if(coll.size() >= N && coll.top().first < id)
        {
            coll.pop();
            coll.push(pair<int,int>(id, id));
        }
    }

    while(!coll.empty())
    {
        cout<<coll.top().first<<"\t"<<coll.top().second<<endl;
        coll.pop();
    }
#endif

    const uint32_t g_uSendLimit = 3;
	priority_queue<pair<uint64_t, uint32_t>, vector<pair<uint32_t, uint64_t>>, cmpPairSecondFloatGreat> oMinHeap;
    map<uint64_t, uint32_t> mapVid2Score;
    mapVid2Score[1688856672325776]=33;
    mapVid2Score[1688856709375990]=33;
    mapVid2Score[1688857600387628]=27;
    mapVid2Score[1688858189471525]=23;

	for(const auto & p : mapVid2Score)
	{
		if(oMinHeap.size() < g_uSendLimit)
        {
			oMinHeap.push(p);
            cout<<"push size:"<<p.second<<endl;
        }
		else if(oMinHeap.top().second < p.second)
		{
			oMinHeap.pop();
			oMinHeap.push(p);
            cout<<"push top:"<<p.second<<endl;
		}
	}
    cout<<endl;
	//XLOG_DEBUG("show score", uVid, uCorpId, mapVid2Score, oMinHeap.size());

	map<uint64_t, uint32_t> mapTopNVid2Score;
	set<uint64_t> setTopNVids;//topN vid列表
	while(!oMinHeap.empty())
	{
		auto pair = oMinHeap.top();
		oMinHeap.pop();
		setTopNVids.insert(pair.second);
		mapTopNVid2Score[pair.second] = pair.first;
        cout<< pair.first << ":"<<pair.second<<endl;
	}



    return 0;
}