#include <iostream>

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
        Item<T> *array;

    public:
        Queue<T>(int _size = 16)
        {
            front = 0;
            rear = _size - 1;
            empty = true;
            size = _size;
            array = new Item<T>[_size];
        }
        ~Queue(){
            delete[] array;
        }

        void enqueue(const T& value, int priority);
        int top();
        T dequeue();        
        bool isFull();
};

template <typename T>
void Queue<T>::enqueue(const T& value, int priority){
    Item<T> add_item{value, priority};
    if(empty){//if empty
        array[front] = add_item;
        rear=front;
        empty = false;
        
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
        front = 0;
        rear = size+1;//increment rear so can add to rear easier later
        size = size*2;//increase size
        delete[] array;
        array = new_array;
        array[rear] = add_item;
    }
    else{//if array not empty, not full
        if(rear == size-1){//if rear is at the end of array
            array[0] = add_item;
            rear=0;
        }
        else{
            array[rear] = add_item;
            rear+=1;
        }
    }
    return;
}

template <typename T>
int Queue<T>::top(){
    if(empty){return -99999;}

    int highest_prio = 0;
    int index = 0;
    for(int i=front; i<size-1; i++){
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
    //TODO
    //returning the array index of the highest priority item
    return index;
}

template <typename T>
T Queue<T>::dequeue(){
    //TODO
    int pop_index = top();
    T returnvalue = array[pop_index].value; 
    if(pop_index == rear){//if pop index is last index of queue
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
            front +=1;
        }
        else if(rear > front){//if rear behind front (normal case) 
            for(int i=0; i<pop_index; i++){
                array[i+1] = array[i];
                front+=1;
            }
        }
    }
    return returnvalue;
}

template <typename T>
bool Queue<T>::isFull(){
    //TODO
    if((front-1==rear) || (front==0 && rear==size-1)) return true;
    return false;
}