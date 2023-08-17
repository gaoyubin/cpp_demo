#include <iostream>
#include <vector>
#include <map>
using namespace std;
int main()
{
    int req_size = 100000;
    vector<int>v(req_size, 0);
    map<int,int>m;
    int range = 100000;
    srand( (unsigned)time(NULL) );
    cout<<RAND_MAX-RAND_MAX%range<<endl;
    cout<<RAND_MAX-(RAND_MAX-5)%6<<endl;
    for(int i = 0; i < req_size; i++)
    {
        // srand(time(0));
        // int req = rand() % 6 + 1;
        // // cout<<req<<endl;
        // // v[req-1]++;
        // m[req]++;
        int n;
        // while((n = rand()) > RAND_MAX - RAND_MAX % range);
        // while( ( n = rand() ) > RAND_MAX - (RAND_MAX-5)%6 );
        n =  rand();
        m[n%range+1] ++;
    }
    int n_zeor = 0;
    cout<<m.size()<<endl;
    // for(const auto& pair : m)
    //     cout<<pair.first<<":"<<pair.second<<endl;
    

    /*
    int zero_size = 0;
    for(int i = 0; i < v.size(); i++)
    {
        // if(v[i] < 1)
            zero_size++;
        // cout<<i<<":"<<v[i]<<endl;
    }
    cout<<zero_size<<endl;
    */
//         unsigned long j;
//     srand( (unsigned)time(NULL) );

//     map<int,int>m;
//     for( j = 0; j < 100500; ++j )
//     {
//         int n;

//         /* skip rand() readings that would make n%6 non-uniformly distributed
//           (assuming rand() itself is uniformly distributed from 0 to RAND_MAX) */
//         while( ( n = rand() ) > RAND_MAX - (RAND_MAX-5)%6 )
//         { /* bad value retrieved so get next one */ }
//         m[n % 6 + 1]++;
//         //printf( "%d,\t%d\n", n, n % 6 + 1 );
//     }
//     for(const auto& pair : m)
//         cout<<pair.first<<":"<<pair.second<<endl;

}