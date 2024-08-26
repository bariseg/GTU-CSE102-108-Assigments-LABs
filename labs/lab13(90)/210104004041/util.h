#ifndef _UTIL_H_
#define _UTIL_H_

typedef struct Node
{
    int value;

    struct Node * left;
    struct Node * right; 
}Node;

typedef struct BST
{
    struct Node * root;
}BST;





struct BST* generateBST(const char* filename);
void addNode(struct BST* bst, int value);
void removeNode(struct BST* bst, int value);
struct Node* searchNode(struct BST* bst, int value);
int countNodes(struct BST* bst);
int countLeafNodes(struct BST* bst);


void printTree(struct BST* bst);




#endif /* _UTIL_H_ */
