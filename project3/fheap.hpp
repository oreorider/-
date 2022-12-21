#ifndef __FHEAP_H_
#define __FHEAP_H_

#include <iostream>
#include <initializer_list>
#include <optional>
#include <vector>
#include <cmath>
#include <memory>
#include <queue>

template <typename T>
class PriorityQueue {
    public:
        virtual void insert(const T& item) = 0;
        virtual std::optional<T> extract_min() = 0;
        virtual bool is_empty() const = 0;
};

template <typename T>
class FibonacciNode {
    public:
        // Constructors
        FibonacciNode();
        FibonacciNode(const T& item)
            :key(item), degree(0), marked(false), child(nullptr), right(nullptr) {}

        // Destructor
		// You can implement your custom destructor.
        ~FibonacciNode(){
            right.reset();
            child.reset();
            //std::cout<<"node deleted"<<std::endl;
        }

        T key;
        size_t degree;
		bool marked;

		std::shared_ptr<FibonacciNode<T>> right;
		std::shared_ptr<FibonacciNode<T>> child;
        // NOTE: To prevent circular reference, left/parent pointer should be set to weak_ptr.
        std::weak_ptr<FibonacciNode<T>> left;
        std::weak_ptr<FibonacciNode<T>> parent;
};

template <typename T>
class FibonacciHeap : public PriorityQueue<T> {
    public:
        // Constructors
        FibonacciHeap()
            : min_node(nullptr), size_(0) {}
        FibonacciHeap(const T& item)
            : min_node(nullptr), size_(0) { insert(item); }

        // Disable copy constructor.
        FibonacciHeap(const FibonacciHeap<T> &);

        // Destructor
        ~FibonacciHeap();

        void removeall(std::shared_ptr<FibonacciNode<T>>& node);
        void insert(const T& item) override;
		void insert(std::shared_ptr<FibonacciNode<T>>& node);

        // Return raw pointer of the min_node.
        FibonacciNode<T>* get_min_node() { return min_node.get(); }

        std::optional<T> get_min() const;

        std::optional<T> extract_min() override;

		void decrease_key(std::shared_ptr<FibonacciNode<T>>& x, T new_key);

		void remove(std::shared_ptr<FibonacciNode<T>>& node);

        bool is_empty() const override { return !size_; }

        size_t size() const { return size_; }
		
    private:

        std::shared_ptr<FibonacciNode<T>> min_node;
        size_t size_;

        void consolidate();
        void merge(std::shared_ptr<FibonacciNode<T>>& x, std::shared_ptr<FibonacciNode<T>>& y);
		void cut(std::shared_ptr<FibonacciNode<T>>& x);
		void recursive_cut(std::shared_ptr<FibonacciNode<T>>& x);

};

template <typename T>
FibonacciHeap<T>::~FibonacciHeap() {
	// TODO
	// NOTE: Be aware of memory leak or memory error.
    //std::cout<<"heap destructor"<<std::endl;
    while(size_ > 0){
        auto x = extract_min();
        //std::cout<<"node has value "<<x.value()<<std::endl;
    }
}

template <typename T>
std::optional<T> FibonacciHeap<T>::get_min() const {
	if(!min_node) 
        //cout<<"hello"<<endl;
		return std::nullopt;
	else
		return min_node->key;
}

template <typename T>
void FibonacciHeap<T>::insert(const T& item) {
	std::shared_ptr<FibonacciNode<T>> node = std::make_shared<FibonacciNode<T>>(item);
	insert(node);
    //node.reset();
}

template <typename T>
void FibonacciHeap<T>::insert(std::shared_ptr<FibonacciNode<T>>& node) {
	// TODO
    if(size_ == 0){
        size_+=1;
        min_node = node;
        min_node->left = node;
        min_node->right = node;
        return;
    }
    if(size_ == 1){
        min_node->right = node;
        node->right = min_node;
        min_node->left = node;
        node->left = min_node;
        if(node->key < min_node->key){
            min_node = node;
        }
        size_+=1;
        return;
    }
    else{
        std::shared_ptr<FibonacciNode<T>> p = min_node->left.lock();
        p->right = node;
        node->right = min_node;
        min_node->left = node;
        node->left = p;
        if(node->key < min_node->key){
            min_node = node;
        }
        size_+=1;
    }

}

template <typename T>
std::optional<T> FibonacciHeap<T>::extract_min() {
	// TODO
    T returnKey = min_node->key;

    remove(min_node);
    if(size_ == 0){
        return returnKey;
    }
    consolidate();


    return returnKey;
}

template <typename T>
void FibonacciHeap<T>::decrease_key(std::shared_ptr<FibonacciNode<T>>& x, T new_key) {
	// TODO
    x->key = new_key;
    if(x->parent.lock() == nullptr){
        return;
    }
    if(x->key < x->parent.lock()->key){//heap property violated
        cut(x);
    }
    auto iter = min_node;
    for(int i=0; i<size_; i++){
        if(iter->key < min_node->key){
            min_node = iter;
        }
        iter = iter->right;
    }
}

template <typename T>
void FibonacciHeap<T>::remove(std::shared_ptr<FibonacciNode<T>>& x) {
	// TODO
    if(size_ == 0){
        //error
        return;
    }

    std::shared_ptr<FibonacciNode<T>> leftChild;
    std::shared_ptr<FibonacciNode<T>> rightChild;
    std::shared_ptr<FibonacciNode<T>> iter;

    if(size_ == 1){//only 1 root
        if(x->degree == 0){//no children
            x->right = nullptr;
            x.reset();
            size_-=1;
            return;
        }
        else{//has children
            
            iter = x->child;
            for(int i=0; i<x->degree; i++){
                iter->parent = x->parent;
                iter = iter->right;
            }

            size_ = size_ - 1 + x->degree;
            x->right = nullptr;
            x.reset();
            x = iter;
            
            return;
        }
    }
    else{//more than one root
        std::shared_ptr<FibonacciNode<T>> leftNode = x->left.lock();
        std::shared_ptr<FibonacciNode<T>> rightNode = x->right;

        if(x->degree == 0){//if no children
            leftNode->right = rightNode;
            rightNode->left = leftNode;
            x.reset();
            x = leftNode;
            size_-=1;
            return; 
        }
        else{//if children
            leftChild = x->child;
            rightChild = x->child->left.lock();

            leftNode->right = leftChild;
            leftChild->left = leftNode;

            rightNode->left = rightChild;
            rightChild->right = rightNode;

            for(int i=0; i<x->degree; i++){
                leftChild->parent = x->parent;
                leftChild = leftChild->right;
            }
            size_ = size_ - 1 + x->degree;
            x.reset();
            x=leftChild;
            return;
        }
    }

    /*
	if(min_node->degree != 0){//at least one child
        std::shared_ptr<FibonacciNode<T>> child = min_node->child;
        for(int i=0; i<min_node->degree; i++){
            leftNode->right = child;
            child->left = leftNode;

        }
    }*/
}

template <typename T>
void FibonacciHeap<T>::consolidate() {
	float phi = (1 + sqrt(5)) / 2.0;
	int len = int(log(size_) / log(phi)) + 10;
    std::vector<std::shared_ptr<FibonacciNode<T>>> A(len, nullptr);
    int startingSize = size_;
	// TODO
    std::shared_ptr<FibonacciNode<T>> iter = min_node;
    std::shared_ptr<FibonacciNode<T>> next_root;



    for(int i=0; i<len; i++){
        std::shared_ptr<FibonacciNode<T>> occupied = A[iter->degree];
        if(occupied == nullptr || occupied == iter){//if array for 해당 degree is empty
           A[iter->degree] = iter;//set
           iter = iter->right;
        }
        else{//if array at index occupied, do merge
            A[iter->degree] = nullptr;
            next_root = iter->right;
            std::shared_ptr<FibonacciNode<T>> leftNode;
            if(iter->key < occupied->key){//iter on top, occupied goes under
            
                //occupied should get skipped over
                leftNode = occupied->left.lock();
                leftNode->right = occupied->right;
                occupied->right->left = leftNode;

                merge(iter, occupied);
                if(A[iter->degree] == nullptr){//if degree index available, add and index iter
                    A[iter->degree] = iter;
                    iter = next_root;
                }
                else{//if degree index unavail, merge again to combine
                    continue;
                }

            }

            else{//iter goes under, occupied on top

                //iter should be skipped over
                leftNode = iter->left.lock();
                leftNode->right = iter->right;
                iter->right->left = leftNode;

                merge(occupied, iter);
                if(A[occupied->degree] == nullptr){
                    A[occupied->degree] = occupied;
                    iter = next_root;
                }
                else{
                    iter = occupied;
                }
            }
        }
    }
    
	for(auto i : A){
        if(i != nullptr){
            min_node = i;//set min node to any random node
            break;
        }
    }
    for(auto i : A){
        if(i != nullptr && i->key < min_node->key){
            min_node = i;
        }
    }
    return;

}

template <typename T> 
void FibonacciHeap<T>::merge(std::shared_ptr<FibonacciNode<T>>& x, std::shared_ptr<FibonacciNode<T>>& y) {//x is smaller, needs to go on top
    //x is parent, y is child to be merged
	// TODO
    if(x->degree == 0){//no children
        x->child = y;
        y->parent = x;
        y->right = y;
        y->left = y;
        x->degree+=1;
    }
    else{//children already exist
        std::shared_ptr<FibonacciNode<T>> leftChild = x->child;
        std::shared_ptr<FibonacciNode<T>> rightChild = leftChild->left.lock();
        rightChild->right = y;
        y->left = rightChild;

        leftChild->left = y;
        y->right = leftChild;

        y->parent = x;
        x->degree+=1;
    }
    size_-=1;
}

template <typename T>
void FibonacciHeap<T>::cut(std::shared_ptr<FibonacciNode<T>>& x) {
	// TODO
    std::shared_ptr<FibonacciNode<T>> parentptr = x->parent.lock();
    T value = x->key;
    if(parentptr == nullptr){
        return;// do nothing if already top node
    }

    //cut out the node and add to the top
    if(parentptr->degree == 1){//x no siblings
        parentptr->child = nullptr;
        parentptr->degree -= 1;
        x->marked = false;
        x->parent.reset();
        insert(x);
    }
    else if(parentptr->degree != 1){//x has siblings
        std::shared_ptr<FibonacciNode<T>> leftNode = x->left.lock();
        std::shared_ptr<FibonacciNode<T>> rightNode = x->right;
        leftNode->right = rightNode;
        rightNode->left = leftNode;

        parentptr->child = leftNode;
        parentptr->degree -=1;
        x->parent.reset();
        x->marked = false;
        insert(x);
    }
    
    //check if recursive call neccessary
    if(parentptr->marked == false){
        parentptr->marked = true;
    }
    else{
        cut(parentptr);
    }
    
    
}

template <typename T>
void FibonacciHeap<T>::removeall(std::shared_ptr<FibonacciNode<T>> & node){
    /*
    if(node->child == nullptr && node->right == nullptr){
        delete node;
        node.reset();
        node = nullptr;
        return;
    }
    if(node->child != nullptr){
        removeall(node->child);
    }
    if(node->child == nullptr && node->right != nullptr){
        for(int i=0; i<node->degree; i++){
            if(node->child != nullptr){
                removeall(node->child);
            }
            else{
                
            }
        }
    }*/
}

template <typename T>
void FibonacciHeap<T>::recursive_cut(std::shared_ptr<FibonacciNode<T>>& x) {
	// TODO

}



#endif // __FHEAP_H_
