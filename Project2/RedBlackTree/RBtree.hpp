#include <iostream>
#include <algorithm>
#include <optional>
#include <unistd.h>

using namespace std;

#define RED 1
#define BLACK 0
#define DOUBLEBLACK 2
#define REMOVE 3

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
        ~RBNode<T,U>(){
            //delete parent;
            //delete right;
            //delete left;
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
        RBNode<T,U>* resolve_doubleblack(RBNode<T,U>*& node);
        RBNode<T,U>* resolve_doublered(RBNode<T,U>*& node);
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
    y->parent = nullptr;
    if(T2 != nullptr) T2->parent = node;

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
    x->parent = nullptr;
    if(T2 != nullptr) T2->parent = node;

    //node->height = max(getHeight(node->left), getHeight(node->right))+1;
    //x->height = max(getHeight(x->left), getHeight(x->right))+1;

    return x;
}

template<typename T, typename U>
int RB_fix_doubleblack(RBNode<T,U>*&node){//fix doubleblack for after removal
    bool sibling_left_child, sibilng_right_child;
    if(node->left !=nullptr && node->right !=nullptr){//if left and right children exist
        //consider case where before doubleblack actually made nullptr

        //doubleblack/remove on right, black sibling on left
        if((node->right->color == DOUBLEBLACK || node->right->color == REMOVE) && node->left->color == BLACK){
            if(node->left->left !=nullptr) sibling_left_child = true;
            if(node->left->right !=nullptr) sibilng_right_child = true;

            //if sibling has red children only
            //if sibling has black children only

            //case 1
            if(sibling_left_child && sibilng_right_child && node->left->left->color == RED && node->left->right->color == RED){
                return 1;//LL
            }
            if(sibling_left_child && !sibilng_right_child && node->left->left->color == RED){
                return 1; //LL
            }
            if(sibilng_right_child && !sibling_left_child && node->left->right->color == RED){
                return 2; //LR
            }
            else{//black sibling has black children or no children, case 2
                if(node->color == BLACK){//if parent is black, must do double black chaining
                    return 4;
                }
                if(node->color == RED){
                    return 5;
                }
            }
        }
        
        //doubleblack/remove on right, red sibling on left
        if((node->right->color == DOUBLEBLACK || node->right->color == REMOVE) && node->left->color == RED){
            return 8;
        }
        
        //doubleblack/remove on left, black sibling on right
        if((node->left->color == DOUBLEBLACK || node->left->color == REMOVE) && node->right->color == BLACK){//doubleblack on left
            if(node->right->left != nullptr) sibling_left_child = true;
            if(node->right->right != nullptr) sibilng_right_child = true;

            //case 1
            if(sibling_left_child && sibilng_right_child && node->right->left->color == RED && node->right->right->color == RED){
                return 3;//RR
            }
            if(sibling_left_child && !sibilng_right_child && node->right->left->color == RED){
                return 10; //RL
            }
            if(sibilng_right_child && !sibling_left_child && node->right->right->color == RED){
                return 3; //RR
            }
            else{//sibling has black children or no children, case 2
                if(node->color == BLACK){
                    return 6;
                }
                if(node->color == RED){
                    return 7;
                }
            }
        }
    
        //doubleblack/remove on left, red sibling on right
        if((node->left->color == DOUBLEBLACK || node->left->color == REMOVE) && node->right->color == RED){
            return 9;
        }

    }
    return 0;
   
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
    if(node->right!=nullptr){//right child exists
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
RBNode<T,U>* RBTree<T,U>::resolve_doublered(RBNode<T,U>*& node){
    
    int code = RB_tree_violated(node);

    if(code == -1){
        node->color = BLACK;
        //return node;
    }

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
        if(node->parent != nullptr) node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
        return node;
    }
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::insert(RBNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    if(node == NULL){
        RBNode<T,U> *newNode = new RBNode<T,U>(key, value);
        newNode->color = RED;
        /*
        if(newNode->parent != nullptr){
            newNode->color = RED;//if not root, make new node red
        }
        else{
            newNode->color = BLACK;//if root node being added, make black
        }
        */
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
    //RBNode<T,U> *uncleNode;
    //RBNode<T,U> *parentNode = node;
    //RBNode<T,U> *grandNode = node->parent;

    if(node->parent == nullptr){//if root node
        node->color = BLACK;
        //return node;
    }
    /*
    if(node->parent->color == BLACK){
        return node;
    }*/
    node = resolve_doublered(node);
    return node;
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

        if(node->color == BLACK) std::cout << node->key <<" BLACK " << std::endl;
        else if(node->color == RED) std::cout << node->key <<" RED " << std::endl;
        else if(node->color == DOUBLEBLACK) std::cout << node->key <<" DOUBLEBLACK " << std::endl;

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
RBNode<T,U>* RBTree<T,U>::resolve_doubleblack(RBNode<T,U>*& node){
    int fixcode = RB_fix_doubleblack(node);

    if(fixcode == 0){
        return node;
    }

    if(fixcode == 1 || fixcode == 2){
        //if REMOVE, make node->right nullptr
        if(node->right->color == REMOVE){
            delete node->right;
            node->right = nullptr;
        }
        //if actual doubleblack, make node->right black
        else if(node->right->color == DOUBLEBLACK){
            node->right->color = BLACK;
        }
        int OGcolor = node->color;
        if(fixcode == 1) {
            node = rotate_right(node);
        }
        else if(fixcode == 2){
            node->left = rotate_left(node->left);
            node = rotate_right(node);
        }
        node->left->color = BLACK;
        node->right->color = BLACK;
        node->color = OGcolor;
        return node;
    }

    if(fixcode == 3 || fixcode == 10){
        if(node->left->color == REMOVE){
            delete node->left;
            node->left = nullptr;
        }
        else if(node->left->color == DOUBLEBLACK){
            node->left->color = BLACK;
        }
        int OGcolor = node->color;
        if(fixcode == 3){
            node = rotate_left(node);
        }
        else if(fixcode == 10){
            node->right = rotate_right(node->right);
            node = rotate_left(node);
        }
        node->left->color = BLACK;
        node->right->color = BLACK;
        node->color = OGcolor;
        return node;
    }
    

    //sibling black, parent black, doubleblack on right
    if(fixcode == 4){
        if(node->right->color == REMOVE){
            delete node->right;
            node->right = nullptr;
        }
        else if(node->right->color == DOUBLEBLACK){
            node->right->color = BLACK;
        }
        //set parent as doubleblack, sibling as red, and recurse up
        node->color = (node->parent != nullptr) ? DOUBLEBLACK : BLACK;
        node->left->color = RED;
        return node;
    }

    //sibling black, parent red, doubleblack on right
    if(fixcode == 5){
        if(node->right->color == REMOVE){
            delete node->right;
            node->right = nullptr;
        }
        else if(node->right->color == DOUBLEBLACK){
            node->right->color = BLACK;
        }
        //set parent as black, sibling as red
        node->color = BLACK;
        node->left->color = RED;
        return node;
    }

    //sibling black, parent red, doubleblack on left
    if(fixcode == 7){
        if(node->left->color == REMOVE){
            delete node->left;
            node->left = nullptr;
        }
        else if(node->left->color == DOUBLEBLACK){
            node->left->color = BLACK;
        }
        //if parent red, set parent as black
        //if parent black, set parent as doubleblack
        //set sibling as red
        if(node->color == RED) node->color = BLACK;
        else if(node->color == BLACK && node->parent != nullptr) node->color = DOUBLEBLACK;//if not root, and node is black, set as DOUBLEBLACK
        //node->color = (node->parent != nullptr) ? DOUBLEBLACK : BLACK;
        node->right->color = RED;
    }

    //sibling black, parent black, doubleblack on left
    if(fixcode == 6){
        if(node->left->color == REMOVE){
            delete node->left;
            node->left = nullptr;
        }
        else if(node->left->color == DOUBLEBLACK){
            node->left->color = BLACK;
        }
        //set parent as doubleblack, sibling as red, and recurse up
        node->color = (node->parent != nullptr) ? DOUBLEBLACK : BLACK;
        node->right->color = RED;
        return node;
    }

    //sibling red, parent must be black, doubleblack on left
    if(fixcode == 8){
        node = rotate_right(node);
        node->color = BLACK;
        node->right->color = RED;
        node->right = resolve_doubleblack(node->right);
    }

    if(fixcode == 9){
        node = rotate_left(node);
        node->color = BLACK;
        node->left->color = RED;
        node->left = resolve_doubleblack(node->left);
    }
    return node;
    
}


template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::remove(RBNode<T,U>*& node, const T& key) {
    //normal BST delete
    if(node == nullptr) return node;

    if(key < node->key) {
        node->left = remove(node->left, key);//go left
        if(node->left != nullptr) node->left->parent = node;
    }
    if(key > node->key) {
        node->right = remove(node->right, key);//go right
        if(node->right != nullptr) node->right->parent = node;
    }
    if(key == node->key){//node found
        
        /*
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
        */

        RBNode<T,U> *temp;
        if(node->left == nullptr && node->right == nullptr){//if leaf node
            if(node->color == RED){//red leaf node, just delete
                temp = node;
                node = nullptr;
                delete temp;
            }
            else if(node->color == BLACK){//black leaf node
                node->color = REMOVE;//set color to remove, and fix later
            }
        }
        
        //remove black node with red child
        //promote red child to black
        else if(node->left == nullptr || node->right == nullptr){//if one child, must be black node with red leaf
            cout<<"removing node with 1 child"<<endl;
            cout<<"key : "<<node->key<<"\tvalue : "<<node->value<<"\n"<<endl;
            temp = node->left !=nullptr ? node->left : node->right;//if left is not null, set temp as left and vice versa
            

            node->key = temp->key;//copy values
            node->value = temp->value;

            node->left = temp->left;//move children pointers
            node->right = temp->right;
            if(node->left != nullptr) node->left = nullptr;
            else if(node->right != nullptr) node->right = nullptr;
            delete temp;
            
        }
        else{//if two children
            cout<<"removing node with 2 children"<<endl;
            cout<<"key : "<<node->key<<"\tvalue : "<<node->value<<"\n"<<endl;
            RBNode<T,U> *max_left_node = maxNode(node->left);//largest of left subtree

            //update with key and value fom max left node
            node->key = max_left_node->key;
            node->value = max_left_node->value;
            
            //recurse down until in order predecessor
            node->left = remove(node->left, max_left_node->key);            
        }


    }
    if(node == nullptr){//if removed the only node in tree
        return nullptr;
    }
    
    //int fixcode = RB_fix_doubleblack(node);
    node = resolve_doubleblack(node);
    node = resolve_doublered(node);
    
    return node;

}

template<typename T, typename U>
void RBTree<T,U>::removeall(RBNode<T,U>*& node) {
    //TODO
    //for destructor
    
    if(node->left == nullptr && node->right == nullptr){//leaf node
        delete node;
        delete node->left;
        delete node->right;
        delete node->parent;
        return;
    } 
    if(node->left == nullptr && node->right !=nullptr){//only right child
        return removeall(node->right);
    }
    if(node->left !=nullptr && node->right == nullptr){//only left child
        return removeall(node->left);
    }
    if(node->left !=nullptr && node->right !=nullptr){//two children
        removeall(node->left);
        
        removeall(node->right);
        delete node;
        return;
    }
    //delete node;
    //delete node->left;
    //delete node->right;
    //delete node->parent;
}
    

