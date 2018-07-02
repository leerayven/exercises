#include <vector>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>
using namespace std;

void reservoirSampling(const vector<int>& nums, unsigned int sample_size, vector<int>* samples)
{
    samples->clear();
    for(unsigned int i = 0; i != nums.size(); ++i){
        if(i < sample_size){
            samples->push_back(nums[i]);
        }else{
            if(rand()%(i+1) < sample_size){
                samples->at(rand()%sample_size) = nums[i];
            }
        }
    }
}

int main(){
    srand(time(NULL));
    vector<int> nums, samples;
    for(int i = 0; i != 100; ++ i){
        nums.push_back(i);
    }
    map<int, int> statistics;
    for(int i = 0; i != 10000; ++i){
        reservoirSampling(nums, 10, &samples);
        for(auto sample: samples){
            ++ statistics[sample];
        }
    }
    for(auto it = statistics.begin(); it != statistics.end(); ++ it){
        cout<<it->first<<": "<<it->second<<endl;
    }
}
