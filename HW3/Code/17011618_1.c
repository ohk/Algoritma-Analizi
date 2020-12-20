#include <stdlib.h>
#include<stdio.h>

float checkTheWin(float winRate, int winCount){
    float matrix[winCount +1][winCount +1];
    int i,j;
    for (i = 0; i <= winCount; i++) {
        matrix[i][0] = 0.0;
        matrix[0][i] = 1.0;
    }

    for ( i = 1; i <= winCount; i++)
        for ( j = 1; j <= winCount; j++)
            matrix[i][j] = (float)(winRate * (float)(matrix[i - 1][j]) + (1 - winRate) * (float)(matrix[i][j - 1]));
            
    return (float)matrix[winCount][winCount];
}
int main(){
    int winCount = 4, choose = 0;
    float winRate = 0.6;
    printf("Do you wanna use default values\nWin rate: 0.6\nWin Count: 4\n--------------------------\n>1 - Yes\n>2 - NO\n>");
    scanf("%d",&choose);
    if(choose == 2){
        printf("Give the Total Win Count:\n>");
        scanf("%d",&winCount);
        printf("Give the Win Rate:\n>");
        scanf("%f",&winRate);
    }
    
    printf("Result is %f\n", checkTheWin(winRate,winCount));
}