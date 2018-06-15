class Solution {
public:
    int myAtoi(string str) {
        int64_t result=0;
        bool pos_f = true;
        bool empty = true;
        for(auto it=str.begin(); it!=str.end(); ++it){
            if(*it == ' ' && empty == true) continue;
            if(*it >= '0' && *it <= '9'){
                empty = false;
                result *= 10;
                result += *it-'0';
                if(result > INT32_MAX)
                    return pos_f?INT32_MAX:INT32_MIN;
            }else if(*it == '-' || *it == '+'){
                if(empty){
                    empty = false;
                    pos_f = *it == '-'?false:true;
                }else{
                    break;
                }
            }else{
                break;
            }
        }
        result = pos_f?result:(-1*result);
        if(result > INT32_MAX) return INT32_MAX;
        if(result < INT32_MIN) return INT32_MIN;
        return result;

    }
};
