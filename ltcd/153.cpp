/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

You may assume no duplicate exists in the array.

Example 1:

Input: [3,4,5,1,2] 
Output: 1
Example 2:

Input: [4,5,6,7,0,1,2]
Output: 0
*/
#include <vector>
#include <iostream>
using namespace std;
int find_min(const vector<int>& nums){
    if(nums.empty()) return 0;
    if(nums.size() == 1) return nums[0];
    int mid = 0;
    int i = 0;
    for(int j = nums.size()-1; i <= j; ){
        if(nums[i] <= nums[j]) return nums[i];
        mid = (i+j)/2;
        if(nums[mid] < nums[j]){
            j = mid;
        }else if(nums[mid] >= nums[i]){
            i = mid+1;
        }
    }
}
/*
int find_target(vector<int>& nums, int target){
    if(nums.empty()) return -1;
    int i = 0;
    for(int j = nums.size(); i != j; ){
        int mid = (i+j)/2;
        if(nums[mid] == target) return mid;
        if(nums[mid] > target) j = mid;
        if(nums[mid] < target) i = mid+1;
    }
    return -1;
}
*/

int main(){
    vector<int> nums = {0,6};
    cout<<find_min(nums)<<'\n';
}
