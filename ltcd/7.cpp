/*
Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21
Note:
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/
class Solution {
public:
    int reverse(int x) {
        int64_t y = x;
        bool pos_f = true;
        if(y < 0){
            y = -y;
            pos_f = false;
        }
        int64_t z = 0;
        while(y){
            z *= 10;
            z += y%10;
            y /= 10;
        }
        if(pos_f && z > INT32_MAX) return 0;
        if((!pos_f)&& z < INT32_MIN) return 0;
        if(pos_f) 
            return y;
        else
            return -y;
    }
};
