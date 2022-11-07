#include <iostream>

using namespace std;

template <typename T>
struct Item{
    T value;
    int priority;
};

template <typename T>
class Queue{
    private:
        int front;
        int rear;
        bool empty;
        int size;
        bool verbose;
        Item<T> *array;

    public:
        Queue<T>(int _size = 16)
        {
            front = 0;
            rear = _size - 1;
            empty = true;
            size = _size;
            verbose = false;
            array = new Item<T>[_size];
        }
        ~Queue(){
            delete[] array;
        }
        
        void setverbose();
        void enqueue(const T& value, int priority);
        int top();
        T dequeue();        
        bool isFull();
};

template <typename T>
void Queue<T>::setverbose(){
    verbose = true;
}

template <typename T>
void Queue<T>::enqueue(const T& value, int priority){
    Item<T> add_item{value, priority};
    if(empty){//if empty
        array[front] = add_item;
        rear=front;
        empty = false;
        if(verbose){
            cout<<"adding value: "<<value<<", priority "<<priority<<" to index "<<front<<endl;
        }
    }
    else if(isFull()){//if array is full
        auto new_array = new Item<T>[size*2];
        int a = 0;
        for(int i=front; i<size; i++){
            new_array[a] = array[i];//copy elements over
            a+=1;
        }
        for(int i=0; i<front; i++){
            new_array[a] = array[i];
            a+=1;
        }
        if(verbose){
            cout<<"doubled size of array because full"<<endl;
        }
        front = 0;
        rear = size;//rear incremented from size-1 to "size"
        size = size*2;//increase size
        delete[] array;
        array = new_array;
        array[rear] = add_item;
        if(verbose){
            cout<<"adding value: "<<value<<", priority "<<priority<<" to index "<<rear<<endl;
        }
    }
    else{//if array not empty, not full
        if(rear == size-1){//if rear is at the end of array
            array[0] = add_item;
            rear=0;
        }
        else{
            rear+=1;
            array[rear] = add_item;
        }
        if (verbose){
            cout<<"adding value: "<<value<<", priority "<<priority<<" to index "<<rear<<endl;
        }
    }
    return;
}

template <typename T>
int Queue<T>::top(){
    if(empty){throw underflow_error("queue is empty");}

    int highest_prio = -9999;
    int index = 0;
    if(front == rear) return front; //if only one elemnt in array
    if(front > rear){//if flipped
        for(int i=front; i<size; i++){
            if(array[i].priority > highest_prio){//if prio of array element higher than previous highest
                highest_prio = array[i].priority;
                index = i;
            }
        }
        for(int i=0; i<rear; i++){
            if(array[i].priority > highest_prio){
                highest_prio = array[i].priority;
                index = i;
            }
        }
    }
    if(rear > front){//if normal
        for(int i=front; i<=rear; i++){
            if(array[i].priority > highest_prio){
                highest_prio = array[i].priority;
                index = i;
            }
        }
    }
    //TODO
    //returning the array index of the highest priority item
    return index;
}

template <typename T>
T Queue<T>::dequeue(){
    //TODO
    int pop_index = top();
    Item<T> nullitem{NULL, -999};
    T returnvalue = array[pop_index].value; 
    if(pop_index == rear){//if pop index is last index of queue
        array[pop_index] = nullitem; //for debugging purposes
        rear-=1;
    }
    else{//if not, must allign again
        if(front > rear){ //if front behind rear
            for(int i=0; i<pop_index; i++){//move "front" part back one
                array[i+1] = array[i];
            }
            array[0] = array[size-1];//last index moves to index 0
            for(int i=front; i<size-1; i++){//move "back" part back one
                array[i+1] = array[i];
            }
            array[front] = nullitem;//for debugging
            front +=1;
        }
        else if(rear > front){//if rear behind front (normal case) 
            for(int i=front; i<pop_index; i++){
                array[i+1] = array[i];
            }
            array[front] = nullitem;
            front+=1;
        }
    }
    return returnvalue;
}

template <typename T>
bool Queue<T>::isFull(){
    //TODO
    if(empty) return false;
    if((front-1==rear) || (front==0 && rear==size-1)) return true;
    return false;
}