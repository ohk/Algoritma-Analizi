#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#define ARRAY_LENGHT 100
#define MAX_RANDOMIZE 100000

/* C implementation QuickSort */
#include<stdio.h> 

// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 


int partition (int array[], int low, int high) 
{ 
	int pivot = array[high]; 
	int i = (low - 1);

	for (int j = low; j <= high- 1; j++) 
	{ 
		if (array[j] < pivot) 
		{ 
			i++;
			swap(&array[i], &array[j]); 
		} 
	} 
	swap(&array[i + 1], &array[high]); 
	return (i + 1); 
} 

void quickSort(int array[], int low, int high) 
{ 
	if (low < high) 
	{ 
		int index = partition(array, low, high); 
		quickSort(array, low, index - 1); 
		quickSort(array, index + 1, high); 
	} 
} 



void bruteForce(int array[]){
   int i = 0, t = 0,minDiff = MAX_RANDOMIZE*2, dif1=0,dif2=0;
   clock_t begin = clock();
   for(i = 0; i < ARRAY_LENGHT; ++i) {
      for(t = 0; t < ARRAY_LENGHT; ++t) {
         if (i != t && minDiff > abs(array[i] - array[t]))
         {
            minDiff = abs(array[i]-array[t]);
            dif1 = array[i];
            dif2 = array[t];
         }
      }
   }
   clock_t end = clock();
   double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("Technique: Brute Force\nEn Yakın Değer: %d\nSayı 1: %d\nSayı 2: %d\nÇalışma süresi: %f\n",minDiff,dif1,dif2,time_spent);
}

void bruteForceSecond(int array[]){
   int i = 0, t = 0,minDiff = MAX_RANDOMIZE*2, dif1=0,dif2=0;
   clock_t begin = clock();
   for(i = 0; i < ARRAY_LENGHT; ++i) {
      for(t = 0; t < ARRAY_LENGHT; ++t) {
         if (i != t && minDiff > abs(array[i] - array[t]))
         {
            minDiff = abs(array[i]-array[t]);
            dif1 = array[i];
            dif2 = array[t];
         }
      }
   }
   clock_t end = clock();
   double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("Technique: Brute Force (Sıralama yer değiştirdikten sonra)\nEn Yakın Değer: %d\nSayı 1: %d\nSayı 2: %d\nÇalışma süresi: %f\n",minDiff,dif1,dif2,time_spent);
}

void withQuicksort(int array[]){
   int i = 0, t = 0,minDiff = MAX_RANDOMIZE*2, dif1=0,dif2=0;
   clock_t begin = clock();
   quickSort(array, 0, ARRAY_LENGHT-1); 
   while(minDiff != 0 && i < ARRAY_LENGHT){
      if (minDiff > abs(array[i] - array[i+1])) {
         minDiff = abs(array[i]-array[i+1]);
         dif1 = array[i];
         dif2 = array[i+1];
      }
      i++;
   }
   clock_t end = clock();
   double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("Technique: Quick Sort (Optimized)\nEn Yakın Değer: %d\nSayı 1: %d\nSayı 2: %d\nÇalışma süresi: %f\n",minDiff,dif1,dif2,time_spent);
}

void printArray(int array[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", array[i]); 
    printf("\n"); 
} 

int main() {
   srand(time(0)); 
   printf("Array Uzunluğu: %d\n",ARRAY_LENGHT);
   
   // printf() displays the string inside quotation
   int array[ARRAY_LENGHT];
   int i=0;
   // Array'i init eder. Random sayılarla
   for(i = 0; i < ARRAY_LENGHT; ++i) {
     array[i] = rand()%MAX_RANDOMIZE;
   }
   printArray(array, ARRAY_LENGHT);
   bruteForce(array);
   withQuicksort(array);
   bruteForceSecond(array);
   return 0;
}