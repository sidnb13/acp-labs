#include <iostream>

#define MIN_DEGREE 3

struct node{
  int n;
  bool leaf;
  int k[2*MIN_DEGREE - 1];
  node* c[2*MIN_DEGREE];
  
};

node* ALLOCATE_NODE() {
    node* aNode = new node();
    aNode->leaf = false;
    aNode->n = 0;
    for (auto & i : aNode->c) {
      i = nullptr;
    }
    return aNode;
}

void B_TREE_SPLIT_CHILD (node* x, int i, node* y) {
    node *z = ALLOCATE_NODE();
    int t = x->n / 2; //median index
    int j;

    z->leaf = y->leaf;
    z->n = t - 1;

    for (j = 1; j < t; j++)
        z->k[j] = y->k[j + t];

    if (!y->leaf) {
        for (j = 1; j <= t; j++)
            z->c[j] = y->c[j + t];
    }
    y->n = t - 1;

    for (j = x->n + 1; j >= i + 1; j--)
        x->c[j + 1] = x->c[j];
    x->c[i + 1] = z;

    for (j = x->n; j >= i; j--)
        x->k[j+1] = x->k[j];
    x->k[i] = y->k[t];
    x->n = x->n + 1;
}

void displayNode(node* aNode) {
  std::cout << "leaf: " << aNode->leaf << std::endl;
  std::cout << "keys" ;
  for (int i=0; i < aNode->n; i++) {
    std::cout << ", " << aNode->k[i];
  }
  std::cout << std::endl;
  if (aNode->leaf) {
    std::cout << "Pointers : ";
    for (int i=0; i < aNode->n+1; i++) {
      if (aNode->c[i] == nullptr) {
        std::cout << "[" << i << "] =  NULL, ";
      }
      else {
        std::cout << "[" << i << "] =  CHILD, ";
        // std::cout << "[" << i << "] = " << aNode->c[i] << ", ";
      }
    }
    std::cout << std::endl;
  }
}

int main() {
  node* node1 = ALLOCATE_NODE();
  node* node2 = ALLOCATE_NODE();
  int index = 0;
  int inCount = 0;
  std::cout << "Hello B-TREE assignment!\n";
  std::cout << "How many keys for node 1?\n";
  std::cin >> inCount;
  node1->leaf = true;
  node1->n = inCount;
  for (int i=0; i < inCount; i++) {
    std::cout << "Enter key " << i << " ";
    std::cin >> node1->k[i];
  }

  std::cout << "How many keys for node 2?\n";
  std::cin >> inCount;
  node2->leaf = false;
  node2->n = inCount;
  for (int i=0; i < inCount; i++) {
    std::cout << "Enter key " << i << " ";
    std::cin >> node2->k[i];
  }
  for (auto & i : node2->c) {
    i = nullptr;
  }
  index = 0;
  for (index=0; index < node1->n; index++) {
    if (node1->k[index] > node2->k[0]) {
      node1->c[index] = node2;
      break;
    }
  }
  // if index == count then node2 keys are greater than all in node1
  if (index == node1->n)
    node1->c[index] = node2;

  B_TREE_SPLIT_CHILD (node1,index,node2);

  std::cout << "Contents of node 1 : " << std::endl;
  displayNode(node1);
  
  for (int i=0; i < node1->n+1; i++) {
      if (node1->c[i]){
        std::cout << "Contents of child " << i << " : " << std::endl;
        displayNode(node1->c[i]);
      }
    }

}

