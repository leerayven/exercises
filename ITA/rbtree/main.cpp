#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "rbtree.h"
using namespace std;

typedef rbtree<int> rbtree_int;

int main(){
    rbtree<int> tree;
    srand(time(NULL));
    //insert
    for(int i = 0; i != 100; ++i){
        tree.insert(rand());
    }
    vector<int> heights;
    tree.traverse_log(heights);
    for(auto it=heights.begin(); it != heights.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;
    return 0;
}
