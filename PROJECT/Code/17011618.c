#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOK_COUNT 50
#define MAX_USER_COUNT 150
#define MAX_BOOK_NAME_LENGHT 128

int main(void)
{
    /**
     * Read the CSV
     */ 
    FILE* FP;
    int bufferLength = MAX_BOOK_COUNT*MAX_BOOK_NAME_LENGHT;
    char buffer[bufferLength];
    
    /**
     * 
     */ 
    int lineCount = 0;
    int userCount = 0;
    int bookCount = 0;
    int i = 0;
    char *token;
    const char whatIsTheParse[2] = ";";
    /**
     * Books and Matrix
     */ 
    char Books[MAX_BOOK_COUNT][MAX_BOOK_NAME_LENGHT];
    int Users[MAX_USER_COUNT][MAX_BOOK_COUNT];

    FP = fopen("RecomendationDataSet.csv", "r");

    while(fgets(buffer, bufferLength, FP)) {
        if(lineCount == 0) {
            token = strtok(buffer, whatIsTheParse);
   
            while( token != NULL ) {
                int tokenLength = strlen(token);
                if(token[tokenLength -1 ] == '\n'){
                    token[tokenLength -1 ] = '\0';
                }
                if(strcmp(token," ") != 0){
                    strcpy(Books[bookCount],token);
                    bookCount++;

                }
                token = strtok(NULL, whatIsTheParse);
            }

        } else {
            i = 0;
            token = strtok(buffer, whatIsTheParse);
   
            while( token != NULL ) {
                int tokenLength = strlen(token);
                if(token[tokenLength -1 ] == '\n'){
                    token[tokenLength -1 ] = '\0';
                }
                if(i != 0){
                    if(strcmp(token," ") != 0){
                        Users[userCount][i-1] = atoi(token);
                    } else {
                        Users[userCount][i-1] = 0;
                    }
                }
                i++;
                
                token = strtok(NULL, whatIsTheParse);
            }
            userCount++;
        }
        lineCount++;
    }
    for (i = 0; i < bookCount; i++)
    {
        printf("%d. Kitap: %s\n", i,Books[i]);
    }

    for ( i = 0; i < userCount; i++)
    {
        for (int y = 0; y < bookCount; y++)
        {
            printf("User: %d Book:%d Puan: %d\n",i,y,Users[i][y]);
        }
        
    }
    
    
    fclose(FP);
}