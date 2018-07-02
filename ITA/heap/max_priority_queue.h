#include "heap.h"
/**
 * All keys are guaranteed to be positive integers.
 */
class MaxPriorityQueue{
public:
    MaxPriorityQueue(const vector<int>& keys);
    void insert(int key);
    int maximum();
    int extract_max();
    void increase_key(int key, int new_key);
private:
    int findByKey(int key);
    vector<int> heap;
};

MaxPriorityQueue::MaxPriorityQueue(const vector<int>& keys):heap(keys){
    build_max_heap(heap);
}

void MaxPriorityQueue::insert(int key){
    heap.push_back(0);
    increase_key(heap.size()-1, key);
}

void MaxPriorityQueue::increase_key(int idx, int new_key){
    if(heap.at(idx) >= new_key)
        return;
    heap[idx] = new_key;
    for(int i = idx; i > 0 && heap.at(i) > heap.at(get_parent(i)); i = get_parent(i)){
        swap(heap.at(i), heap.at(get_parent(i)));
    }
}

int MaxPriorityQueue::maximum(){
    if(heap.empty())
        return -1;
    return heap.at(0);
}

int MaxPriorityQueue::extract_max(){
    if(heap.empty())
        return -1;
    int max_key = heap.at(0);
    heap.at(0) = heap.at(heap.size()-1);
    heap.erase(heap.end()-1);
    max_heapify(heap, 0);
    return max_key;
}

