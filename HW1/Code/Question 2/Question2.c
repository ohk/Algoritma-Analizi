#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

void vonNeumann(int **array,int x,int y,int recursiveCount){
    array[x-1][y] = 1;
    array[x][y-1] = 1;
    array[x+1][y] = 1;
    array[x][y+1] = 1;
    if(recursiveCount != 0){
        vonNeumann(array,x-1,y,recursiveCount-1);
        vonNeumann(array,x+1,y,recursiveCount-1);
        vonNeumann(array,x,y-1,recursiveCount-1);
        vonNeumann(array,x,y + 1,recursiveCount-1);
    }
    return 0;
}

int main(void) {

	int N,i,j,x0,y0;
	printf("N Value: ");
	scanf("%d", &N);
	printf("\n");
	int totalBoyut = 2*N*(N+1)+1; 

	int **array = (int **)malloc(totalBoyut * sizeof(int*));
	for(i = 0; i < totalBoyut; i++) array[i] = (int *)malloc(totalBoyut * sizeof(int));


    for (i = 0; i <  totalBoyut; i++){
		for (j = 0; j < totalBoyut; j++){
		  array[i][j] = 0;
		}
	} 
      
	
	x0 = floor(totalBoyut/2);
	y0 = floor(totalBoyut/2);

	array[x0][y0] = 1;
	
    if(N>0){
		vonNeumann(array,x0,y0,N-1);
	}
	    

	printf("\nVon Neumann’s Neighborhood: \n");
    for (i = 0; i <  totalBoyut; i++){
		printf("\n");
		for (j = 0; j < totalBoyut; j++) {
			printf("%d ", array[i][j]);
		}			
	} 	
}