#include <iostream>
#include <stack>
#include <string>
using namespace std;
bool is_operator(char c){
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')')
        return true;
    else
        return false;
}
int priority(char op){
    if(op==')') return 0;
    if(op=='+'||op=='-') return 1;
    if(op=='*'||op=='/') return 2;
    if(op=='(') return 3;
}
int base_cal(char op, int left_operand, int right_operand){
    switch(op){
        case '+': return left_operand+right_operand;
        case '-': return left_operand-right_operand;
        case '*': return left_operand*right_operand;
        case '/': return left_operand/right_operand;
        default: return 0;
    }
}
void pop_stack(stack<char>& operators, stack<int>& operands, char op=')'){
    int left_operand, right_operand;
    char stack_op;
    while(!operators.empty() && operators.top() != '('){
        if(priority(operators.top()) < priority(op)){
            break;
        }
        right_operand = operands.top();
        operands.pop();
        left_operand = operands.top();
        operands.pop();
        stack_op = operators.top();
        operators.pop();
        operands.push(base_cal(stack_op, left_operand, right_operand));
    }
    if(op == ')' && !operators.empty() && operators.top() == '(')
        operators.pop();
    if(op != ')') operators.push(op);
}
int two_stack_cal(string s){
    stack<char> operators;
    stack<int> operands;
    for(auto it=s.begin(); it!=s.end();){
        if(is_operator(*it)){
            if(operators.empty() || priority(operators.top()) < priority(*it)){
                operators.push(*it);
            }else{
                pop_stack(operators, operands, *it);
            }
            ++it;
        }else{
            operands.push(atoi(s.substr(it-s.begin()).c_str()));
            while(it!=s.end() && *it>='0' && *it<='9') ++it;
        }
    }
    pop_stack(operators, operands);
    return operands.top();
}
int main(){
    string s("(3-12)*4*8/(8/4+8)-35");
    cout<<two_stack_cal(s)<<'\n';
    return 0;
}
