/*

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I
*********************
0,6,12...
1,5,7,
...

0, +2n, +2n, ...
1, +2*(n-1), +2*(1), ...
2, +2*(n-2), +2*(2), ...

 */

#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows <= 0) return s;  // assert 
        int len = s.length();
        if(len <= numRows || numRows == 1) return s;
        string result(s);
        int idx = 0;
        for(int i=0; i != numRows; ++i){
            int line_idx = i;
            result[idx++] = s.at(line_idx);
            int inc;
            for(int j=1;; ++j){
                inc = 2*(i+(j%2)*(numRows-1-2*i));
                if(inc) 
                    line_idx += inc;
                else
                    continue;
                if(line_idx < len)
                    result[idx++] = s.at(line_idx);
                else
                    break;
            }
        }
        return result;
    }
};

