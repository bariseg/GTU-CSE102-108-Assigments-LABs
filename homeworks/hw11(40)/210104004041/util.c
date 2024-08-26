#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void addFT(node **root,const char* treename){

    char option;
    int menuflag=1;
    

    do
    {
        printf("1. Add node\n2. Save Family tree\n3. Return to main menu\n>");
        scanf(" %c",&option);

        switch (option){
            case '1':
                char tempname[20],momname[20],fathername[20];
                int age;

                printf("Enter name:");
                scanf(" %s",tempname);
                printf("Enter age:");
                scanf("%d",&age);
                printf("Enter mother name:");
                scanf(" %s",momname);
                printf("Enter fathername:");
                scanf(" %s",fathername);

                addNode(root,age,tempname,momname,fathername);
                break;
            case '2':
                saveFT(root,treename);
                break;
            case '3':
                printf("Returning to main menu!\n");
                menuflag= 0;
                break;

            default :
                printf("Invalid input!!\n");
                break;
        }
    } while (menuflag);
}


void addNode(node **root,int age,const char *name,const char *mothername,const char *fathername){

    node * newnode= (node*)malloc(sizeof(node));
    newnode->age= age;
    strcpy(newnode->name,name);
    for (int i = 0; i < 5; i++) newnode->children[i]=NULL;
    

    if ((*root)== NULL){
        newnode->father=NULL;
        newnode->mother=NULL;
        (*root)= newnode;
    }else{

        
        node **visitedlist= (node**)malloc(sizeof(node*)*20);
        for (int i = 0; i < 20; i++) visitedlist[i]= NULL;
        node * mother= searchperson(root,mothername,visitedlist);
        free(visitedlist);
        if (mother!=NULL)
        {
            printf("mother found:%s\n",mother->name);
            newnode->mother= mother;
            for (int i = 0; i < 5; i++)
            {
                if (mother->children[i]==NULL){
                    mother->children[i]= newnode;
                    break;
                }
            }
        }else{
            printf("mom cant found!! being added\n");
            mother= (node*)malloc(sizeof(node));
            strcpy(mother->name,mothername);
            int mage;
            printf("enter mother age:");
            scanf("%d",&mage);
            mother->age=mage;
            mother->mother=NULL;
            mother->father=NULL;
            newnode->mother= mother;
            
            
            for (int i = 0; i < 5; i++) mother->children[i]= NULL;
            for (int i = 0; i < 5; i++)
            {
                if (mother->children[i]==NULL){
                    mother->children[i]= newnode;
                    break;
                }
            }

            
        }
        

        node **visitedlist2= (node**)malloc(sizeof(node*)*20);
        for (int i = 0; i < 20; i++) visitedlist2[i]= NULL;
        
        node *father= searchperson(root,fathername,visitedlist2);
        free(visitedlist2);

        if (father!=NULL)
        {   
            printf("father found:%s\n",father->name);
            newnode->father= father;
            for (int i = 0; i < 5; i++)
            {
                if (father->children[i]==NULL){
                    father->children[i]= newnode;
                    break;
                }
            }
        }else { 
            printf("father cant found ,being added!\n");
            father= (node*)malloc(sizeof(node));
            strcpy(father->name,fathername);
            int fage;
            printf("enter father age:");
            scanf("%d",&fage);
            father->age=fage;
            father->father=NULL;
            father->mother=NULL;
            newnode->father= father;
            
            for (int i = 0; i < 5; i++) father->children[i]= NULL;
            for (int i = 0; i < 5; i++)
            {
                if (father->children[i]==NULL){
                    father->children[i]= newnode;
                    break;
                }
            }

        }

    }

    

}

node* searchperson(node** root, const char* name,node **visitedlist){

    for (int i = 0; visitedlist[i] != NULL; i++)
    {
        //printf("%dtest:%s\n",i,visitedlist[i]->name);
        if (visitedlist[i]== (*root)){
            //printf("%donceden bakilmis:%s\n",i,(*root)->name);
            return NULL;
        }
    }

    for (int i = 0; i < 20; i++)
    {
        if (visitedlist[i]==NULL){
            visitedlist[i]= (*root);
            break;
        }
    }

    if ((*root) == NULL){
        return NULL;
    }else{
        
        if (strcmp((*root)->name, name) == 0){
            return (*root);
        }else{
            
            node* child;
            node *person;
            for (int i = 0; i < 5; i++)
            {
                child=(*root)->children[i];
                if (child != NULL){

                    if (strcmp(child->name, name) == 0) return child;

                    person = searchperson(&child, name,visitedlist);
                    if (person != NULL) return person;
                }
            }

            node* mother = (*root)->mother;
            if (mother != NULL)
            {
                if (strcmp(mother->name, name) == 0) return mother;
                    
                person = searchperson(&mother, name,visitedlist);
                if (person != NULL) return person;
                    
            }
            
            node* father = (*root)->father;
            if (father != NULL)
            {
                if (strcmp(father->name, name) == 0) return father;
                    
                person = searchperson(&father, name,visitedlist);
                if (person != NULL) return person;
                    
            }

        }
    }
    return NULL;
}

void saveFT(node **root,const char *filename){

    FILE * fpt= fopen(filename,"w");

    fprintf(fpt,"%s,",(*root)->name);
    fprintf(fpt,"%d,",(*root)->age);
    fprintf(fpt,"null,");
    fprintf(fpt,"null\n");

    node **visitedlist= (node**)malloc(sizeof(node*)*20);

    for (int i = 0; i < 20; i++) visitedlist[i]=NULL;
    visitedlist[0]= (*root);

    saveallpersons((*root)->children[0],visitedlist,fpt);

    fclose(fpt);
}

void saveallpersons(node* root, node** visitedList,FILE *fpt){

    if (root == NULL) {
        return;
    }
    
    for (int i = 0; i < 20; i++) {
        if (visitedList[i] == root) {
            return;
        }
    }

    for (int i = 0; i < 20; i++)
    {
        if (visitedList[i]==NULL)
        {
            visitedList[i]= root;
            break;
        }
        
    }

    

    fprintf(fpt,"%s,",root->name);
    fprintf(fpt,"%d,",root->age);
    if (root->mother!=NULL){
        fprintf(fpt,"%s,",root->mother->name);
    }else{
        fprintf(fpt,"null,");
    }
    
    if (root->father!=NULL){
        fprintf(fpt,"%s\n",root->father->name);
    }else{
        fprintf(fpt,"null\n");
    }

    saveallpersons(root->father, visitedList,fpt);
    saveallpersons(root->mother, visitedList,fpt);
    for (int i = 0; i < 5; i++) {
        saveallpersons(root->children[i], visitedList,fpt);
    }

}

void removeFT(const char *filename){
    remove(filename); // :D
}

void loadFT(node **root,const char*filename){

    char option;
    int menuflag=1;
    
    do
    {
        printf( "this part is not implemented sorry! iyi bayramlar\n"
                "1. Add new person(not yet)\n"
                "2. Remove a person(not yet)\n"
                "3. Print person's nuclear family(not yet)\n"
                "4. Search relatives of given person(not yet)\n"
                "5. Return to the main menu\n"
                ">" );
        scanf(" %c",&option);

        switch (option){
            case '1':
                
                break;
            

            case '5':
                printf("Returning to main menu!\n");
                menuflag= 0;
                break;

            default :
                printf("Invalid input!!\n");
                break;
        }
    } while (menuflag);


}

void readfamily(node **root,const char*filename){

    FILE *fpt= fopen(filename,"r");

    //node *newnode= (node*)malloc(sizeof(node));




    fclose(fpt);
}

