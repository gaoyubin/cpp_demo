#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

#define shit(a, b)  a ## .has_ ## b();

shit(qq, bb)

int main()
{
    time_t timestamp = 100*3600;
    struct tm tm;
    localtime_r(&timestamp, &tm);
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    cout<<mktime(&tm)<<endl;

    //string strMail = "sdfaf<123@aa.com>sdfsf";
    string strMail="test <appleybgao@tencent.com>";
    auto uBegin = strMail.find("<");
    auto uEnd = strMail.rfind(">");
    string strSub = strMail.substr(uBegin + 1, uEnd - uBegin-1);
    cout<<strSub<<endl;
    cout<<uBegin<<" "<<uEnd;
    char *ptr;
    cout<<std::strtod("0.28", &ptr)<<endl;
    printf("字符串部分是 |%s|", ptr);

}