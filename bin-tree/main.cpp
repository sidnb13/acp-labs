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

    /*int arr[256]; //UNCOMMENT BELOW FOR TEST CASE
    int rem[256];*/

    //Some random test data, use as you like //COMMENT OUT BEFORE TEST CASE
    int arr[] = {2,3,1};
    int rem[] = {};
    int arrlen = 3;
    int remlen = 0;

    //Get list of keys to insert UNCOMMENT BELOW FOR TEST CASE
    /*int i = 0;
    cout << "Tree insert\n";
    do
    {
      cin >> arr[i++];
    }	while (arr[i-1] >= 0 );
    int arrlen = i-1;

    // Get list of keys to remove
    i = 0;
    cout << "Tree remove\n";
    do
    {
      cin >> rem[i];
    }	while (rem[i++] >= 0 );
    int remlen = i-1;*/


    cout << "Array size: " << arrlen << endl;


    for (int i=0; i<arrlen; i++)
    {
        temp = new node;
        temp->key_value = arr[i];
        bst.insert(bst.root, temp);
    }

    for (int i=0; i<remlen; i++) {
        bst.remove(rem[i]);
    }

    cout<<"Display BST:"<<endl;
    bst.display(bst.root,1);

    cout<<endl;

    //cout << bst.searchKey(4, bst.root);

}
 
