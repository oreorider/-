#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include "queue.hpp"

using namespace std;

int main() {

    //You can check if your code works well.

    cout<<__cplusplus<<endl;

    Queue<int> q;
    //q.setverbose();

    cout<<boolalpha;
    cout<<q.isFull()<<endl;

    q.enqueue(1,2);
    q.enqueue(2,3);
    for(int i=0; i<14; i++){
        q.enqueue(99, 1);
    }

    cout<<q.isFull()<<endl;//should print true
    cout<<q.top()<<endl;//should print 1

    q.enqueue(101, 4);//should make array twice as large
    cout<<q.isFull()<<endl;//should print false

    cout<<q.dequeue()<<endl;//should print 101
    cout<<q.top()<<endl;//should print 1

    for(int i=0; i<10; i++){
        cout<<"index "<<q.top()<<" element dequeued, value: "<<q.dequeue()<<endl;
    }//front should be 10, rear 15, size 32
    cout<<"finished"<<endl; 

    for(int i=0; i<20; i++){//will loop around and add to index 0
        if(i==9){
            q.enqueue(1337, 4);//add to 25th index
        } 
        if(i==16){
            q.enqueue(301, 3);
        }
        else{
            q.enqueue(i, 2);
        } 

    }//front should abe 10, rear should be 3
    cout<<"index "<<q.top()<<endl;//should print 25
    cout<<"index "<<q.top()<<" element dequeued, value: "<<q.dequeue()<<endl;//pop 1337 @ index 25
    cout<<"index "<<q.top()<<" element dequeued, value: "<<q.dequeue()<<endl;//pop 1337 @ index 25
    return 0;

}