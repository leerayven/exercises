#include <vector>
#include <string>
using namespace std;

string matrixChainOrder(const vector<int>& matrixChain)
{
    string result;
    int numMatries = matrixChain.size()-1;
    if(numMatries < 2)
        return result;
    vector<vector<pair<uint64_t, int>>> record(numMatries, vector<pair<uint64_t, int>>(numMatries, make_pair(0,0)));
    for(int lenStep = 1; lenStep < numMatries; ++ lenStep){
        for(int start = 0; start < numMatries-lenStep; ++ start){
            uint64_t minCost = UINT64_MAX;
            int end = start + lenStep;
            int mStartEnd = matrixChain[start]*matrixChain[end+1];
            for(int split = start; split < end; ++ split){
                uint64_t cost = record[start][split].first + record[split+1][end].first \
                    + mStartEnd*matrixChain[split+1];
                if(cost < minCost){
                    record[start][end] = make_pair(cost, split);
                    minCost = cost;
                }
            }
        }
    }
    result = to_string(record[0][numMatries-1].first);
    return result;
}
