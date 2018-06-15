/*
Given an input string, reverse the string word by word.

Example:  

Input: "the sky is blue",
Output: "blue is sky the".
Note:

A word is defined as a sequence of non-space characters.
Input string may contain leading or trailing spaces. However, your reversed string should not contain leading or trailing spaces.
You need to reduce multiple spaces between two words to a single space in the reversed string.
Follow up: For C programmers, try to solve it in-place in O(1) space.
 */

/*
 * solution:
 * reduce unneccessary spaces
 * reverse the whole string
 * reverse evey word
 */
#include <string.h>
#include <stdio.h>
void reverse(char *s, int start, int end){
    for(int i = start, j = end; i < j; ++i, --j){
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}
void reverseWords(char *s) {
    //printf("len:%d, %s\n",int(strlen(s)), s);
    int len = strlen(s);
    int j = 0;
    //开始部分不会被覆盖
    bool keep_space = s[0] == ' '? false:true;
    for(int i = 0; i != len; ++i){
        //考虑得不够全面，
        if(i == j && (keep_space == true || s[i] != ' ')){ 
            ++j;
        }else if( i != j &&(keep_space == true || s[i] != ' ')){
            s[j++] = s[i];
        }
        if(s[i] != ' '){
            keep_space = true;
        }else{
            keep_space = false;
        }
    }
    len = j;
    //strlen 返回的长度不包括\0
    s[len] = '\0'; 
    if(s[len-1] == ' '){
        s[len-1] = '\0';
        --len;
    }
    //printf("len:%d, %s\n",int(strlen(s)), s);
    if(len <= 2) return;
    reverse(s, 0, len-1);
    j = 0;
    for(int i = 0; i != len+1; ++i){
        if(s[i] == ' ' || i == len){
            reverse(s, j, i-1);
            j = i+1;
        }
    }
}

int main(){
    //char s[] = "the   sky      is blue";
    char s[] = "the sky is blue";
    reverseWords(s);
    printf("len:%d, %s\n",int(strlen(s)), s);
}
