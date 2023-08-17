#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

    int partition(vector<int>& nums, int left, int right)
    {
        if(left >= right)
            return left;
        int base = nums[left];
        int l = left, r = right;
        while(l < r)
        {
            while(l < r && nums[r] >= base)
                r--;
            while(l < r && nums[l] <= base)
                l++;
            if(l < r)
            {
                std::swap(nums[l], nums[r]);
                //cout<<"swap:"<<nums[l]<<"|"<<nums[r]<<endl;
            }
        }
        std::swap(nums[left], nums[r]);
        //cout<<"partition|"<<left<<"|"<<right<<"|"<<r<<endl;
        return r;
    }
    void find(vector<int>& nums, int k, int left, int right)
    {
        if(left >= right)
            return;
        
        int index = partition(nums, left, right);
        cout<<left<<"|"<<right<<"|"<<index<<"|"<<endl;
        copy(nums.begin(), nums.end(), ostream_iterator<int>(cout, " "));
        cout<<endl;
        if(index == nums.size() - k)
            return;
        find(nums, k, left, index - 1);
        find(nums, k, index + 1, right);
        return;
    }


int main()
{
    vector<int>nums{3,2,1,5,6,4};
    int k = 2;
    find(nums, k, 0, nums.size() - 1);
    copy(nums.begin(), nums.end(), ostream_iterator<int>(cout, " "));
    cout<<endl;
    cout<<nums[nums.size() - k]<<endl;
    return 0;
}
