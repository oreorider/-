#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Stack{
    private: 
        int current;
        int size;
        T * array;

    public:
        Stack<T> (int _size = 16)
        {   
            current = -1;
            size = _size;
            array = new T[_size];
        }
        ~Stack()
        {
            delete[] array;
        }    

        bool isEmpty() const;
        bool isFull() const;
        T top() const;
        T pop();
        void push(const T& item);
};

template <typename T>
bool Stack<T>::isEmpty() const{
    if(current == -1) return true;
    else return false;
    
}

template <typename T>
bool Stack<T>::isFull() const{
    if(current == size-1) return true;
    else return false;
}

template <typename T>
T Stack<T>::top() const{
    if(isEmpty()){
        throw underflow_error("stack is empty");
    }
    else return array[current];
    
}

template <typename T>
T Stack<T>::pop(){
    cout<<"pop"<<endl;
    if(isEmpty()){
        cout<<"empty"<<endl;
        //throw underflow_error("stack is emtpy");
    }
    auto returnValue = array[current];
    current-=1;
    return returnValue;
}

template <typename T>
void Stack<T>::push(const T& item){
    //TODO
    if(isFull()){ //if stack is full, double size, then push
        auto new_array = new T[size*2];
        for(int i=0; i<size;i++){
            new_array[i] = array[i];//copy elements over
        }
        size=size*2;
        delete[] array;
        array = new_array;
        current+=1;
        array[current] = item;
    }
    else{
        current+=1;
        array[current] = item;
    }
    return;
}

bool checkParentheses(const string& line, const vector<pair<char,char>>& pairs);
float calculate(const string& line);