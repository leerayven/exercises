/*
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

*/
#include <string>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int result = 0;
        int start = 0;
        unordered_map<char, int> char_pos;
        for(int i = 0; i != s.length(); ++i){
            if(char_pos.find(s[i]) != char_pos.end() && char_pos[s[i]] >= start){
                result = (result<(i-start))?(i-start):result;
                start = char_pos[s[i]] + 1;
            }
            char_pos[s[i]] = i;
        }
        result = (result<(s.length()-start))?(s.length()-start):result;
        return result;
    }
};
