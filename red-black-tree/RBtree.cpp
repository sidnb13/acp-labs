#include "RBtree.h"

RBtree::RBtree() {
	NIL = new Node;
	NIL->color = BLACK;
	NIL->left = nullptr;
	NIL->right = nullptr;
	root = NIL;
}

RBtree::~RBtree() {
    delete root;
}

Node* RBtree::searchTreeHelper(Node* node, int key) {
	if (node == NIL || key == node->key) {
		return node;
	}

	if (key < node->key) {
		return searchTreeHelper(node->left, key);
	} 
	return searchTreeHelper(node->right, key);
}

// fix-up remove operation
void RBtree::fixRemove(Node* x) {
	Node* s;
	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			s = x->parent->right;
			if (s->color == RED) {
				s->color = BLACK;
				x->parent->color = RED;
				leftRotate(x->parent);
				s = x->parent->right;
			}

			if (s->left->color == BLACK && s->right->color == BLACK) {
				s->color = RED;
				x = x->parent;
			} else {
				if (s->right->color == BLACK) {
					s->left->color = BLACK;
					s->color = RED;
					rightRotate(s);
					s = x->parent->right;
				} 

				s->color = x->parent->color;
				x->parent->color = BLACK;
				s->right->color = BLACK;
				leftRotate(x->parent);
				x = root;
			}
		} else {
			s = x->parent->left;
			if (s->color == RED) {
				s->color = BLACK;
				x->parent->color = RED;
				rightRotate(x->parent);
				s = x->parent->left;
			}

			if (s->right->color == BLACK) {
				s->color = RED;
				x = x->parent;
			} else {
				if (s->left->color == BLACK) {
					s->right->color = BLACK;
					s->color = RED;
					leftRotate(s);
					s = x->parent->left;
				} 

				s->color = x->parent->color;
				x->parent->color = BLACK;
				s->left->color = BLACK;
				rightRotate(x->parent);
				x = root;
			}
		} 
	}
	x->color = BLACK;
}


void RBtree::transplant(Node* u, Node* v){
	if (u->parent == nullptr) {
		root = v;
	} else if (u == u->parent->left){
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void RBtree::remove(int key) {
	removeNodeRecursive(this->root, key);
}


void RBtree::removeNodeRecursive(Node* node, int key) {
	Node* z = NIL;
	Node *x, *y;
	while (node != NIL){
		if (node->key == key) {
			z = node;
		}

		if (node->key <= key) {
			node = node->right;
		} else {
			node = node->left;
		}
	}

	if (z == NIL) {
		cout<<"tree is empty"<<endl;
		return;
	} 

	y = z;
	int y_original_color = y->color;
	if (z->left == NIL) {
		x = z->right;
		transplant(z, z->right);
	} else if (z->right == NIL) {
		x = z->left;
		transplant(z, z->left);
	} else {
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		} else {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (y_original_color == BLACK){
		fixRemove(x);
	}
}

void RBtree::leftRotate(Node* x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left)
      y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
      root = y;
    else if (x->parent->left == x) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBtree::rightRotate(Node* x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x->parent->right == x) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RBtree::fixInsert(Node* k){
    Node *y;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            y = k->parent->parent->left;
            if (y->color == RED) {
                y->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }

                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        } else {
            y = k->parent->parent->right;
            if (y->color == RED) {
                y->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else { //copied from the prior else statement but left <-> right
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }

                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBtree::insert(int key) {
    Node* z = new Node;
    z->parent = nullptr;
    z->key = key;
    z->left = nullptr;
    z->right = nullptr;
    z->color = RED;

    Node *y = nullptr;
    Node *x = root;

    while (x != nullptr) {
      y = x;
      if (z->key < x->key)
          x = x->left;
      else x = x->right;
    }
    z->parent = y;

    if (y == nullptr)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else y->right = z;

    fixInsert(z); //cause of bug
}

void RBtree::printTraverse(Node* root, string indent, bool last) {
  
	if (root != NIL) {
	   cout<<indent;
	   if (last) {
		  cout<<"R----";
		  indent += "     ";
	   } else {
		  cout<<"L----";
		  indent += "|    ";
	   }
		
	   string sColor = root->color?"RED":"BLACK";
	   cout<<root->key<<"("<<sColor<<")"<<endl;
	   printTraverse(root->left, indent, false);
	   printTraverse(root->right, indent, true);
	}
  
}


void RBtree::preorder() {
	RBtree::preOrderTraverse(this->root);
}

void RBtree::preOrderTraverse(Node* node) {
	if (node != NIL) {
		cout<<node->key<<" ";
		preOrderTraverse(node->left);
		preOrderTraverse(node->right);
	} 
}



void RBtree::inorder() {
	inOrderTraverse(this->root);
}
void RBtree::inOrderTraverse(Node* node) {
	if (node != NIL) {
		inOrderTraverse(node->left);
		cout<<node->key<<" ";
		inOrderTraverse(node->right);
	} 
}

void RBtree::postorder() {
	postOrderTraverse(this->root);
}

void RBtree::postOrderTraverse(Node* node) {
	if (node != NIL) {
		postOrderTraverse(node->left);
		postOrderTraverse(node->right);
		cout<<node->key<<" ";
	} 
}


Node* RBtree::searchTree(int k) {
	return searchTreeHelper(this->root, k);
}


Node* RBtree::minimum(Node* node) {
	while (node->left != NIL) {
		node = node->left;
	}
	return node;
}


Node* RBtree::maximum(Node* node) {
	while (node->right != NIL) {
		node = node->right;
	}
	return node;
}


Node* RBtree::successor(Node* x) {


	if (x->right != NIL) {
		return minimum(x->right);
	}


	Node* y = x->parent;
	while (y != NIL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

Node* RBtree::predecessor(Node* x) {


	if (x->left != NIL) {
		return maximum(x->left);
	}

	Node* y = x->parent;
	while (y != NIL && x == y->left) {
		x = y;
		y = y->parent;
	}

	return y;
}


Node* RBtree::getRoot(){
	return this->root;
}



void RBtree::prettyPrint() {
	if (root) {
		printTraverse(this->root, "", true);
	}
}


