#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdio.h>
#include <ctype.h>

#define TABLE_SIZE 9973
#define M TABLE_SIZE
#define MM M-1

/**
 * Hashtable item struct
 */
typedef struct{
	char* key;
	char* value;
} hashTableItem;

/**
 * Hashtable struct
 */
typedef struct{
	int size;
	int count;
	hashTableItem** items;
}hashTable;

/**
 * Create hash table
 */
hashTable* createHashTable(){
	hashTable* ht = malloc(sizeof(hashTable));
	
	ht -> size = TABLE_SIZE;
	ht -> count = 0;
	ht -> items = calloc((size_t) ht -> size, sizeof(hashTableItem*));
	return ht;
}
/**
 * New Hashtable item
 */ 
hashTableItem* newItem(char* key, char* value){
	hashTableItem* i = malloc(sizeof(hashTableItem));
	i -> key = strdup(key);
	i -> value = strdup(value);
	return i;
}

/**
 * Hash the key
 */ 
int hashTheKey(char* key, int a, int m){
	long hash = 0;
	int len_s = strlen(key);
	for(int i = 0; i < len_s; i++){
		hash += (long)pow((double)a, (double)len_s - (i + 1)) * key[i];
		hash %= m;
	}
	return (int)m;
}

/**
 * Double Hashing
 */ 
int doubleHashing(char* key, int num_buckets, int attempt){
	int hashA = hashTheKey(key, M, num_buckets);
	int hashB = hashTheKey(key, MM, num_buckets);
	return (hashA + (attempt * (hashB + 1))) % num_buckets;
}

/**
 * Search on the hashtable
 * Its return index
 */ 
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

/**
 * Insert item to the hashtable
 * Its return load factor
 */ 
float insert(hashTable* ht, char* key, char* value){
	int index = search(ht,key);
    if((float)(ht->count)/(ht->size) > 1 || index < 0){
        printf("%s\n",key);
        return (float)(ht->count)/(ht->size);
    }
    
    if(ht -> items[index] == NULL) {
        if((float)(ht->count)/(ht->size) > 0.8){
            printf("Load Factor: %f - Attention\n%s added\n",(float)(ht->count)/(ht->size),key);
        }
		
        hashTableItem* item = newItem(key, value);
        ht -> items[index] = item;
        ht -> count ++;
    }
	
    return (float)(ht->count)/(ht->size);
}

/**
 * Reads dictionary
 */
void readDictionary(hashTable* ht){
	FILE * fp;
    int i = 0, j = 150;
    int htIsFull = 0;
    float loadFactor = 0.0;
    fp = fopen("smallDictionary.txt", "r");
    char c; 
    char string[150];
	for ( j = 150; j > 0; j--)
	{
		string[j] = '\0';
	}
	
	j=0;
    while((c = fgetc(fp)) != EOF) { 
		if(c == ' ' || c == '\n' || c == '\0' || c == ',' || c == '.' || c == ':' || c == '?' || c == '!' || c == '\'' || c == '\"' || c == '(' || c == ')' || c == '-' || c == '/' || c == '[' || c == ']') {
            if(j != 0){
                loadFactor = insert(ht,string,"");
                if(loadFactor == 1 && htIsFull == 0){
                    htIsFull = 1;
                    printf("Load Factor: %f\nHashtable is FULL\nWe can't add any more word\nWords that cannot be added\n----------------------------------------------------------------\n",loadFactor);
                }
            }
			for ( j = 150; j > 0; j--)
			{
				string[j] = '\0';
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

/**
 * create formated string from values.
 * FORMAT: INDEX KEY VALUE\n
 */ 
char *concatWrite(int i,char *key,char *value){
    char buffer[20];
	char *string;
	if(value != NULL){
		string = malloc(25+strlen(key) + strlen(value));
	} else {
		string = malloc(25+strlen(key));
	}
    
    sprintf(buffer, "%d", i);
    strcpy(string,buffer);
    strcat(string," ");
    strcat(string, key);
	strcat(string," ");
	strcat(string,value);
    strcat(string,"\n");
	
    return string;
}


/**
 * Write the hashtable to txt file
 * Its return int -1 Error 0 Non Error
 */ 
int writeHashTable (hashTable* ht, int flag) {
    FILE * fp;
    int i = 0;
	if(flag == 1){
		fp = fopen("mistakenWords.txt", "w");
		if (fp == NULL)
			return(-1);
	} else {
		fp = fopen("dictionary.txt", "w");
		if (fp == NULL)
			return(-1);
	}
    
    while(i < TABLE_SIZE){
        if(ht->items[i] != NULL) {
            char *string = concatWrite(i,ht->items[i] -> key, ht->items[i] -> value);
            fputs(string,fp);
        }

        i++;
    }
	fclose(fp);
	return 0;
}

/**
 * If flah equal to 1 its "Hatalı Kelimler"
 * Else Dictionary
 */ 
int readHashFile(hashTable* ht,int flag){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int count = 0;
	if(flag == 1){
		fp = fopen("mistakenWords.txt", "r");
		if (fp == NULL){
			fp = fopen("mistakenWords.txt","w");
			if(fp == NULL){
				return -1;
			}
		}
	} else {
		fp = fopen("dictionary.txt", "r");
		if (fp == NULL){
			readDictionary(ht);
			writeHashTable(ht,flag);
			return 0;
		}
	}
    
    
    while ((read = getline(&line, &len, fp)) != -1) {
        char *pt;
        char *key ;
        char *value="";
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

/**
 * Print the hash table
 * @param ht hashtable ( struct table)
 * @return 0
 */ 
void printHashTable(hashTable* ht,int flag){
    int i = 0;
	for(i = 0; i < ht -> size; i++){
        //Print item if next is not NULL
		if(ht -> items[i] != NULL){
			printf("Word is %s",ht -> items[i] -> key);
			if (flag == 1){
				printf(" Did you mean: %s",ht -> items[i] -> value);
			}
            printf("\n");
		}
	}
}

/**
 * İlk olarak Hash Tablolarını hazırla ( Kelimeler ve Hatalı kelimeler için)
 * Input al ve inputu hash tablosu ile karşılaştır. Hash tablosunda yoksa Did you mean?
 * Maksimum uzunluk farkı 2 olan kelimeleri seç(önce 1) 2 ayrı liste tut burada 1 uzaklık ve 2 uzaklık olanları
 * iç taramada satırın tamamı 2yi geçerse işlemi durdur.
 * Kullanıcıya verilen önerileri sun. Seçileni hatalı kelimeler hash tablosuna ekle
 */ 

/***
 *  Sözlük tablosunda arama yap
 * 	Sözlük tablosunda yoksa hatalı kelime tablosunda arama yap
 * 	TODO: Hatalı kelime tablosunda da yoksa Distance hesapla
 * 	Distancelara göre seçim yaptır.
 * 	Seçim sonucuna göre hatalı kelime tablosuna ekleme yap
 */




int levenshtein(const char * word1,const char * word2, int maxDistance)
{
	int len1 = strlen(word1);
	int len2 = strlen(word2);
    int matrix[len1 + 1][len2 + 1];
    int i, j, notBreak = 1, maximum, delete,insert,substitute,minimum;
    char c1,c2;
    for (i = 0; i <= len1; i++) {
        matrix[i][0] = i;
        matrix[0][i] = i;
    }
	i = 1;
    while (i <= len1 && notBreak == 1) {
		maximum = 100;
        c1 = word1[i-1];
		notBreak = 0;
        for (j = 1; j <= len2; j++) {
            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
			if(matrix[i][j] < maximum){
				maximum = matrix[i][j];
			}
        }
		if(maximum <= maxDistance){
			notBreak = 1;
		}
		i++;
    }
	if(notBreak == 0) {
		return 500;
	} else {
		return matrix[len1][len2];
	}
}


/**
 * Verilen kelime için distanceları hesaplar
 */ 
int findDistance(hashTable* ht,char *keyword, int *array){
	int count = 0, i = 0, length = 0, result = 0, tur = 0, maxDistance = 1;

	while(tur < 2 ){	
		i = 0;
		while(i<TABLE_SIZE){
			if(ht->items[i] != NULL){
				length = strlen(keyword) - strlen(ht->items[i]->key);
				if(abs(length)<maxDistance){
					result = levenshtein(keyword,ht->items[i]->key,maxDistance);
					if(result <= maxDistance){
						array[count] = i;
						count++;
					}
				}
			}
			i++;
		}
		if(count == 0){
			tur++;
			maxDistance++;
		} else {
			tur = 99;
		}
	}
	return count;
}

void searchKeyword(hashTable* words, hashTable* mistaken, char *keyword){
	int index = -1, choosen = -1, i = 0, count = 0, indexs[10] ;
	index = search(words,keyword);
	
	if(words -> items[index] == NULL){
		index = search(mistaken,keyword);
	} else {
		printf("\n%s, no problem!\n",keyword);
		return;
	}

	
	if(mistaken -> items[index] == NULL){
		count = findDistance(words, keyword,indexs);
		if(count > 0){
			printf("Please choose correct word for %s\n",keyword);
			while( i < count){
				printf("%d -> %s\n",i, words -> items[indexs[i]] -> key);
				i++;
			}
			scanf("%d",&choosen);
			insert(mistaken,keyword,words -> items[indexs[choosen]]->key);
			writeHashTable(mistaken,1);
			printf("Result is updated! %s is %s\n",keyword,words -> items[indexs[choosen]]->key);
		} else {
			printf("We dont have any correction ...\n");
		}
		
	} else {
		printf("For %s -> Did you mean: %s\n",keyword,mistaken -> items[index]-> value);
	}
}

int main()
{
	char string[1024], *str, ch;

	hashTable* words = createHashTable();
	hashTable* mistaken = createHashTable();
	readHashFile(words,0);
	readHashFile(mistaken,1);
	printf("Please give a string:\n>");
	fgets(string,1023,stdin);

	if ((strlen(string) > 0) && (string[strlen (string) - 1] == '\n'))
        string[strlen (string) - 1] = '\0';

  
    for(int i = 0; string[i]; i++){
  		string[i] = tolower(string[i]);
	}

	char * pch;
	pch = strtok (string," ");
	while (pch != NULL )
	{
		searchKeyword(words,mistaken,pch);
		pch = strtok (NULL, " ");
	}
	return 0;
}