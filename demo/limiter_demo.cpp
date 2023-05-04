#include <iostream>
#include <set>
#include <map>
using namespace std;
class FixWindownLimiter
{
private:
    uint64_t last_ts = 0;
    uint32_t counter = 0;
    uint32_t limit = 0;
    uint32_t duration = 0;
public:
    FixWindownLimiter(uint32_t l, uint32_t d)
    {
        limit = l;
        duration = d;
        counter = 0;
        last_ts = 0;
    };
    bool tryAcquire()
    {
        time_t now = time(NULL);
        if(now - last_ts < duration)
        {
            if(counter < limit)
            {
                counter++;
                last_ts = now;
                return true;
            }
            else
                return false;
        }
        
        counter = 0;
        last_ts = now;
        return true;
    }
};

class SlideWindownLimter
{
private:
    uint64_t last_ts = 0;
    map<uint64_t, uint32_t> counter;
    uint32_t limit = 0;
    uint32_t duration = 0;
public:
    SlideWindownLimter(uint32_t l, uint32_t d)
    {
        limit = l;
        duration =d;
    }
    uint32_t getWindownCnt(const uint64_t& end_ts)
    {
        uint32_t win_cnt = 0;
        uint64_t begin_ts = 0;
        if(end_ts > duration)
            begin_ts = end_ts -duration;
             
        for(auto it = counter.begin(); it !=  counter.end();)
        {
            if(it->first < begin_ts)
                it = counter.erase(it);
            else
            {
                win_cnt += it->second;
                it++;
            }
        }
        return win_cnt;
    }
    bool tryAcquire()
    {
        uint64_t now = time(NULL);
        uint32_t win_cnt = getWindownCnt(now);
        if(win_cnt < limit)
        {
            counter[now]++;
            return true;
        }
        else
            return false;
    }
};

class LeakyBucketLimter
{
private:
    uint64_t last_ts = 0;
    int32_t limit = 0;
    int32_t left_water = 0;
    uint32_t leaky_rate = 0;//每秒钟漏桶速率
    
public:
    LeakyBucketLimter(uint32_t l, uint32_t rate)
    {
        limit = l;
        leaky_rate = rate;
    }
    bool tryAcquire()
    {
        uint64_t now = time(NULL);
        int32_t leaky_water = (now - last_ts)*leaky_rate;
        left_water = max(0, left_water - leaky_water);
        left_water = min(left_water, limit);
        if(left_water == limit)
            return false;
        else
        {
            left_water += 1;
            last_ts = now;
            return true;
        }
    }
};

class TokenBucketLimiter
{
private:
    int32_t limit = 0;
    uint64_t last_ts = 0;
    uint32_t token_rate = 0;
    int32_t left_token = 0;
public:
    TokenBucketLimiter(int32_t l, uint32_t t)
    {
        limit = l;
        token_rate = t;
    }
    bool tryAcquire()
    {
        uint64_t now  = time(NULL);
        uint32_t new_token = (now - last_ts) * token_rate;
        left_token += new_token;
        left_token = min(limit, left_token);
        if(left_token > 0)
        {
            left_token--;
            last_ts = now;
            return true;
        }
        else
            return false;
    }
};
int main()
{

}