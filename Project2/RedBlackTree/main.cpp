#include <algorithm>
#include <iterator>
#include <vector>
#include <random>
#include <time.h>
#include <string>

#include "RBtree.hpp"
#include <iostream>

using namespace std;

int main () {

    clock_t start_insert_remove, finish_insert_remove;
    clock_t start_search, finish_search;

    RBTree<int,string> tree;
    
    cout<<"<< RBtree >>"<<endl<<endl;

    start_insert_remove = clock();
    /*
    tree.insert(16545, "yeonnamdng");
    tree.insert(54312, "sinsadong");
    
    tree.insert(11243, "sillimdong");
    tree.insert(66443, "bongcheondong");
    tree.insert(55443, "jungangdong");
    tree.insert(32340, "banpodong");
    tree.insert(33450, "dobongdong");
    tree.insert(25234, "samseongdong");    
    tree.remove(54312);
    tree.insert(54155, "gurodong");
    tree.insert(51211, "banghwadong");
    
    tree.remove(11243);
    */
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
    //printBT(tree.root);
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

    //add in ascending
    /*
    tree.insert(1, "apple");
    tree.insert(2, "pear");
    tree.insert(3, "bananna");
    tree.remove(-999);
    //printBT(tree.root);

    //cout<<"\n\n insert mango \n\n"<<endl;
    tree.insert(4, "mango");
    //printBT(tree.root);

    //cout<<"\n\n insert pineapple \n\n"<<endl;
    tree.insert(5, "pineapple");
    //printBT(tree.root);

    //cout<<"\n\n insert durian \n\n"<<endl;
    tree.insert(6, "durian");
    //printBT(tree.root);
    
    //cout<<"\n\ninsert grape"<<endl;
    tree.insert(7, "grape");
    //printBT(tree.root);

    //cout<<"\n\ninsert grapefruit"<<endl;
    tree.insert(8, "grapefruit");
    //printBT(tree.root);

    tree.insert(9, "mangosteen");
    tree.insert(10, "dragonfruit");
    cout<<"\n\nadd a bunch of stuff"<<endl;
    printBT(tree.root);

    cout<<"\n\nremove 10"<<endl;
    tree.remove(10);
    printBT(tree.root);

    //cout<<"\n\nremove 8"<<endl;
    tree.remove(8);
    //printBT(tree.root);

    //cout<<"\n\nremove 3"<<endl;
    tree.remove(3);
    //printBT(tree.root);

    //cout<<"\nnremove 7"<<endl;
    tree.remove(7);
    //printBT(tree.root);

    cout<<"\n\nadding a bunch more items"<<endl;
    tree.insert(10, "dragonfruit");
    tree.insert(12, "kiwi");
    tree.insert(13, "watermelon");
    printBT(tree.root);
    
    //cout<<"\n\n remove 2"<<endl;
    tree.remove(2);
    //printBT(tree.root);

    tree.insert(7, "grape");
    printBT(tree.root);
    tree.remove(10);
    printBT(tree.root);

    tree.remove(5);//case 5
    printBT(tree.root);
    

    tree.remove(7);//case 3
    printBT(tree.root);

    tree.remove(1);
    tree.remove(13);
    tree.remove(4);//case 10
    printBT(tree.root);
    cout<<"end"<<endl;
    */
    finish_insert_remove = clock();
    /*
    for(int i=0; i<15; i++){
        tree.insert(i, "o");
    }
    printBT(tree.root);
    
    tree.remove(4);//case 6, 7;
    printBT(tree.root);
    tree.remove(8);//case 2
    printBT(tree.root);
    tree.remove(10);//case 3
    printBT(tree.root);
    tree.insert(10, "o");
    printBT(tree.root);
    tree.remove(14);//case 1
    printBT(tree.root);
    for(int i=-10; i<0; i++){
        tree.insert(i, "x");
    }
    printBT(tree.root);
    tree.remove(-9);
    printBT(tree.root);
    */

    
    cout<<"print inorder"<<endl;
    cout<<"_________________________"<<endl;
    tree.inorder(tree.root);
    cout<<endl;
    cout<<"print preorder"<<endl;
    cout<<"_________________________"<<endl;
    tree.preorder(tree.root);
    cout<<endl;

    start_search = clock();
    
    cout<<"print search"<<endl;
    cout<<"_________________________"<<endl;
    cout<<"search 54155: "<<tree.search(54155)<<endl;
    //print 0 if none
    cout<<"search 12345:"<<tree.search(12345)<<endl;
    cout<<"search 11243:"<<tree.search(11243)<<endl; //removed

    finish_search = clock();
   
    //time for operation ( this case may have 0ms )
    cout<<endl<<"print time for opration"<<endl;
    cout<<"_________________________"<<endl;
    cout<<"time for insert and remove: "<<(double)(finish_insert_remove-start_insert_remove)<<"ms"<<endl;   
    cout<<"time for search: "<<(double)(finish_search-start_search)<<"ms"<<endl;  
    
    return 0;
}
