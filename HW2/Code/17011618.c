#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdio.h>
#include <ctype.h>

#define TABLE_SIZE 997
#define M TABLE_SIZE
#define MM M-1

typedef struct{
	char* key;
	char* value;
} hashTableItem;

typedef struct{
	int size;
	int count;
	hashTableItem** items;
}hashTable;


hashTable* createHashTable(){
	hashTable* ht = malloc(sizeof(hashTable));
	
	ht -> size = TABLE_SIZE;
	ht -> count = 0;
	ht -> items = calloc((size_t) ht -> size, sizeof(hashTableItem*));
	return ht;
}

hashTableItem* newItem(char* key, char* value){
	hashTableItem* i = malloc(sizeof(hashTableItem));
	i -> key = strdup(key);
	i -> value = strdup(value);
	return i;
}

int hashTheKey(char* key, int a, int m){
	long hash = 0;
	int len_s = strlen(key);
	for(int i = 0; i < len_s; i++){
		hash += (long)pow((double)a, (double)len_s - (i + 1)) * key[i];
		hash %= m;
	}
	return (int)m;
}

int doubleHashing(char* key, int num_buckets, int attempt){
	int hashA = hashTheKey(key, M, num_buckets);
	int hashB = hashTheKey(key, MM, num_buckets);
	return (hashA + (attempt * (hashB + 1))) % num_buckets;
}

int search(hashTable* ht, char* key){
	int index = doubleHashing(key, ht -> size, 0);
	hashTableItem* item = ht -> items[index];
	int i = 1;
	
	while(item != NULL && i < ht -> size){
        if(strcmp(item -> key, key) == 0){
            return index;
        }
		index = doubleHashing(key, ht -> size, i);
		i ++;
		item = ht -> items[index];
	}
    if(item == NULL ){
	    return index;
    } else {
        return -1;
    }
}

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 4);
    char delimiter[5] = "|";
    strcpy(result, s1);
    strcat(result, delimiter);
    strcat(result, s2);
    return result;
}

float insert(hashTable* ht, char* key, char* value){
	int index = search(ht,key);
    if((float)(ht->count)/(ht->size) > 1 || index < 0){
        printf("%s\n",key);
        return (float)(ht->count)/(ht->size);
    }
    
    if(ht -> items[index] == NULL) {
        if((float)(ht->count)/(ht->size) > 0.8){
            printf("Load Factor: %f - Attention\n%s added\n",(float)(ht->count)/(ht->size),key);
        } else {
            printf("Load Factor: %f\n%s added\n",(float)(ht->count)/(ht->size),key);
        }
        hashTableItem* item = newItem(key, value);
        ht -> items[index] = item;
        ht -> count ++;
    } else {
        char *baseValue = malloc(strlen(ht -> items[index] -> value)+1);
        strcpy(baseValue,ht -> items[index] -> value);
        char *pt;
        int find = 0;
        pt = strtok (baseValue,"|");
        while (pt != NULL && find != 1) {
            if(strcmp (pt, value) == 0) {
                find = 1;
            }
            pt = strtok (NULL, "|");
        }
        if(find == 0){
            char *newValue = concat(baseValue, value);
            hashTableItem* item = newItem(key, newValue);
            free(ht -> items[index]);
            ht -> items[index] = item;
        }
    }
    
    return (float)(ht->count)/(ht->size);
}

int readHashFile(hashTable* ht){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int count = 0;
    fp = fopen("17011618.txt", "r");
    if (fp == NULL)
        return(-1);
    
    while ((read = getline(&line, &len, fp)) != -1) {
        char *pt;
        char *key ;
        char *value;
        int i = 0;
        int index = 0;
        // id
        pt = strtok (line," \n");

        while (pt != NULL) {
            if(i == 0 ){
                index = atoi(pt);
            } else if ( i == 1 ){
                key = malloc(strlen(pt)+1);
                strcpy(key,pt);
            } else {
                if( pt[strlen(pt)-1] == '\n' )
                    pt[strlen(pt)-1] = 0;
                value = malloc(strlen(pt)+1);
                strcpy(value,pt);
            }
            i++;
            pt = strtok (NULL, " ");
        }
        hashTableItem* item = newItem(key, value);
        ht -> items[index] = item;
        count++;
    }
    ht -> count = count;
    fclose(fp);
    if (line)
        free(line);
    return 0;
}

char *concatWrite(int i,char *key,char *value){
    char buffer[20];
    char *string = malloc(15+strlen(key) + strlen(value));
    sprintf(buffer, "%d", i);
    strcpy(string,buffer);
    strcat(string," ");
    strcat(string, key);
    strcat(string," ");
    strcat(string,value);
    strcat(string,"\n");
    return string;
}

void writeHashTable (hashTable* ht) {
    FILE * fp;
    int i = 0;
    fp = fopen("17011618.txt", "w");
    if (fp == NULL)
        return;
    
    while(i < TABLE_SIZE){
        if(ht->items[i] != NULL) {
            char *string = concatWrite(i,ht->items[i] -> key,ht->items[i] -> value);
            fputs(string,fp);
        }
        i++;
    }
    fclose(fp);
}

void readFile(hashTable* ht,char *fileName){
    FILE * fp;
    int i = 0, j = 150;
    int htIsFull = 0;
    float loadFactor = 0.0;
    fp = fopen(fileName, "r");
    char c; 
    char string[1024];
    while(j != -1){
        string[j+3] = '\0';
        string[j+2] = '\0';
        string[j+1] = '\0';
        string[j] = '\0';
        j--;
    }
	j=0;
    while((c = fgetc(fp)) != EOF) { 
		if(c == ' ' || c == '\n' || c == '\0' || c == ',' || c == '.' || c == ':' || c == '?' || c == '!' || c == '\'' || c == '\"' || c == '(' || c == ')' || c == '-' || c == '/' || c == '[' || c == ']') {
            if(j != 0){
                loadFactor = insert(ht,string,fileName);
                if(loadFactor == 1 && htIsFull == 0){
                    htIsFull = 1;
                    printf("Load Factor: %f\nHashtable is FULL\nWe can't add any more word\nWords that cannot be added\n----------------------------------------------------------------\n",loadFactor);
                }
            }
			while(j != -1){
                string[j+3] = '\0';
                string[j+2] = '\0';
                string[j+1] = '\0';
                string[j] = '\0';
                j--;
            }
			j=0;
		} 
		else {
			c=tolower(c);
			string[j]=c;
			j++;
		} 
	}
}

void printValue(char *key, char *value){
    int t = 0;
    char *pt;
    printf("\nThe word is: %s \n", key);
    printf("Existing file names: ");
    pt = strtok (value,"|");
    printf("%s",pt);
    while (pt != NULL) {
        pt = strtok (NULL, " ");
        if( pt == NULL ) break;
        printf(" - %s",pt);
        t++;
    }
    printf("\n");
}

/**
 * Print the hash table
 * @param ht hashtable ( struct table)
 * @return 0
 */ 
void printHashTable(hashTable* ht){
    int i = 0;
	for(i = 0; i < ht -> size; i++){
        //Print item if next is not NULL
		if(ht -> items[i] != NULL){
            printValue(ht -> items[i] -> key,ht -> items[i] -> value);
		}
	}
}



void printMenu(void)  {
	printf("\n\n.:17011618 - Algoritma Analizi - HW2:.\n\n");
	printf("Please select an option:\n");
	printf("\t1 - Read File\n");
	printf("\t2 - Search\n");
    printf("\t3 - Print\n");
	printf("\t0 - exit\n\n\n\t>");
}

int main(int argc, char * argv[]) {
    hashTable* ht = createHashTable();
    readHashFile(ht);
    char input[1024];
    int indis = 0;
    int select=1;
    while(select)  {
		printMenu();
		scanf("%d", &select);
		switch(select)  {
		    case 0: 
				break;
        	case 1: 
                printf("Give me a file name:");
                scanf("%s",input);
				readFile(ht,input);
                writeHashTable(ht);
        		break;
        	case 2: 
				printf("Give me a word:");
                scanf("%s",input);
                indis = search(ht,input);
                if(indis>0){
                    printValue(ht -> items[indis] -> key,ht -> items[indis] -> value);
                } else {
                    printf("The word is not exist\n");
                }
        		break;
            case 3: 
                printHashTable(ht);
                break;
  
		}
    }
}