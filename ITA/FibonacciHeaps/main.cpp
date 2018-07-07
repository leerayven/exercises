#include<stdlib.h>
#include<time.h>
#include "fibonacciHeap.h"

int main(){
    FibonacciHeaps heaps;
    srand(time(NULL));
    for(int i = 0; i != 10; ++i){
        heaps.insertKey(rand()%1000);
    }
    heaps.printHeaps();
    for(; !heaps.empty();){
        cout<<heaps.extractMin()<<endl;
        heaps.printHeaps();
    }
    return 0;
}
