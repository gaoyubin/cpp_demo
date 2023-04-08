#include<iostream>
#include<vector>
#include <iterator>
#include <iostream>
#include <time.h>
using namespace std;
int main()
{
    vector<uint32_t>vecDaysOfMonth = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    struct tm tm;
    time_t starttime = time(NULL);
    cout<<starttime<<endl;
    cout<<endl;
    localtime_r(&starttime, &tm);
    int daysofmonth = vecDaysOfMonth[tm.tm_mon];
    vector<uint32_t> vecWorkDayThisMonth;
    vector<uint32_t> vecWeekDayThisMonth;
    for(int i = 0; i <  daysofmonth; i++)
    {
        tm.tm_mday=i+1;
        time_t tIndextime = mktime(&tm);
        cout<<tIndextime<<endl;
        struct tm tmIndex;
        localtime_r(&tIndextime, &tmIndex);
        if(tmIndex.tm_wday != 0 && tmIndex.tm_wday != 6)
        {
            vecWorkDayThisMonth.push_back(tmIndex.tm_mday);
        }
        else
        {
            vecWeekDayThisMonth.push_back(tmIndex.tm_mday);
        }
    }

    copy(vecWorkDayThisMonth.begin(), vecWorkDayThisMonth.end(), ostream_iterator<uint32_t>(cout, ","));
    cout<<endl;
    copy(vecWeekDayThisMonth.begin(), vecWeekDayThisMonth.end(), ostream_iterator<uint32_t>(cout, ","));
    cout<<endl;

}