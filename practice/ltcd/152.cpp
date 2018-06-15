/*
Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

Example 1:

Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
Example 2:

Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/
#include <vector>
using namespace std;
int max_product(vector<int>& nums){
    if(nums.size() == 0) return 0;
    int max_so_far = nums[0];
    int max_ending_here = max_so_far;
    int min_ending_here = max_so_far;
    for(auto it = nums.begin()+1; it != nums.end(); ++it){
        max_ending_here = max(max(max_ending_here*(*it), min_ending_here*(*it)), *it);
        min_ending_here = min(min(min_ending_here*(*it), max_ending_here*(*it)), *it);
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}
