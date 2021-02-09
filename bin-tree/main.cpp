/*
 * C++ Program To Implement BST
 */
#include <iostream>
#include <cstdlib>
#include "BSTree.h"
#include "printPretty.h"

using namespace std;

/*
 * Main Contains Menu
 */
int main() {
    int choice, num;
    BST bst;
    node *temp;

    //Some random test data, use as you like //COMMENT OUT BEFORE TEST CASE

    int arr[] = {2,4,3,5,1};
    int rem[] = {4};
    int arrlen = 5;
    int remlen = 1;


    cout << "Array size: " << arrlen << endl;


    for (int i=0; i<arrlen; i++)
    {
        temp = new node;
        temp->key_value = arr[i];
        bst.insert(bst.root, temp);
    }

    cout<<"Display BST:"<<endl;
    bst.display(bst.root,1);

    //cout << endl << "root key:" << bst.root->key_value << endl;

    for (int i=0; i<remlen; i++) {
        bst.remove(rem[i]);
    }

    cout<<"\n\nDisplay BST:"<<endl;
    bst.display(bst.root,1);

}
 
