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
    string postfix = " ";
    for(int i=0; i<line.length(); i++){
        if((int(line[i])>=48 && int(line[i])<=57) || int(line[i]) == 46){//if number or decimal
            while((int(line[i])>=48 && int(line[i])<=57) || int(line[i]) == 46){
                postfix.push_back(line[i]);
                i+=1;
            }
            postfix.push_back(' ');
            i-=1;
        }
        else if(i==0 && (line[i] == '+' || line[i] == '-')){//if line starts with + or -
            if(line[0] == '-'){
                postfix.append(line.substr(0,1));//include - 
                i+=0;
            }
            else if(line[0] == '+'){
                postfix.append(line.substr(1,1));//dont include +
                i+=1;
            }
        }
        else if(line[i] == '('){
            stk.push('(');
            if(line[i+1] == '-'){//(-6...
                string neg_num_string = line.substr(i+1, 1);//include - in front in the postfix string
                postfix.append(neg_num_string);
                i+=1;
            }
            if(line[i+1] == '+'){
                postfix.append(line.substr(i+2, 1));//dont include + sign in postfix string
                i+=2;
            }
            
        }
        else if(line[i] == ')'){
            while(!stk.isEmpty() && stk.top() != '('){
                postfix.push_back(stk.pop());
                postfix.push_back(' ');
            }
            stk.pop();
        }
        else{
            if(stk.isEmpty() || precedence(line[i]) > precedence(stk.top())){
                stk.push(line[i]);
            }
            else{
                while(!stk.isEmpty() && precedence(line[i])<=precedence(stk.top())){
                    postfix.push_back(stk.pop());
                    postfix.push_back(' ');
                }
                stk.push(line[i]);
            }
        }
    }
    while(!stk.isEmpty()){
        postfix.push_back(stk.pop());
        postfix.push_back(' ');
    }
    
    return postfix;
}

bool contains_digit(const string& line){
    for(auto ch : line){
        if((int(ch)>=48 && int(ch)<=57) || int(ch) == 46){//if any of the characters are numbers return true
            return true;
        }
    }
    return false;
}

float calculate(const string& line){
    //TODO
    Stack<float> numbers;
    Stack<char> operators;
    string postfix = infix_to_postfix(line);
    //cout<<postfix<<endl;
    int space_start = 0;
    int space_end = 0;
    float new_val = 0;
    float temp = 0;
    for(int i=0; i<postfix.length(); i++){
        space_start = postfix.find(' ', i);//search next space from current index
        space_end = postfix.find(' ', space_start+1);//search the space after that from space_start
        
        if(space_end == -1) break;
        string element = postfix.substr(space_start+1, space_end-space_start-1);
        if(contains_digit(element)){
            float num = stof(element);
            numbers.push(num);
            //cout<<"pushing "<<num<<" to num stack"<<endl;
        }
        else if(!contains_digit(element)){ //if operator
            if(element == "+") new_val = numbers.pop() + numbers.pop();
            if(element == "*") new_val = numbers.pop() * numbers.pop();
            if(element == "-"){
                temp = numbers.pop();
                new_val = numbers.pop() - temp;
            }
            if(element == "/"){
                temp = numbers.pop();
                if(temp == 0){
                    throw overflow_error("divide by zero");
                }
                new_val = numbers.pop() / temp;
            }
            numbers.push(new_val);
        }
        //cout<<"element is : "<<element<<endl;
        i=space_end-1;
    }
    //cout<<"answer is "<<numbers.top()<<endl;
    return numbers.top();
}