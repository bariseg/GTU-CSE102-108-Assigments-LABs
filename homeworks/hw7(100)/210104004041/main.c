#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THRESHOLD_VALUE 25
//suggested treshold is 25 //but the value changes depending on the vector count for each word in the dictionaryfile
//0 means words are the same; the greater dissimilarity,the more difference.

#define MAX_WORD_SIZE 30 //max word size is 12 but sometimes i need to store the words itself and the closest together
#define MAX_WORD_COUNT 100 //that user inputs and words in ignorefile
#define MAX_DICT_WORD_COUNT 5000
#define MAX_INPUT_WORD_COUNT 300000
#define MAX_LINE_SIZE 3000
#define MAX_VECTOR_COUNT 400


int str_comparer(const char str1[], const char str2[]);

int read_dict(const char * file_name, char dict[MAX_DICT_WORD_COUNT][MAX_WORD_SIZE]);
int read_text(const char * text_file, const char * ignore_file, char words[MAX_INPUT_WORD_COUNT][MAX_WORD_SIZE]);
double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, int *index);
int histogram(const char words[][MAX_WORD_SIZE], const int occurrences[], char hist[][MAX_WORD_SIZE+5+20]);


int main(){

    char input_str[MAX_LINE_SIZE];
    char search_words[MAX_WORD_COUNT][MAX_WORD_SIZE]; 
    int word_count = 0; //word count user input
    char *word ;

    printf("Enter word(s):");
    fgets(input_str, MAX_LINE_SIZE, stdin);
    
    word= strtok(input_str, " ");

    while (word != NULL) { //seperates all words from the input

        strcpy(search_words[word_count],word);
        if(search_words[word_count][strlen(search_words[word_count])-1]=='\n') 
            search_words[word_count][strlen(search_words[word_count])-1]='\0'; //REMOVEs the \n if exist 
        
        word_count++;
        word = strtok(NULL, " ");
    }
    /*
    for (int i = 0; i < word_count; i++)
    {
        printf("%d %s\n",i,search_words[i]);
    }*/
    
    

    //reading dictionary
    char dictionary[MAX_DICT_WORD_COUNT][MAX_WORD_SIZE];
    char file_name[20]="dictionary.txt";

    //printf("Enter dictionary file name:");
    //scanf("%s",file_name);

    int dict_word_count;
    dict_word_count=read_dict(file_name,dictionary);
    
    //printf("%d\n",dict_word_count);
    //printf("%s",dictionary[1001]);
    //reading inputtxt
    
    char allwordsread[MAX_INPUT_WORD_COUNT][MAX_WORD_SIZE];
    int input_word_count=0;
    char input_file_name[20]="input.txt";
    char ignore_file_name[20]="ignore.txt";
    input_word_count =read_text(input_file_name,ignore_file_name,allwordsread);
    int scale=1;

    //printf("inwordcount:%d\n",input_word_count);

    //the main part
    if (word_count==1)
    {
        int occurence=0;
        
        for (int i = 0; i < input_word_count; i++)
        {
            if (str_comparer(search_words[0],allwordsread[i]))
                occurence++;
            
        }

        if (occurence>0)
        {
            printf("\"%s\" appears in \"%s\" %d times.\n\n",search_words[0],input_file_name,occurence);
        }else{

            //en yakini arayacak
            float thrshld=THRESHOLD_VALUE;
            int index=0;
            double dissim=0;
            double closer_dissim=100;
            int closer_index=0;
            int error_flag=0;
            //tester
            //dissim=dissimilarity(search_words[0],dictionary[5],dictionary,thrshld,&index);
            //printf("%lf",dissim);
            for (int i = 0; i < dict_word_count; i++)
            {
                dissim=dissimilarity(search_words[0],dictionary[i],dictionary,thrshld,&index);
                //printf("%s--%s %.4lf\n",search_words[0],dictionary[i],dissim);

                if (dissim==-1){
                    printf("The word you entered does not exist in dictionary!!\n\n");
                    error_flag=1;
                    break;
                }
                if (dissim<closer_dissim && dissim!=0)
                {
                    closer_dissim=dissim;
                    closer_index=i;
                }

            }
            if (!error_flag){
                for (int i = 0; i < input_word_count; i++)
                {
                    if (str_comparer(dictionary[closer_index],allwordsread[i])) occurence++;
                }

                if (closer_dissim>=THRESHOLD_VALUE && occurence>0)
                {
                    printf("\"%s\" does not appear in \"%s\"\nbut the closest word \"%s\" appears %d\n\n",search_words[0],input_file_name,dictionary[closer_index],occurence);
                }else{
                    printf("\"%s\" does not appear in \"%s\",and the closest word \"%s\" is not close enough or also does not appear!!\n\n",search_words[0],input_file_name,dictionary[closer_index]);
                
                }
            }
        }

    }else if(word_count>1)
    {
        char hist_array[MAX_WORD_COUNT][MAX_WORD_SIZE+5+20];
        char wordstosent[MAX_WORD_COUNT][MAX_WORD_SIZE];
        int occurence;
        int occurences[MAX_WORD_COUNT];
        int occ_size=0;
        

        for (int swordindex = 0; swordindex < word_count; swordindex++)
        {
            occurence=0;
            for (int i = 0; i < input_word_count; i++)
            {
                if (str_comparer(search_words[swordindex],allwordsread[i])) occurence++;
            }

            if (occurence==0)
            {
                //en yakını arayacak
                
                float thrshld=THRESHOLD_VALUE;
                int index=0;
                double dissim=0;
                double closer_dissim=100;
                int closer_index=0;
                int error_flag=0;
                
                //tester
                //dissim=dissimilarity(search_words[0],dictionary[5],dictionary,thrshld,&index);
                //printf("%lf",dissim);
                for (int i = 0; i < dict_word_count; i++)
                {
                    dissim=dissimilarity(search_words[swordindex],dictionary[i],dictionary,thrshld,&index);
                    //printf("%s--%s %.4lf\n",search_words[0],dictionary[i],dissim);

                    if (dissim==-1){
                        printf("The word you entered does not exist in input file and dictionary\nso couldnt find the closest word!!\n\n");
                        error_flag=1;
                        break;
                    }
                    if (dissim<closer_dissim && dissim!=0)
                    {
                        closer_dissim=dissim;
                        closer_index=i;
                    }

                }
                if (!error_flag){
                    for (int i = 0; i < input_word_count; i++)
                    {
                        if (str_comparer(dictionary[closer_index],allwordsread[i])) occurence++;
                    }
                    if (closer_dissim>=THRESHOLD_VALUE && occurence>0)
                    {
                        //en yakin kelime bulundu occur hesaplandi
                        occurences[swordindex]=occurence;
                        strcat(wordstosent[swordindex],search_words[swordindex]);
                        strcat(wordstosent[swordindex],"*"); //thats a indicator for histogram to understand the word it looks at is a closest word
                        strcat(wordstosent[swordindex],dictionary[closer_index]);
                        
                    }else{
                        //en yakin kelime bulunamadi ya da 0 occ
                        occurences[swordindex]=occurence;
                        strcat(wordstosent[swordindex],search_words[swordindex]);
                    }

                }

            }else{
                occurences[swordindex]= occurence;
                strcat(wordstosent[swordindex],search_words[swordindex]);
            }
            //printf("%d %s\n",occurences[swordindex],wordstosent[swordindex]);
            occ_size=swordindex;
        }
        
        occ_size++;
        occurences[occ_size]=-1;//sentinel value to be used in histogram


        scale=histogram(wordstosent,occurences,hist_array);

        printf("Scale %d\n\n",scale);
        int k=0;
        while (occurences[k]!=-1)
        {
            
            printf("%-25s\n",hist_array[k]);

            k++;
        }

    }
    

    return 0;
}

int read_dict(const char * file_name, char dict[MAX_DICT_WORD_COUNT][MAX_WORD_SIZE]) {
   
    FILE *fpt;

    char line[MAX_LINE_SIZE];
    
    fpt = fopen(file_name, "r");
    //printf("as");
    if (fpt == NULL) {
        printf("File cant be opened!\n");
        fclose(fpt);
        return -1;
    }
    
    int num_words = 0;

    fgets(line, 100, fpt); //first line
    char *word = strtok(line, " ");

    int j;
    while (fgets(line, 2000, fpt) != NULL) {
        //printf("%s\n",line);
        
        word = strtok(line , " ");
        
        //printf("%c\n",word[0]);
        
        j=0;
        while (word[j]!='\0')
        {
            dict[num_words][j]= word[j];
            j++;
        }
        dict[num_words][j]='\0';
        //printf("%s\n",dict[num_words]);
        

        //printf("%s**\n",array_elements[num_words]);
        
        num_words++;
    }
    dict[num_words][0]= '-';
    dict[num_words][1]= '\0';

    fclose(fpt);
    return num_words;
}

int read_text(const char * text_file, const char * ignore_file, char words[MAX_INPUT_WORD_COUNT][MAX_WORD_SIZE]){

    
    FILE* ignorefpt;

    char ignore_line[MAX_WORD_SIZE];
    char ignored_words[MAX_WORD_COUNT][MAX_WORD_SIZE];

    ignorefpt=fopen(ignore_file,"r");
    
    if (ignorefpt==NULL)
    {
        printf("Ignore file opening error!!");
        fclose(ignorefpt);
        return -1;
    }

    int index=0;
    int len;
    
    while ((fgets(ignore_line,MAX_WORD_SIZE,ignorefpt))!=NULL)
    {   
        
        len=(int)strlen(ignore_line);

        ignore_line[len-2]='\0'; //removes the \n 

        //printf("%s",ignore_line);

        strcpy(ignored_words[index],ignore_line);

        index++; //also counts the words
    }

    fclose(ignorefpt);
    
    //***************************************

    FILE* fpt;
    int word_count=0;
    char line[MAX_LINE_SIZE];
    char* word;


    fpt=fopen(text_file,"r");
    if (fpt==NULL)
    {
        printf("input file opening error!\n");
        fclose(fpt);
        return -1;
    }

    int match_flag;
    while ((fgets(line,MAX_LINE_SIZE,fpt))!=NULL)
    {
        //"I see 
        
        word = strtok(line, " \n!\"&'()*+,-./:;?[\\]_`{|}~");
        
        while (word!=NULL)
        {   
            match_flag=0;
            for (int ignoreindex = 0; ignoreindex < index; ignoreindex++)
            {
                //printf("%s",ignored_words[ignoreindex]);
                if (strcmp(ignored_words[ignoreindex],word)==0)
                {
                    match_flag=1;
                    //printf("%s",ignored_words[ignoreindex]);
                    
                }
            }
            if (!match_flag)
            {
                strcpy(words[word_count],word);
                //printf("%d %s\n",word_count,words[word_count]);
                word_count++;
                
            }
            
            word = strtok(NULL, " \n!\"&'()*+,-./:;?[\\]_`{|}~");
        }

        

    }
    fclose(fpt);

    strcpy(words[word_count],"-");
    //word_count++;

    return word_count;

}

double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, int *index){

    int indx=0; //i didnt want to use * for each situation // is 0 for beginning
    double vectors1[MAX_VECTOR_COUNT];
    double vectors2[MAX_VECTOR_COUNT];

    //first find the w1's vectors
    do
    {
        if (str_comparer(w1,dict[indx]))
        {
            
            break;
        }
        indx++;
        //printf("%d %s\n",indx,dict[indx]);
    } while (dict[indx][0]!='-');
    
    if (dict[indx][0]=='-')
    {
        //printf("The word \"%s\" doesnt exist in dictionary\n",w1);
        return -1;
    }

    
    FILE*fpt=fopen("dictionary.txt","r");
    if (fpt==NULL)
    {
        fclose(fpt);
        printf("Dictionary file opening error in dissimilarity function!\n\n");
        return -1;
    }


    char line[MAX_LINE_SIZE];
    char *cursormover;

    fgets(line,MAX_LINE_SIZE,fpt);
    cursormover=strtok(line, " ");
    for (int linenum = 2; linenum <= indx+2; linenum++)
    {
        
        fgets(line,MAX_LINE_SIZE,fpt);
        cursormover=strtok(line, " ");

        //printf("%s\n",cursormover);

    }

    cursormover=strtok(NULL, " ");
    
    for (int vnum = 1; vnum <= MAX_VECTOR_COUNT; vnum++)
    {
        
        if (cursormover==NULL)
        {
            break;
        }else{
            vectors1[vnum-1]= atof(cursormover);
            //printf("%lf**",vectors1[vnum-1]);
        }
        cursormover=strtok(NULL, " ");

    }

    rewind(fpt);

    //now find w2's vectors
    indx=0;
    do
    {
        if (str_comparer(dict[indx],w2))
        {
            break;
        }
        indx++;
    } while (dict[indx][0]!='-');
    
    fgets(line,MAX_LINE_SIZE,fpt);
    cursormover=strtok(line, " ");
    for (int linenum = 2; linenum <= indx+2; linenum++)
    { 
        fgets(line,MAX_LINE_SIZE,fpt);
        cursormover=strtok(line, " ");  
    }
    //printf("%s\n",cursormover);

    cursormover=strtok(NULL, " "); //moves to first vector in the line
    int vector_count=0;

    for (int vnum = 1; vnum <= MAX_VECTOR_COUNT; vnum++)
    {
        if (cursormover==NULL)
        {
            vector_count=vnum-1;
            break;
        }else{
            vectors2[vnum-1]= atof(cursormover);
            //printf("%lf**",vectors2[vnum-1]);
        }
        cursormover=strtok(NULL, " ");
    }   
    fclose(fpt);

    //now i do the calculations
    
    double vector_diff[MAX_VECTOR_COUNT];

    for (int vi = 0; vi < vector_count; vi++)
    {
        vector_diff[vi]= vectors1[vi]- vectors2[vi];
        //printf("%.5lf  ",vector_diff[vi]);
    }
    
    double sums_of_vector_squared=0;

    for (int vi = 0; vi < vector_count; vi++)
    {
        sums_of_vector_squared= sums_of_vector_squared + vector_diff[vi]*vector_diff[vi];
    }
    //printf("%lf sums", sums_of_vector_squared);
    
    
    return sums_of_vector_squared;
    
    return 0;
}

int str_comparer(const char str1[], const char str2[]){
    int i = 0;
    while (str1[i] == str2[i])
    {
        if (str1[i] == '\0' && str2[i] == '\0')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int histogram(const char words[][MAX_WORD_SIZE], const int occurrences[], char hist[][MAX_WORD_SIZE+5+20]){

    //eger occur 0sa hic yok.
    //* varsa   original*closest  occur= closestoccur
    
    int stars[MAX_WORD_COUNT];
    int scale=1;
    int m=0;
    //printf("histogram\n");
    

    while (occurrences[m]!=-1)
    {
        stars[m]=occurrences[m]; //gonna manipulate stars because occurenses is const array
        m++;
    }
    stars[m]=occurrences[m]; // -1 value
    
    m=0;
    int max_stars=stars[0];
    while (stars[m]!=-1)
    {
        if (stars[m]>max_stars)
        {
            max_stars=stars[m];
        }
        m++;
    }

    int n;
    if (max_stars>20)
    {   
        scale=(max_stars/20)+1;
        n=0;
        while (stars[n]!=-1)
        {
            
            stars[n]= stars[n]/scale;

            n++;
        }
        
    }

    m=0;
    
    

    int j=0;
    while (occurrences[j]!=-1)
    {
        //printf("star:%d %s\n",stars[j],words[j]);

        if (occurrences[j]==0)
        {
            strcat(hist[j],words[j]);
            strcat(hist[j],"\t\t\tNO MATCHES");
        }else{
            int ind=0;
            int closesetflag=0;
            while (words[j][ind] != '\0') {
                
                if (words[j][ind] == '*') {
                    closesetflag=1;
                    break;
                }
                ind++;
            }

            if (!closesetflag)
            {
                strcat(hist[j],words[j]);
                strcat(hist[j],"\t\t\t");
                for (int i = 0; i < stars[j]; i++)
                {
                    strcat(hist[j],"*");
                }

            }else{
                char temp_word[MAX_WORD_SIZE];
                stpcpy(temp_word,words[j]); //as words is constant array
                char *original= strtok(temp_word, "*");
                strcat(hist[j],original);
                strcat(hist[j],"->");
                original=strtok(NULL, "*");
                strcat(hist[j],original);
                strcat(hist[j],"\t");

                for (int i = 0; i < stars[j]; i++)
                {
                    strcat(hist[j],"+");
                }


            }
            
        }
        j++;
    } 
    return scale;

}