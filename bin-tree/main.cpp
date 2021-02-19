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

    int arr[] = {72,114,56,31,128,39,34,80,121,116,57,1,13,89,62,98,3,8,53,
            42,123,93,113,
            4,
            54,
            105,
            103,
            117,
            48,
            51,
            94,
            40,
            77,
            70,
            27,
            120,
            90,
            95,
            30,
            47,
            55,
            52,
            125,
            24,
            112,
            96,
            67,
            118,
            26,
            43,
            73,
            6,
            50,
            11,
            101,
            17,
            18,
            35,
            74,
            28,
            68,
            107,
            63,
            45,
            75,
            65,
            88,
            79,
            29,
            86,
            127,
            25,
            104,
            32,
            20,
            22,
            69,
            81,
            46,
            82,
            5,
            100,
            78,
            9,
            16,
            71,
            66,
            109,
            76,
            110,
            119,
            58,
            19,
            99,
            122,
            64,
            59,
            92,
            124,
            36,
            61,
            126,
            49,
            10,
            33,
            41,
            38,
            91,
            21,
            44,
            7,
            87,
            84,
            111,
            85,
            15,
            102,
            23,
            97,
            60,
            2,
            108,
            12,
            83,
            106,
            14,
            37};
    int rem[] = {93,40,127,70};
    //int rem[] = {93,127};
    int arrlen = 128;
    int remlen = 4;


    cout << "Array size: " << arrlen << endl;


    for (int i=0; i<arrlen; i++) {
        temp = new node;
        temp->key_value = arr[i];
        bst.insert(bst.root, temp);
    }

    /*cout<<"Display BST:";
    bst.display(bst.root,1);*/

    //cout << endl << "root key:" << bst.root->key_value << endl;

    for (int i=0; i<remlen; i++) {
        bst.remove(rem[i]);
    }

    cout<<"\n\nDisplay BST:";
    bst.display(bst.root,1);

}
