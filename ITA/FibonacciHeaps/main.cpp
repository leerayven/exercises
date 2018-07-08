#include<stdlib.h>
#include<time.h>
#include "fibonacciHeap.h"

int main(){
    FibonacciHeaps heaps;
    srand(time(NULL));
    for(int i = 0; i != 90; ++i){
        heaps.insertKey(rand()%1000);
    }
    //heaps.printHeaps();
    int count = 0;
    for(; !heaps.empty();){
        int key = heaps.extractMin();
        cout<<(count++)<<" "<<key<<"************************************"<<endl;
//        heaps.printHeaps();
        if(key == -1)
            break;
    }
    return 0;
}
