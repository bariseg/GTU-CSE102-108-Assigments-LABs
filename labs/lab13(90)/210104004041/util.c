#include <stdio.h>
#include <stdlib.h>
#include "util.h"



struct BST* generateBST(const char* filename){

    BST * tree = (BST*)malloc(sizeof(BST));
    tree->root=NULL;
    FILE *fpt= fopen(filename,"r");
    int tempvalue;

    while (fscanf(fpt,"%d ",&tempvalue)!=EOF) addNode(tree,tempvalue);

    return tree;

    fclose(fpt);
}

void addNode(struct BST* bst, int value){

    Node * newnode= (Node*)malloc(sizeof(Node));
    newnode->value=value;
    newnode->left=NULL;
    newnode->right=NULL;
    Node *result;

    if (bst->root!=NULL){

        Node * curr= bst->root;
        Node * currparent;
        //goes till the null
        while (curr!=NULL)
        {
            currparent=curr;
            if (curr->value < value)
            {
                curr= curr->right;
            }else{
                curr=curr->left;
            }
        }
        //inserts the newnode to null
        if (currparent->value < value)
        {
            currparent->right= newnode;
        }else{
            currparent->left= newnode;
        }
    }else{
        bst->root=newnode;
    }

}

void printTree(struct BST* bst){

    if (bst->root!=NULL)
    {
        BST nextleft;
        nextleft.root= bst->root->left;
        BST nextright;
        nextright.root= bst->root->right;

        printTree(&nextleft);
        printf("%d ",bst->root->value);
        printTree(&nextright);
    }

}

void removeNode(struct BST* bst, int value){

}

struct Node* searchNode(struct BST* bst, int value){

    Node* result=NULL;

    Node* curr= bst->root;
    while (curr!=NULL)
    {
        if (curr->value== value)
        {
            result= curr;
            break;
        }else if(curr->value< value){
            curr= curr->right;
        }else if(curr->value> value){
            curr= curr->left;
        }
    }
    return result;
}

int countNodes(struct BST* bst){

    int result=0;

    if (bst->root!=NULL)
    {
        BST nextright;
        nextright.root= bst->root->right;
        BST nextleft;
        nextleft.root= bst->root->left;

        result= result + countNodes(&nextleft);
        result++;
        result= result + countNodes(&nextright);

    }else{
        return 0;
    }
    
    return result;
}

int countLeafNodes(struct BST* bst){

    int result=0;

    if (bst->root!=NULL)
    {
        BST nextright;
        nextright.root= bst->root->right;
        BST nextleft;
        nextleft.root= bst->root->left;

        result= result + countNodes(&nextleft);
        if (bst->root->left==NULL && bst->root->right==NULL) result++;
        result= result + countNodes(&nextright);

    }else{
        return 0;
    }
    return result;
}
