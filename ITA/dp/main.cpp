//#include "longestCommonStr.h"
#include "matrixChain.h"
#include <iostream>
int main(){
    /*
    string str1("ACCGGTCGAGTGCGCGGAAGCCGGCCGAA");
    string str2("GTCGTTCGGAATGCCGTTGCTCTGTAAA");
    cout<<str1<<endl<<str2<<endl<<longestCommonStr(str1, str2)<<endl;
    */
    vector<int> matries = {30, 35,15,5,10,20,25};
    cout<<matrixChainOrder(matries);

    return 0;
}
