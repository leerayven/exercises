#include <iostream>
//#include "heap.h"
#include <stdlib.h>
#include "max_priority_queue.h"
int main(){
    //vector<int> nums = {32,45,65,12,34,6,2,6,7,2,1};
    /*
    heapsort(nums);
    for(auto num : nums){
        cout<<num<<",";
    }
    cout<<endl;
    */
    vector<int> nums;
    MaxPriorityQueue queue(nums);
    srand(0);
    for(int i = 0; i != 10; ++i){
        queue.insert(rand()%100);
    }
    int key;
    for(;;){
        key = queue.extract_max();
        if(key < 0)
            break;
        cout<<key<<"  ";
    }
    cout<<endl;
    return 0;
}
