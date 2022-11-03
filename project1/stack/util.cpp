#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "stack.hpp"

using namespace std;

bool checkParentheses(const string& line, const vector<pair<char,char>>& pairs){
    //TODO
    char popvalue;
    Stack<char> parentheses;
    for (auto &ch : line){
        for(auto pair : pairs){
            if(ch == pair.first){//if the character is first element of pairs
                parentheses.push(ch);
                continue;
            }
            else if(ch == pair.second){
                if(!parentheses.isEmpty() && parentheses.top() == pair.first){ //if matching, pop
                    popvalue = parentheses.pop();
                }
                else{
                    return false;
                }
            }
        }
    }
    return true;
}

int precedence(char ch){
    if(ch == '+' || ch == '-') return 1;
    if(ch == '*' || ch == '/') return 2;
    else return 0;
}

string infix_to_postfix(const string &line){
    Stack<char> stk;
    string postfix = "";
    for(int i=0; i<line.length(); i++){
        if((int(line[i])>=48 && int(line[i])<=57) || int(line[i]) == 46){//if number or decimal
            while((int(line[i])>=48 && int(line[i])<=57) || int(line[i]) == 46){
                postfix.push_back(line[i]);
                i+=1;
            }
            postfix.push_back(' ');
            i-=1;
        }
        else if(line[i] == '('){
            stk.push('(');
            if(line[i+1] == '-'){
                stk.push('0');
                i++;
            }
            
        }
        else if(line[i] == ')'){
            while(!stk.isEmpty() && stk.top() != '('){
                postfix.push_back(stk.pop());
            }
        }
        else{
            if(precedence(line[i]) > precedence(stk.top())){
                stk.push(line[i]);
            }
            else{
                while(!stk.isEmpty() && precedence(line[i])<=precedence(stk.top())){
                    postfix.push_back(stk.pop());
                }
                stk.push(line[i]);
            }
        }
    }
    while(!stk.isEmpty()){
        postfix.push_back(stk.pop());
    }
    return postfix;
}

float calculate(const string& line){
    //TODO
    Stack<float> numbers;
    Stack<char> operators;
    string postfix = infix_to_postfix(line);
    cout<<postfix<<endl;
    return 0.f;
}