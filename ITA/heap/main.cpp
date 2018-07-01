#include <iostream>
#include "heap.h"
int main(){
    vector<int> nums = {32,45,65,12,34,6,2,6,7,2,1};
    heapsort(nums);
    for(auto num : nums){
        cout<<num<<",";
    }
    cout<<endl;
    return 0;
}
