#include <stdio.h> 
#include <stdlib.h> 

int main() {
   // printf() displays the string inside quotation
   int array[100000];

    // Array'i init eder. Random sayılarla
   for(int i = 0; i < 100000; ++i) {
     array[i] = rand()%1000;
  }

   return 0;
}