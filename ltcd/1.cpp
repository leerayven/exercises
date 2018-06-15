#include <iostream>
#include <vector>
using namespace std;
//***************
template<typename T>
void sort_vec(vector<T>& nums);
bool operator<(const pair<int, int>& p1, const pair<int, int>& p2){
    return p1.first < p2.first;
}
bool operator==(const pair<int, int>& p1, const pair<int, int>& p2){
    return p1.first == p2.first;
}

//***************
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target);
};
vector<int> Solution::twoSum(vector<int>& nums, int target){
    vector<int> result;
    if(nums.empty()) return result;
    vector<pair<int, int>> pairs;
    for(size_t i=0; i != nums.size(); ++i){
        pairs.push_back(make_pair(nums[i], i)); 
    }
    sort_vec(pairs);
    for(int i=0, j=nums.size()-1; i != j;){
        int tmp = pairs[i].first + pairs[j].first;
        if(tmp == target){
            result.push_back(pairs[i].second);
            result.push_back(pairs[j].second);
            break;
        }
        if(tmp < target) ++i;
        if(tmp > target) --j;
    }
    return result;
    
}
template<typename T>
void quick_sort(vector<T>& nums, int i, int j);
template<typename T>
void sort_vec(vector<T>& nums){
    if(nums.size() <= 1) return;
    quick_sort(nums, 0, nums.size()-1);
}
template<typename T>
void quick_sort(vector<T>& nums, int i, int j){
    if(i >= j) return;
    int pivot = j;
    while(i < j){
        if(nums[i] < nums[pivot] || nums[i] == nums[pivot]){
            ++i;
        } else if(nums[pivot] < nums[j]){
            --j;
        } else {
            swap(nums[i], nums[j]);
        }
    }
    if(i != pivot && nums[i] > nums[pivot]) swap(nums[i], nums[pivot]);
    if(i != 0){
        quick_sort(nums, 0, i-1);
    }
    if(i != pivot){
        quick_sort(nums, i+1, pivot);
    }
}
/*
template<typename T>
void print_v(vector<T>& nums){
    for(typename vector<T>::iterator it = nums.begin(); it != nums.end(); ++it){
        cout<<*it<<' ';
    }
    cout<<'\n';
}
*/
int main(){
    vector<int> nums({11, 5, 77777771, 4, 5, 17, 3});
    Solution s;
    vector<int> result = s.twoSum(nums, 16);
    for(auto idx: result){
        cout<<idx<<' ';
    }
    return 0;
}
