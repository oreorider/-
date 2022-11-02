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
                if(parentheses.top() == pair.first){ //if matching, pop
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

string infix_to_postfix(string line){
    Stack<char> stk;
    string returnString = "";
    for(auto &ch : line){
        if(int(ch)>=48 && int(ch)<=57){//if number

        }
    }
}

float calculate(const string& line){
    //TODO
    Stack<float> numbers;
    Stack<char> operators;
    string postfix = infix_to_postix(line);
    return 0.f;
}