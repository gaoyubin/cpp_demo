#include <iostream>
#include <vector>
using namespace std;
int CreateZinzag(int n, int m)
{
    vector<vector<int>>vv(n, vector<int>(m,0));
    int up_r = 0, up_c = 1;
    int down_r = 0, down_c = 0;
    bool reverse = false;
    int b_num = 1;
    for(int i = 0; i < m+n-1; i++)
    {
        if(reverse == true)
        {
            int tmp_r = up_r;
            int tmp_c = up_c;
            while(tmp_c >= 0 && tmp_r < n)
                vv[tmp_r++][tmp_c--] = b_num++;
            if(up_c + 2 <= m -1)
                up_c += 2;
            else if(up_c + 1 == m -1)
            {
                up_c = m -1;
                up_r += 1;

            }
            else if(up_c == m -1)
            {
                up_c = m -1;
                up_r += 2;
            }

        }
        else
        {
            int tmp_r = down_r;
            int tmp_c = down_c;
            while(tmp_r >= 0 && tmp_c < m)
                vv[tmp_r--][tmp_c++] = b_num++;
            
            if(down_r + 2<= n -1)
                down_r += 2;
            else if(down_r + 1 == n -1)
            {
                down_r = n -1;
                down_c += 1;
            }
            else if(down_r == n -1)
            {
                down_r = n -1;
                down_c += 2;
            }

        }
        reverse = !reverse;
    }
    for(int i = 0; i < vv.size(); i++)
    {
        for(int j = 0; j < vv[i].size(); j++)
        {
            cout<<vv[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}

int main()
{
    CreateZinzag(4, 3);
}
