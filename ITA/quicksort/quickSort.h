#include <vector>
using namespace std;

void partition(vector<int>* nums, int start, int end){
    if(start >= end)
        return;
    int pivot = nums->at(end);
    int i = start, j = end-1;
    for(; i <= j; ){
        if(nums->at(i) <= pivot){
            ++ i;
        }else if(nums->at(j) > pivot){
            -- j;
        }else{
            swap(nums->at(i), nums->at(j));
        }
    }
    swap(nums->at(i), nums->at(end));
    partition(nums, start, i-1);
    partition(nums, i+1, end);
}

//v2 to leverage the cache space locality
void partition_v2(vector<int>* nums, int start, int end){
    if(start >= end)
        return;
    int pivot = nums->at(end);
    int i = start, store_idx = start;
    for(; i <= end; ++ i){
        if(nums->at(i) <= pivot)
            swap(nums->at(store_idx++), nums->at(i));
    }
    //swap(nums->at(store_idx), nums->at(end));
    //pivote is at store_idx-1;
    partition_v2(nums, start, store_idx-2);
    partition_v2(nums, store_idx, end);
}

void quick_sort(vector<int>* nums){
    if(nums->size() < 2)
        return;
    partition_v2(nums, 0, nums->size()-1);
}
