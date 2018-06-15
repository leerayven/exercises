/*
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: 3
Output: "III"
Example 2:

Input: 4
Output: "IV"
Example 3:
*/
#include <string>
using namespace std;
class Solution {
public:
    string intToRoman(int num); 
};
string Solution::intToRoman(int num){
    string result;
    int tmp;
    for(int base = 1000; base != 0; base /= 10){
        tmp = num/base;
        if(tmp == 0) continue;
        num %= base;
        if(base == 1000){
            result += string(tmp, 'M');
        }else if(base == 100){
            if(tmp < 4){
                result += string(tmp, 'C');
            }else if(tmp == 4){
                result += string("CD");
            }else if(tmp < 9){
                result += string("D");
                result += string(tmp-5, 'C');
            }else if(tmp == 9){
                result += string("CM");
            }
        }else if(base == 10){
            if(tmp < 4){
                result += string(tmp, 'X');
            }else if(tmp == 4){
                result += string("XL");
            }else if(tmp < 9){
                result += string("L");
                result += string(tmp-5, 'X');
            }else if(tmp == 9){
                result += string("XC");
            }
        }else{
            if(tmp < 4){
                result += string(tmp, 'I');
            }else if(tmp == 4){
                result += string("IV");
            }else if(tmp < 9){
                result += string("V");
                result += string(tmp-5, 'I');
            }else if(tmp == 9){
                result += string("IX");
            }
        }
    }
    return result;
}
