/*
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.
*/
#include <vector>
using namespace std;
class Solution {
public:
    int maxArea(vector<int>& height) {
        if(height.size() <= 1) return 0;
        int result = 0;
        int space;
        for(int i = 0, j = height.size()-1; i != j; ){
            space = min(height[i], height[j])*(j-i);
            result = result<space?space:result;
            if(height[i] < height[j]){
                ++i;
            }else{
                --j;
            }
        }
        return result;
    }
};
