#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
int Partition(vector<int>& nums, int left, int right)
{
    int base = nums[left];
    int base_index = left;
    while(left < right)
    {
        while(left < right && base <= nums[right])right--;
        while(left < right && base >= nums[left])left++;
        swap(nums[left], nums[right]);
    }
    swap(nums[base_index], nums[right]);
    return right;
}
int QuickSort(vector<int>& nums, int left, int right)
{
    if(left >= right)
        return 0; 
    int mid = Partition(nums, left, right);
    QuickSort(nums, left, mid - 1);
    QuickSort(nums, mid + 1, right);
    return 0;
}
int main()
{
    vector<int>nums{1,4,6,8,2,3,5,7,3};
    QuickSort(nums, 0, nums.size() - 1);
    copy(nums.begin(), nums.end(), ostream_iterator<int>(cout, " "));
    cout<<endl;
}