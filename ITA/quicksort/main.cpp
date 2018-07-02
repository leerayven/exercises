#include "quickSort.h"
#include <iostream>
#include <stdlib.h>
int main(){
    vector<int> nums;
    for(int i = 0; i != 20; ++i){
        nums.push_back(rand()%100);
    }
    quick_sort(&nums);
    for(auto num: nums){
        cout<<num<<" ";
    }
    cout<<endl;
}
