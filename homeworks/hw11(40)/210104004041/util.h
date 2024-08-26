#ifndef _UTIL_H_
#define _UTIL_H_

typedef struct node
{
    char name[20];
    int age;

    struct node* mother;
    struct node* father;
    struct node* children[5]; //max 5 children

}node;



void addFT(node **root,const char* treename);
void addNode(node **root,int age,const char *name,const char *mothername,const char *fathername);
void saveFT(node **root,const char *filename);
void saveallpersons(node* root, node** visitedList,FILE *fpt);
void removeFT(const char *filename);
node* searchperson(node** root, const char* name,node **visitedlist);

void loadFT(node **root,const char*filename);
void readfamily(node **root,const char*filename);


#endif /* _UTIL_H_ */
