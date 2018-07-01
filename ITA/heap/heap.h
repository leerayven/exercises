#include <vector>
using namespace std;
static inline int get_parent(int i){
    return (i-1) >> 1;
}

static inline int get_left(int i){
    return (i << 1) | 1;
}

static inline int get_right(int i){
    return (i << 1) + 2;
}

void max_heapify(vector<int>& nums, int i, int heap_size = 0){
    int size = heap_size != 0 ? heap_size : static_cast<int>(nums.size());
    int parent, left, right;
    int idx = i;
    for(;;){
        parent = nums[idx];
        // nums are guaranted to be positive integers;
        left = get_left(idx)<size ? nums[get_left(idx)] : 0;
        right = get_right(idx)<size ? nums[get_right(idx)] : 0;
        if(parent >= left && parent >= right)
            break;
        if(left > right){
            swap(nums[idx], nums[get_left(idx)]);
            idx = get_left(idx);
        }else{
            swap(nums[idx], nums[get_right(idx)]);
            idx = get_right(idx);
        }
    }
}

void build_max_heap(vector<int>& nums){
    int size = static_cast<int>(nums.size());
     for(int i = (size-2)/2; i >= 0; --i){
        max_heapify(nums, i);
     }
}

void heapsort(vector<int>& nums){
    build_max_heap(nums);
    int size = static_cast<int>(nums.size());
    for(int i = size-1; i > 0; --i){
        swap(nums[0], nums[i]);
        max_heapify(nums, 0, i);
    }
}
