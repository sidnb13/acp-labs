
#ifndef AVLTREE_H
#define AVLTREE_H

#include<stdlib.h>  
#include<stdio.h>  

 
//#define HEIGHT 1  
#define HEIGHT(t) ((t == NULL) ? 0 : t->height)

struct node
{  
	int key_value = 0;
	struct node* left{};
	struct node* right{};
	int height{};
};


class AVLTree
{
public:
	AVLTree();
	~AVLTree();

	node*	root;
	
	static struct node* get_node(int val);
	static int get_height(struct node* root);
	static int get_balance(struct node* root);
	static int max(int a, int b);
	static struct node* left_rotate(struct node* t);
	static struct node* right_rotate(struct node* t);
	struct node* insert(struct node* root, int val);
	struct node* deletion(struct node* root, int val);
	static struct node* inorder_succ_right_tree(struct node* root);
	void preorder(struct node* root);
	void inorder(struct node* root);
	void inorder_level(struct node* tree, int level);
	int max_level(struct node* tree, int level, int max);
	int min_level(struct node* tree, int level, int min);

	int sumorder(struct node* tree);
	void clear(struct node* tree);
	void display(node*, int level, int dir);
	 
};

#endif // AVLTREE_H
