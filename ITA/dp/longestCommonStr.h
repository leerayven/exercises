#include <vector>
#include <string>
using namespace std;

enum PathDirection{
    Direction_Empty= 0,
    Direction_Left,
    Direction_Up,
    Direction_UpLeft
};

string longestCommonStr(const string& str1, const string& str2)
{
    string result;
    if(str1.empty() || str2.empty())
        return result;
    vector<vector<pair<int, PathDirection>>> record(str1.length()+1, vector<pair<int, PathDirection>>(str2.length()+1, make_pair(0, Direction_Empty)));
    for(unsigned int i = 1; i <= str1.length(); ++ i){
        for(unsigned int j = 1; j <= str2.length(); ++ j){
            if(str1.at(i-1) == str2.at(j-1)){
                record[i][j] = make_pair(record[i-1][j-1].first+1, Direction_UpLeft);
            }else if(record[i][j-1].first <= record[i-1][j].first){
                record[i][j].first = record[i-1][j].first;
                record[i][j].second = Direction_Up;
            }else{
                record[i][j].first = record[i][j-1].first;
                record[i][j].second = Direction_Left;
            }
        }
    }
    for(unsigned int i = str1.length(), j = str2.length(); i != 0 && j != 0; ){
        if(record[i][j].second == Direction_UpLeft){
            result.insert(0, 1, str1.at(i-1));
            -- i;
            -- j;
        }else if(record[i][j].second == Direction_Up){
            -- i;
        }else{
            -- j;
        }
    }
    return result;
}
