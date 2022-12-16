
#include <iostream>
#include <algorithm>
#include <optional>
#include <unistd.h>
#include <string.h>

using namespace std;

template <typename T, typename U>
class AVLNode{
    
    public :
        T key;
        U value;
        AVLNode<T,U> * left;
        AVLNode<T,U> * right;
        int height;

        AVLNode<T,U>(const T& k, const U& v)
        {
            key = k;
            value = v;
            left = nullptr;
            right = nullptr;
            height = 1;
        }        
        ~AVLNode<T,U>(){

        }
        
};

template <typename T, typename U>
class AVLTree {
    public : 
        AVLNode<T,U> * root = nullptr;
        ~AVLTree() {
            removeall(root);
        }

        void insert(const T& key, const U& value);
        U search(const T& key);
        bool remove(const T& key);

        //for checking
        void preorder(AVLNode<T,U>*& node){
            if(!node) return;

            std::cout<<node->key<<": "<<node->value<<std::endl;
            preorder(node->left);
            preorder(node->right);
        }
        void inorder(AVLNode<T,U>*& node){
            if(!node) return;

            inorder(node->left);
            std::cout<<node->key<<": "<<node->value<<std::endl;
            inorder(node->right);
        }

    private :
        int getHeight(AVLNode<T,U>*& node);
        int getBalance(AVLNode<T,U>*& node);
        AVLNode<T,U>* rotate_left(AVLNode<T,U>*& node);
        AVLNode<T,U>* rotate_right(AVLNode<T,U>*& node);

        AVLNode<T,U>* insert(AVLNode<T,U>*& node, const T& key, const U& value);
        U search(AVLNode<T,U>*& node, const T& key);
        AVLNode<T,U>* remove(AVLNode<T,U>*& node, const T& key);
        void removeall(AVLNode<T,U>*& node);

};

template <typename T, typename U>
int AVLTree<T,U>::getHeight(AVLNode<T,U>*& node){
    if(!node) return 0;
    return node->height;
}

template <typename T, typename U>
int AVLTree<T,U>::getBalance(AVLNode<T,U>*& node){
    if(!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

template<typename T, typename U>
void AVLTree<T,U>::insert(const T& key, const U& value) {
    root = insert(root, key, value);
}

template<typename T, typename U>
U AVLTree<T,U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool AVLTree<T,U>::remove(const T& key) {
    if(!search(root,key).length()) return false;
    root = remove(root, key);
    return true;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_left(AVLNode<T,U>*& node){ //parent of imbalanced node as parameter
    //TODO    
    //cout<<"rotate left"<<endl;
    AVLNode<T,U> *y = node->right;
    AVLNode<T,U> *T2 = y->left;

    y->left = node;
    node->right = T2;

    node->height = max(getHeight(node->left), getHeight(node->right))+1;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;

    return y;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_right(AVLNode<T,U>*& node){
    //TODO
    //cout<<"rotate right"<<endl;
    AVLNode<T,U> *x = node->left;
    AVLNode<T,U> *T2 = x->right;

    x->right = node;
    node->left = T2;

    node->height = max(getHeight(node->left), getHeight(node->right))+1;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;

    return x;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::insert(AVLNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    if (node == NULL){
        AVLNode<T,U> *newNode = new AVLNode<T,U>(key, value);
        return newNode;
    }
    if(key < node->key){
        node->left = insert(node->left, key, value);
    }
    else if(key > node->key){
        node->right = insert(node->right, key, value);
    }
    else{
        node->value = value;//update value
        return node;
    }

    node->height = max(getHeight(node->left), getHeight(node->right))+1;

    int balance = getBalance(node);
    //left left
    if(balance > 1 && key < node->left->key){
        return rotate_right(node);
    }

    //right right
    if(balance < -1 && key > node->right->key){
        return rotate_left(node);
    }

    //left right
    if(balance > 1 && key > node->left->key){
        node->left = rotate_left(node->left);//rotate left once
        return rotate_right(node);//then rotate right
    }

    //right left
    if(balance < -1 && key < node->right->key){
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    //if no need for updates, just return the ndoe
    return node;
}

template<typename T, typename U>
U AVLTree<T,U>::search(AVLNode<T,U>*& node, const T& key) {
    //TODO
    //return NULL if there are no such key, return value if there is
    if(node == NULL) return "";//value not found
    
    if(node->key == key) {//value found
        //cout<<"key : "<<key<<" found"<<endl;
        return node->value;
    }
    if(key < node->key) return search(node->left, key);//go to left tree

    if(key > node->key) return search(node->right, key);//go to right tree
}

template<typename T, typename U>
AVLNode<T,U> *maxNode(AVLNode<T,U>*&node){
    AVLNode<T,U> *current = node;
    while(current->right != nullptr){
        current = current->right;
    }
    return current;
}

template<typename T, typename U>
void printBT(const std::string& prefix, const AVLNode<T,U>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->key << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

template<typename T, typename U>
void printBT(const AVLNode<T,U>* node)
{
    printBT("", node, false);    
}

// pass the root node of your binary tree

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::remove(AVLNode<T,U>*& node, const T& key) {
    if(node == nullptr) return node;

    if(key < node->key) node->left = remove(node->left, key);//go left
    if(key > node->key) node->right = remove(node->right, key);//go right

    if(key == node->key){
        AVLNode<T,U> *temp;
        if(node->left == nullptr && node->right == nullptr){//if leaf node
            temp = node;
            node = nullptr;
            delete temp;
            
        }
        else if(node->left == nullptr || node->right == nullptr){//if one child
            //cout<<"removing node with 1 child"<<endl;
            //cout<<"key : "<<node->key<<"\tvalue : "<<node->value<<"\n"<<endl;
            temp = node->left !=nullptr ? node->left : node->right;//if left is not null, set temp as left and vice versa

            node->key = temp->key;//copy values
            node->value = temp->value;

            node->left = temp->left;//move children pointers
            node->right = temp->right;

            //if(node->left != nullptr) node->left = nullptr;
            //else if(node->right != nullptr) node->right = nullptr;
            
            delete temp;
        }
        else{//if two children
            //cout<<"removing node with 2 children"<<endl;
            //cout<<"key : "<<node->key<<"\tvalue : "<<node->value<<"\n"<<endl;
            AVLNode<T,U> *max_left_node = maxNode(node->left);//largest of left subtree

            node->key = max_left_node->key;
            node->value = max_left_node->value;
            
            //delete maxleftnode by overwriting it with its left child
            //max_left_node = max_left_node->left;
            //auto __ = remove(node->left, max_left_node->key);//recursiely call remove function
            node->left = remove(node->left, max_left_node->key);
            
        }

    }
    if(node == nullptr){//if removed the only node in tree
        return nullptr;
    }

    //balance the tree after remove
    node->height = max(getHeight(node->left), getHeight(node->right))+1;

    int balance = getBalance(node);
    //left left
    if(balance > 1 && getBalance(node->left) >= 0){
        //cout<<"rotate left left"<<endl;
        return rotate_right(node);
    }

    //right right
    if(balance < -1 && getBalance(node->right) <= 0){
        //cout<<"rotate right right"<<endl;
        return rotate_left(node);
    }

    //left right
    if(balance > 1 && getBalance(node->left) < 0){
        //cout<<"rotate left right"<<endl;
        node->left = rotate_left(node->left);//rotate left once
        return rotate_right(node);//then rotate right
    }

    //right left
    if(balance < -1 && getBalance(node->right) > 0){
        //cout<<"rotate right left"<<endl;
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    //if no need for updates, just return the ndoe
    return node;
}

template<typename T, typename U>
void AVLTree<T,U>::removeall(AVLNode<T,U>*& node) {
    //TODO
    //for destructor
    if(node->left == nullptr && node->right == nullptr){//leaf node
        delete node;
        node = nullptr;
        return;
    } 
    if(node->left == nullptr && node->right !=nullptr){//only right child
        removeall(node->right);
        delete node;
        node = nullptr;
        return;
    }
    if(node->left !=nullptr && node->right == nullptr){//only left child
        removeall(node->left);
        delete node;
        node = nullptr;
        return;
    }
    if(node->left !=nullptr && node->right !=nullptr){//two children
        removeall(node->left);
        
        removeall(node->right);
        delete node;
        node = nullptr;
        return;
    }
        
}
    

