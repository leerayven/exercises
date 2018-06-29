#include <stdlib.h>
//#include <algorithm>
#include <time.h>
#include "rbtree.h"
using namespace std;

typedef rbtree<int> rbtree_int;

void printTreeInfo(rbtree_int& tree){
    vector<int> black_heights;
    vector<int> values;
    vector<int> heights;
    vector<bool> colors;
    tree.traverse(values, heights, colors);
    vector<int> leaf_values;
    tree.traverse_leaves(leaf_values, black_heights);
    
    for(uint32_t i=0; i != values.size(); ++i){
        cout<<values[i]<<","<<heights[i]<<","<<colors[i]<<"    ";
    }
    cout<<endl<<"*************"<<endl;
    for(auto it=leaf_values.begin(); it !=leaf_values.end(); ++it){
        int black_height;
        tree.lookup(*it, &black_height);
        cout<<black_height<<" ";
    }
    
    cout<<endl<<"*************"<<endl;
    for(auto it=black_heights.begin(); it != black_heights.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}
int main(){
    rbtree<int> tree;
    srand(time(NULL));
    //insert
#if 0    
    vector<int> orig_values = {3, 73, 9, 8};
#else
    vector<int> orig_values;
    for(int i = 0; i != 10; ++i){
        orig_values.push_back(rand()%1000);
    }
#endif
    for(uint32_t i = 0; i != orig_values.size(); ++i){
        cout<<(orig_values[i])<<"    ";
    }
    cout<<endl<<"*************"<<endl;

    for(uint32_t i = 0; i != orig_values.size(); ++i){
        tree.insert(orig_values[i]);
//        cout<<endl<<"iterator:"<<i<<endl;
//        printTreeInfo(tree);
    }
    printTreeInfo(tree);
    for(;!orig_values.empty();){
        int j = rand()%orig_values.size();
        int target = orig_values[j];
        int black_height;
        Node_t<int>* target_node = tree.lookup(target, &black_height);
        tree.remove(target_node);
        printTreeInfo(tree);
        orig_values.erase(orig_values.begin()+j);
    }
    return 0;
}
