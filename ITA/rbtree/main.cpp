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
    return 0;
}
