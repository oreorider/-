#include <algorithm>
#include <iterator>
#include <vector>
#include <random>
#include <time.h>
#include <string>

#include "avltree.hpp"
#include <iostream>

using namespace std;

int main () {

    clock_t start_insert_remove, finish_insert_remove;
    clock_t start_search, finish_search;

    AVLTree<int,string> tree;
    
    cout<<"<< AVL tree >>"<<endl<<endl;

    start_insert_remove = clock();
    /*
    tree.insert(16, "yf");
    tree.insert(4, "rg");
    tree.insert(6, "fj");
    tree.insert(7, "zm");
    tree.insert(9, "aq");
    tree.insert(13, "gw");
    tree.insert(13, "ry");
    tree.insert(12, "ve");
    tree.insert(2, "xo");
    tree.insert(11, "kz");
    tree.insert(4, "nv");
    tree.insert(6, "yx");
    tree.insert(12, "te");
    tree.insert(17, "uj");
    tree.insert(18, "go");
    tree.insert(9, "wb");
    tree.insert(10, "an");
    tree.insert(19, "it");
    tree.insert(3, "wh");
    tree.insert(17, "to");

    cout<<"print inorder"<<endl;
    cout<<"_________________________"<<endl;
    tree.inorder(tree.root);
    cout<<"print preorder"<<endl;
    cout<<"_________________________"<<endl;
    tree.preorder(tree.root);
    printBT(tree.root);
    */

    tree.insert(34, "ax");
    tree.insert(6, "jr");
    tree.insert(7, "zl");
    tree.insert(12, "fk");
    tree.insert(1, "fr");
    tree.insert(13, "ku");
    tree.insert(20, "ye");
    tree.insert(39, "qh");
    tree.insert(43, "hb");
    tree.insert(17, "kp");
    tree.insert(29, "ld");
    tree.insert(2, "sg");
    tree.insert(18, "ku");
    tree.insert(31, "pq");
    tree.insert(44, "pr");
    tree.insert(8, "mu");
    tree.insert(5, "br");
    tree.insert(30, "ij");
    tree.insert(26, "ud");
    tree.insert(16, "kp");
    tree.remove(12);
    tree.remove(1);
    tree.remove(18);
    tree.remove(20);
    tree.remove(44);
    tree.remove(2);
    tree.remove(26);
    tree.remove(7);
    tree.remove(8);
    tree.remove(16);
    cout<<"print inorder"<<endl;
    cout<<"_________________________"<<endl;
    tree.inorder(tree.root);
    cout<<"print preorder"<<endl;
    cout<<"_________________________"<<endl;
    tree.preorder(tree.root);
    printBT(tree.root);

    /*
    tree.insert(16545, "yeonnamdong");
    tree.insert(54312, "sinsadong");
    
    tree.insert(11243, "sillimdong");
    tree.insert(66443, "bongcheondong");
    tree.insert(55443, "jungangdong");
    tree.insert(32340, "banpodong");
    tree.insert(33450, "dobongdong");
    tree.insert(25234, "samseongdong");    
    tree.remove(54312);
    tree.insert(59155, "gurodong");
    tree.insert(51211, "banghwadong");
    
    tree.remove(11243);*/
    /*
    for(int i=0; i<10; i++){
        char insert = 'A' + i;
        tree.insert(i, std::string(1, insert));
        //if(i%5 == 0) tree.inorder(tree.root);
    }*/
    //printBT(tree.root);
    
    //tree.inorder(tree.root);
    //cout<<"remove 5"<<endl;
    //tree.remove(5);
    //printBT(tree.root);
    
    //tree.inorder(tree.root);
    //cout<<"remove"<<endl;
    //tree.remove(4);
    //printBT(tree.root)
    //tree.inorder(tree.root);

    //cout<<"remove 3"<<endl;
    //tree.remove(3);
    //printBT(tree.root);
    //tree.inorder(tree.root);
    
    
    finish_insert_remove = clock();

    cout<<"print inorder"<<endl;
    cout<<"_________________________"<<endl;
    tree.inorder(tree.root);
    cout<<endl;
    cout<<"print preorder"<<endl;
    cout<<"_________________________"<<endl;
    tree.preorder(tree.root);
    cout<<"tree diagram\n"<<endl;
    printBT(tree.root);
    cout<<endl;

    start_search = clock();

    cout<<"print search"<<endl;
    cout<<"_________________________"<<endl;
    /*
    cout<<"search 54155: "<<tree.search(54155)<<endl;
    //print 0 if none
    cout<<"search 54312:"<<tree.search(54312)<<endl;
    cout<<"search 12345:"<<tree.search(12345)<<endl;
    cout<<"search 11243:"<<tree.search(11243)<<endl; //removed
    */

    finish_search = clock();
   
    //time for operation ( this case may have 0ms )
    cout<<endl<<"print  time for opration"<<endl;
    cout<<"_________________________"<<endl;
    cout<<"time for insert and remove: "<<(double)(finish_insert_remove-start_insert_remove)<<"ms"<<endl;   
    cout<<"time for search: "<<(double)(finish_search-start_search)<<"ms"<<endl;  
    return 0;
}
