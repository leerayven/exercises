/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#define NULL 0
#include <stack>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    Solution():result(NULL){}
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;
        int sum = 0;
        int carry = 0;
        result = new ListNode(0);
        ListNode *curNode = result;
        ListNode* node = NULL;
        for(; !(l1==NULL && l2==NULL);){
            sum = carry;
            if(l1){
                sum += l1->val;
                l1 = l1->next;
            }
            if(l2){
                sum += l2->val;
                l2 = l2->next;
            }
            node = new ListNode(sum%10);
            carry = sum/10;
            curNode->next = node;
            curNode = node;
        }
        if(carry){
            node = new ListNode(carry);
            curNode->next = node;
        }
        curNode = result;
        result = result->next;
        delete curNode;
        return result;
    }
    ~Solution(){
    /*
        ListNode* curNode = NULL;
        for(;result;){
            curNode = result;
            result = result->next;
            delete curNode;
        }
        */
    }
private:
    ListNode* result;
};

