/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".
Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
*/
#include <string>
using namespace std;
bool isMatch_inn(string& s, string& p, int i, int j){
    if(i==0 && j==0) return true;
    if(i!=0 && j==0) return false;
    if(j!=0 && p[j-1]!='*'){
        return i!=0 && (s[i-1]==p[j-1] || p[j-1]=='.') && isMatch_inn(s, p, i-1, j-1);
    }
    if(j!=0 && p[j-1]=='*'){
        return isMatch_inn(s, p, i, j-2) || isMatch_inn(s, p, i, j-1) \
            ||(i!=0 && (s[i-1]==p[j-2] || p[j-2]=='.') && isMatch_inn(s, p, i-1, j));
    }
}
class Solution {
public:
    bool isMatch(string s, string p) {
        return isMatch_inn(s, p, s.length(), p.length());   
    }
};
