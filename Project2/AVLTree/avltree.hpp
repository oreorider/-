#include <iostream>
#include <algorithm>
#include <optional>
#include <unistd.h>

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
AVLNode<T,U>* AVLTree<T,U>::rotate_left(AVLNode<T,U>*& node){ //parent of impalanced node as parameter
    //TODO    
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
        return AVLNode<T,U>(key, value);
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
        return rotate_right(node);
    }

    //if no need for updates, just return the ndoe
    return node;
}

template<typename T, typename U>
U AVLTree<T,U>::search(AVLNode<T,U>*& node, const T& key) {
    //TODO
    //return NULL if there are no such key, return value if there is
    if(node == NULL) return NULL;//value not found
    
    if(node->key == key) return node->value;//value found

    if(key < node->key) return search(node->left, key);//go to left tree

    if(key > node->key) return search(node->right, key);//go to right tree
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::remove(AVLNode<T,U>*& node, const T& key) {
    //TODO
    if(search(node, key) == NULL) return node;//if key not in tree, just return root

    if(node->left == nullptr && node->right == nullptr){//if leaf just delete
        delete node;
    }

    T max_key;
    U max_value;
    bool max_found = 0;
    while(max_found == 0){
        
    }
}

template<typename T, typename U>
void AVLTree<T,U>::removeall(AVLNode<T,U>*& node) {
    //TODO
    //for destructor
        
    }
    

