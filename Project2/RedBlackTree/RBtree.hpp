#include <iostream>
#include <algorithm>
#include <optional>
#include <unistd.h>

#define RED 1
#define BLACK 0

template <typename T, typename U>
class RBNode{
    
    public :
        T key;
        U value;
	    RBNode<T,U> * parent;
        RBNode<T,U> * left;
        RBNode<T,U> * right;
        int color; // 1 -> red, 0 -> black

        RBNode<T,U>(const T& k, const U& v)
        {
            key = k;
            value = v;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }        
        
};

template <typename T, typename U>
class RBTree {
    public : 
        RBNode<T,U> * root = nullptr;
        ~RBTree() {
            removeall(root);
        }

        void insert(const T& key, const U& value);
        U search(const T& key);
        bool remove(const T& key);

        //for checking
        void preorder(RBNode<T,U>*& node){
            if(!node) return;

            std::cout<<node->key<<": "<<node->value<<std::endl;
            preorder(node->left);
            preorder(node->right);
        }
        void inorder(RBNode<T,U>*& node){
            if(!node) return;

            inorder(node->left);
            std::cout<<node->key<<": "<<node->value<<std::endl;
            inorder(node->right);
        }

    private :
        RBNode<T,U>* rotate_left(RBNode<T,U>*& node);
        RBNode<T,U>* rotate_right(RBNode<T,U>*& node);

        RBNode<T,U>* insert(RBNode<T,U>*& node, const T& key, const U& value);
        U search(RBNode<T,U>*& node, const T& key);
        RBNode<T,U>* remove(RBNode<T,U>*& node, const T& key);
        void removeall(RBNode<T,U>*& node);

};




template<typename T, typename U>
void RBTree<T,U>::insert(const T& key, const U& value) {
    root = insert(root, key, value);
}


template<typename T, typename U>
U RBTree<T,U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool RBTree<T,U>::remove(const T& key) {
    if(!search(root,key).length()) return false;
    root = remove(root, key);
    return true;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_left(RBNode<T,U>*& node){
    //TODO    
    cout<<"rotate left"<<endl;
    RBNode<T,U> *y = node->right;
    RBNode<T,U> *T2 = y->left;

    y->left = node;
    node->parent = y;

    node->right = T2;
    T2->parent = node;

    //node->height = max(getHeight(node->left), getHeight(node->right))+1;
    //y->height = max(getHeight(y->left), getHeight(y->right))+1;

    return y;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_right(RBNode<T,U>*& node){
    //TODO
    cout<<"rotate right"<<endl;
    RBNode<T,U> *x = node->left;
    RBNode<T,U> *T2 = x->right;

    x->right = node;
    node->parent = x;

    node->left = T2;
    T2->parent = node;

    //node->height = max(getHeight(node->left), getHeight(node->right))+1;
    //x->height = max(getHeight(x->left), getHeight(x->right))+1;

    return x;
}


template<typename T, typename U>
int RB_tree_violated(RBNode<T,U>*& node){//fixes two reds in a row
    if(node->left!=nullptr && node->right!=nullptr){//two children exist
        if(node->left->color == RED && node->right->color==RED){//both children red
            //just need to swap colors to fix, and recurse up
            if(node->left->left!=nullptr && node->left->left->color == RED){//LL
                //1
                return 1;
            }
            else if(node->left->right!=nullptr && node->left->right->color==RED){//LR
                //2
                return 2;
            }
            else if(node->right->left!=nullptr && node->right->left->color == RED){//RL
                //3
                return 3;
            }
            else if(node->right->right!=nullptr && node->right->right->color == RED){//RR
                //4
                return 4;
            }
        }
    }
    if(node->left!=nullptr){//left child exists
        if(node->left->color == RED){//left child is red
            if(node->left->left!=nullptr && node->left->left->color == RED){//LL - left child's left child is red
                //5
                return 5;
            }
            if(node->left->right!=nullptr && node->left->right->color == RED){//LR - left child's right child is red
                //6
                return 6;
            }
        }
    }
    else if(node->right!=nullptr){//right child exists
        if(node->right->color == RED){//right child is red
            if(node->right->left!=nullptr && node->right->left->color == RED){//RL - right child's left child is red
                //7
                return 7;
            }
            if(node->right->right!=nullptr && node->right->right->color == RED){//RR - right child's right child is red
                //8
                return 8;
            }
        }
    }
    return 0;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::insert(RBNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    if(node == NULL){
        RBNode<T,U> *newNode = new RBNode<T,U>(key, value);
        if(node->parent != nullptr){
            newNode->color = RED;//if not root, make new node red
        }
        else{
            newNode->color = BLACK;//if root node being added, make black
        }
        //fix_tree_after_insert(node);
        //fixorientation(node);
        return newNode;
    }
    if(key < node->key){
        node->left = insert(node->left, key, value);
        node->left->parent = node;
    }
    else if(key > node->key){
        node->right = insert(node->right, key, value);
        node->right->parent = node;
    }
    else{
        node->value = value;//update value
        return node;
    }
    RBNode<T,U> *uncleNode;
    RBNode<T,U> *parentNode = node;
    RBnode<T,U> *grandNode = node->parent;

    if(node->parent == nullptr){//if root node
        node->color = BLACK;
        return node;
    }
    /*
    if(node->parent->color == BLACK){
        return node;
    }*/

    int code = RB_tree_violated(node);

    if(code == 0){
        return node;
    }
    if(code == 5){//LL - one child
        node->color = RED;
        node->left->color = BLACK;
        return rotate_right(node);
    }
    if(code == 6){//LR - one child
        node->color = RED;
        node->left->right->color = BLACK;
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if(code == 7){//RL - one child
        node->color = RED;
        node->right->left->color = BLACK;
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    if(code == 8){//RR - one child
        node->color = RED;
        node->right->color = BLACK;
        return rotate_left(node);
    }
    if(code == 1 || code == 2 || code == 3 || code == 4){//both children red, just change colors
        node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
        return node;
    }
    /*
    if(node->parent->color == RED){
        uncleNode = grandNode->left == parentNode ? : grandNode->right : grandNode->left;
        if(uncleNode != nullptr && uncleNode->color == RED){//if uncle is red
            parentNode->color = BLACK;//change uncle and parent to black
            uncleNode->color = BLACK;
            grandNode->color = RED;
        }
        if(uncleNode->color == BLACK || uncleNode == NULL){//if uncle is black
            //LL case
            if(grandNode->left == parent && parent->left == node){
                
            }
            //LR case
            else if(grandNode->left == parent && parent->right == node){

            }
            //RR case
            else if(grandNode->right == parent && parent->right == node){

            }
            //RL
            else if(grandNode->right == parent && parent->left == node){

            }
        }
    }
    */
}


template<typename T, typename U>
U RBTree<T,U>::search(RBNode<T,U>*& node, const T& key) {
    //TODO
    //return NULL if there are no such key, return value if there is
    if(node == NULL) return "";//value not found
    
    if(node->key == key) {//value found
        cout<<"key : "<<key<<" found"<<endl;
        return node->value;
    }
    if(key < node->key) return search(node->left, key);//go to left tree

    if(key > node->key) return search(node->right, key);//go to right tree
}

template<typename T, typename U>
void printBT(const std::string& prefix, const RBNode<T,U>* node, bool isLeft)
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
void printBT(const RBNode<T,U>* node){
    printBT("", node, false);  
}

template<typename T, typename U>
RBNode<T,U> *maxNode(RBNode<T,U>*&node){
    RBNode<T,U> *current = node;
    while(current->right != nullptr){
        current = current->right;
    }
    return current;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::remove(RBNode<T,U>*& node, const T& key) {
    //normal BST delete
    if(node == nullptr) return node;

    if(key < node->key) {
        node->left = remove(node->left, key);//go left
        node->left->parent = node;
    }
    if(key > node->key) {
        node->right = remove(node->right, key);//go right
        node->right->parent = node;
    }
    if(key == node->key){//node found
        bool rightside, leftside = 0;
        RBNode<T,U> *parentNode = node->parent;
        RBNode<T,U> *siblingNode;  
        if(parentNode->left == node){
            siblingNode = parentNode->right;
            leftside = 1;
        }
        else if(parentNode->right == node){
            siblingNode = parentNode->left;
            rightside = 0;
        }

        RBNode<T,U> *temp;
        if(node->left == nullptr && node->right == nullptr && node->color == RED){//if red leaf node
            temp = node;
            node = nullptr;
        }
        if(node->left == nullptr && node->right == nullptr && node->color == BLACK){//if black leaf node
            //case 1, leaf is on right side
            if(siblingNode->color == BLACK && (siblingNode->left !=nullptr || siblingNode->right !=nullptr)){
                if(rightside){
                    return rotate_right(node->parent);
                }
                else if(leftside){
                    return rotate_left(node->parent);
                }
            }
        }
        else if(node->left == nullptr || node->right == nullptr){//if one child, must be black node with red leaf
            cout<<"removing node with 1 child"<<endl;
            cout<<"key : "<<node->key<<"\tvalue : "<<node->value<<"\n"<<endl;
            temp = node->left !=nullptr ? node->left : node->right;//if left is not null, set temp as left and vice versa
            

            node->key = temp->key;//copy values
            node->value = temp->value;

            node->left = temp->left;//move children pointers
            node->right = temp->right;

            delete temp;
        }
        else{//if two children
            cout<<"removing node with 2 children"<<endl;
            cout<<"key : "<<node->key<<"\tvalue : "<<node->value<<"\n"<<endl;
            RBNode<T,U> *max_left_node = maxNode(node->left);//largest of left subtree

            //update with key and value fom max left node
            node->key = max_left_node->key;
            node->value = max_left_node->value;
            
            //if max left node is red leaf
            if(max_left_node->color == RED && (max_left_node->left == nullptr && max_left_node->right == nullptr)){
                node->left = remove(node->left, max_left_node->key);//remove maxleftnode
            }

            //if max left node is black with right red child
            if(max_left_node->color == BLACK && max_left_node->left != nullptr && max_left_node->right !=nullptr){
                
            }

            //if max left node is black leaf

            //delete maxleftnode by overwriting it with its left child
            //max_left_node = max_left_node->left;
            //auto __ = remove(node->left, max_left_node->key);//recursiely call remove function
            //node->left = remove(node->left, max_left_node->key);
            
        }

    }
    if(node == nullptr){//if removed the only node in tree
        return nullptr;
    }
    
    return node;

}

template<typename T, typename U>
void RBTree<T,U>::removeall(RBNode<T,U>*& node) {
    //TODO
    //for destructor
        
}
    

