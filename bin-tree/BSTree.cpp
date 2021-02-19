/*
 * Binary Search Tree class
 * Do not alter the display() function, this will break the Repl.it
 * tests
 */

#include <iostream>
#include <cstdlib>
#include "BSTree.h"

using namespace std;

/*
 * Find Element in the Tree
 * find a node by item_key and provide an updated parent node
 *   pointer and location node pointer
 */

void BST::find(int item_key, node **prnt, node **loc) const {
    node *ptr, *ptrsave;
    if (root == nullptr) {
        *loc = nullptr;
        *prnt = nullptr;
        return;
    }
    if (item_key == root->key_value) {
        *loc = root;
        *prnt = nullptr;
        return;
    }
    if (item_key < root->key_value)
        ptr = root->p_left;
    else
        ptr = root->p_right;
    ptrsave = root;
    while (ptr != nullptr) {
        if (item_key == ptr->key_value) {
            *loc = ptr;
            *prnt = ptrsave;
            return;
        }
        ptrsave = ptr;
        if (item_key < ptr->key_value)
            ptr = ptr->p_left;
        else
            ptr = ptr->p_right;
        }
    *loc = nullptr;
    *prnt = ptrsave;
}

/*
 * Helper to find if node exists
 */

bool BST::searchKey(int key, node* loc) {
    if (loc == nullptr)
        return false;
    if (loc->key_value == key) {
        return true;
    } else if (loc->key_value < key)
        searchKey(key, loc->p_right);
    return searchKey(key, loc->p_left);
}

/*
* Helper to make binary decision
*/

void BST::chooseBin(node** parent, node** child) {
    if ((*parent) == nullptr) {
        (*parent) = new node;
        (*parent)->key_value = (*child)->key_value;
        root = *parent;
    } else {
        if ((*child)->key_value > (*parent)->key_value)
            (*parent)->p_right = (*child);
        else
            (*parent)->p_left = (*child);
    }
}

/*
 * Inserting Element into the Tree
 */
void BST::insert(node *tree, node *pNode) {
    if (tree == nullptr) { //we  are at root
        // Just create a single node for root to point to,
        //    with all the data in it.
        chooseBin(&tree, &pNode);
    } else if (searchKey(pNode->key_value, root)) { // there is already a node with our key value
        //Just return
        return;
    } else if (pNode->key_value < tree->key_value) { //the new node is less than the current node
        if (tree->p_left != nullptr) { //see if something is already a child on the left
            // if so, the recurse insert at this subtree
            insert(tree->p_left, pNode);
      	} else {
            // otherwise the new node goes here as a leaf (ie no children)
            chooseBin(&tree, &pNode);
        }
    } else { // it must be to the right
        if (tree->p_right != nullptr) { //is there already a child on right?
             // if so, the recurse insert at this subtree
             insert(tree->p_right, pNode);
        } else {
            // otherwise the new node goes here as a leaf (ie no children)
            chooseBin(&tree, &pNode);
        }
    }
}

/*
 * Helper to find minimum
 */
node* BST::min(node* curr) {
    if (curr == nullptr || curr->p_left == nullptr)
        return curr;
    return min(curr->p_left);
}

/*
 * Helper to find max
 */
node *BST::max(node *curr) {
    if (curr == nullptr || curr->p_right == nullptr)
        return curr;
    return max(curr->p_right);
}

/*
 * Delete Element from the tree
 */
void BST::remove(int item) {
    node* prnt = root;
    node* loc = nullptr;
    find(item, &prnt, &loc);

    if (loc == nullptr)
        return;

   /* cout << item << endl;
    cout << (loc->p_left == nullptr) << " " << (loc->p_right == nullptr) << endl;*/

    if (loc->p_left == nullptr && loc->p_right == nullptr) {
        //cout << "CASE 0" << endl << endl;
        case_0(prnt, loc);
    } else if (loc->p_left == nullptr ^ loc->p_right == nullptr) {
        //cout << "CASE 1" << endl << endl;
        case_1(prnt, loc);
    } else if (loc->p_left != nullptr && loc->p_right != nullptr) {
        //cout << "CASE 2" << endl << endl;
        if (loc->p_right->p_left == nullptr) {
            loc->key_value = loc->p_right->key_value;
            loc->p_right = loc->p_right->p_right;
            return;
        }

        node* suc = loc->p_right;
        node* sucP = loc;

        while (suc->p_left != nullptr) {
            sucP = suc;
            suc = suc->p_left;
        }

        loc->key_value = suc->key_value;
        sucP->p_left = suc->p_right;
    }
}

/*
 * Case 0
 * the node is simply removed no other updates necessary.
 */
void BST::case_0(node *prnt, node *loc ) const {
    //cout << endl << "case 0" << endl;
    if (prnt == root) //we are at the root, so update the root
        prnt->key_value = loc->key_value;
    if (prnt->p_left != nullptr)
        prnt->p_left = nullptr;
    else
        prnt->p_right = nullptr;
}

/*
 * Case 1
 * We have only one child so promote the child and replace the target
 * node
 */
void BST::case_1(node *prnt, node *loc) const {
    //cout << endl << "case 1" << endl;
    node *child;
    if (loc->p_left != nullptr) { //the child is on the left?
        //point left
        child = loc->p_left;
    } else {  // must be the right side has child
        // point right
        child = loc->p_right;
    }
    if (loc == root) { //we are at the root handle specially
        // update the root
        loc->key_value = child->key_value;
        loc->p_left = child->p_left;
        loc->p_right = child->p_right;
    } else {
        //cout << endl << "not root" << endl;
        if (prnt->p_left == loc) { //the node is left child of parent, promote the left
            prnt->p_left = child;
        } else { // the node is right of parent, promote right
            prnt->p_right = child;
        }
    }
}

/*
 * Case case_2
 * We have to find and promote a successor or predecessor
 */
void BST::case_2(node *prnt, node *loc) {

    //cout << endl << "REMOVE: " << (loc->p_left != nullptr && loc->p_right != nullptr);

    node* succ = loc->p_right;
    node* ptr = loc;

    if (succ->p_left == nullptr) {
        ptr->key_value = succ->key_value;
        ptr->p_right = succ->p_right;
        return;
    }

    while (succ->p_left != nullptr) {
        ptr = succ;
        succ = succ->p_left;
    }

    loc->key_value = succ->key_value;

    ptr->p_left = succ->p_right;

    /*//cout << endl << "case 2" << endl;
    // temporary pointers for node we are manipulating
    node* temp;
    // Find successor: Step to the right child
    node* find = successor(loc);
    // Find the min of the subtree on parent's right

    //cout << endl << "find " << find->key_value << endl << "right_min " << right_min->key_value << endl;

    node* p = prnt;
    node* l = loc;
    this->find(find->key_value, &p, &l);

    if (find->p_left == nullptr && find->p_right == nullptr) { //found node has no children
        // Replace the target node with the successor node

        //cout << "p " << p->key_value << endl << "l " << l->key_value << endl;

        swap(loc->key_value, find->key_value);

        if (p->p_right != nullptr)
            p->p_right = nullptr;
        else p->p_left = nullptr;

    } else {
        // Temporarily remove the successor node by replacing it with
        // its right child, we will replace the node we are removing
        // with the successor we just removed.
        temp = find;
        case_1(p, l);
    }

    if (loc == root) { //we are at root
        //then update root


    } else {
        // Insert the successor node where the target node we
        //   are removing is located
    }
    // then update the successor child pointers to reflect the old
    //     target's child pointers.*/
}

/*
 * Display Tree Structure
 */
void BST::display(node *ptr, int level) {
    int i;
    if (ptr != nullptr) {
        display(ptr->p_right, level+1);
        cout<<endl;
        if (ptr == root)
            cout<<"Root->:  ";
        else {
            /*for (i = 0;i < level;i++)
                cout<<"       ";*/
	}
        cout<<ptr->key_value;
        display(ptr->p_left, level+1);
    }
}
