#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include "stack.hpp"

using namespace std;

int main() {

    //You can check if your code works well.

    cout<<__cplusplus<<endl;

    Stack<int> s;

    cout<<boolalpha;
    cout<<s.isEmpty()<<endl;
    cout<<s.isFull()<<endl;
    
    s.push(10);
    for(int i=0; i<20; i++){
        s.push(i);
    }
    cout<<s.isEmpty()<<endl;
    cout<<s.isFull()<<endl;
    cout<<s.pop()<<endl;
    for(int i=0; i<10; i++){
        cout<<s.pop()<<endl;;
    }
    for(int i=15; i<20; i++){
        s.push(i);
    }
    
    pair<char,char> p = make_pair('(',')');
    vector<pair<char,char>> v;
    v.push_back(p);

    string a = "(3))";
    cout<<checkParentheses(a, v)<<endl;
    
    string expression = "-.5*(-3.+4)/3.2-9*3.14";
    //string postfix = infix_to_postfix(expression);
    //cout<<postfix<<endl;
    float answer = calculate(expression);
    cout<<expression<<" = "<<answer<<endl;
    //cout<<postfix<<endl;
    return 0;

}