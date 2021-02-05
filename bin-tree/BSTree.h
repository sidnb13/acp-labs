/*
 * C++ Program To Implement BST
 */
#ifndef BSTREE_H
#define BSTREE_H


/*
 * Node Declaration
 */
struct node
{
    int key_value = 0;
    struct node *p_left;
    struct node *p_right;
};
 
/*
 * Class Declaration
 */
class BST {

public:
		node* root;
        void find(int, node **, node **) const;
        void insert(node *, node *);
        void remove(int) const;
        void case_0(node *,node *);
        void case_1(node *,node *);
        void case_2(node *,node *);
        void display(node *, int);
        BST() {root = nullptr;}

        void chooseBin(node **r, node **l);
        bool searchKey(int key, node *loc);
};


#endif	//BSTREE_H
