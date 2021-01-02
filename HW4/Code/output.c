#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include <ctype.h>

#define MOR 1;
#define MAVI 2;
#define SIYAH 3;
#define YESIL 4;
#define KIRMIZI 5;
#define SARI 6;
#define KAHVERENGI 7;
#define LACIVERT 8;

/**
 * Renk matrisini yazdırır.
 * @param int renk matrisi
 * @param int matrisin boyutu
 */ 
void printArray(int colorMatrix[10][10],int size){
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            switch (colorMatrix[i][j]){
                case 1:
                    printf("MOR       \t");
                    break;
                case 2:
                    printf("MAVI      \t");
                    break;
                case 3:
                    printf("SIYAH     \t");
                    break;
                case 4:
                    printf("YESIL     \t");
                    break;
                case 5:
                    printf("KIRMIZI   \t");
                    break;
                case 6:
                    printf("SARI      \t");
                    break;
                case 7:
                    printf("KAHVERENGI\t");
                    break;
                case 8:
                    printf("LACIVERT  \t");
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Renk matrisinin verilen satır numarasına göre kontrol eder.
 * @param int renk matrisi
 * @param int matrisin boyutu
 * @param int kaçıncı satıra kadar kontrol edileceği
 * @return 0 -> array düzgün veya -1 -> array hatalı
 */ 
int arrayCheck(int colorMatrix[10][10], int size, int step){
    int breakConfirm = 0,i,j,t;
    i = 0;
    /** 
     * Dıştaki while sütünları değiştirir.
     */ 
    while (i<size && breakConfirm == 0)
    {
        /** 
         * içteki while satırları değiştirir.
         */ 
        j=step-1;
        while(j>=0 && breakConfirm == 0){
            if(colorMatrix[step][i] == colorMatrix[j][i]){
                breakConfirm = -1;
            } else {
                j = j - 1;
            }
        }
        i++;
    }
    return breakConfirm;
}

/**
 * Renk matrisini yazdırır.
 * @param int renk matrisi
 * @param int matrisin boyutu
 * @param int kaçıncı satır sağa kaydırılacak
 */ 
void arrayShifter(int colorMatrix[10][10], int size, int step){
    int tmp = 0,i;
    tmp = colorMatrix[step][size-1];
    for ( i = size-1; i > 0; i--)
    {
        colorMatrix[step][i] = colorMatrix[step][i -1];
    }
    colorMatrix[step][0] = tmp;
}

/**
 * Renk matrisini yazdırır.
 * @param int renk matrisi
 * @param int matrisin boyutu
 * @param int kaçıncı satırda kontrol edileceği
 * @return 0 -> her şey düzgün çalıştı, -1 -> uygun sonuç yok.
 */ 
int solveTheColorMatrix(int colorMatrix[10][10], int size, int step){
    int innerShiftCount = 0,returnValue, i = 0;

    if(step >= size)
        return 0;
    
    while(i < size + 1){
        if (arrayCheck(colorMatrix,size,step) != 0) { 
           arrayShifter(colorMatrix,size,step);
        } else {
            printf("Adım: %d, Üst satırlara göre düzgün. Array Son durum\n",step);
            printArray(colorMatrix,size);
            if(solveTheColorMatrix(colorMatrix, size, step +1) == 0){
                return 0;
            } else {
                printf("Geriye dönüyorum.\n");
                arrayShifter(colorMatrix,size,step);
            }
        }
        i++;
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int colorMatrix[10][10], value;
    printf("N:3 ÖRNEK 1\n");
    colorMatrix[0][0] = MOR;
    colorMatrix[0][1] = YESIL;
    colorMatrix[0][2] = SIYAH;

    colorMatrix[1][0] = SIYAH;
    colorMatrix[1][1] = MOR;
    colorMatrix[1][2] = YESIL;

    colorMatrix[2][0] = YESIL;
    colorMatrix[2][1] = SIYAH;
    colorMatrix[2][2] = MOR;

    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,3);
    value = solveTheColorMatrix(colorMatrix, 3, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Sonuc bulundu. Arrayin son durumu\n");
        printArray(colorMatrix,3);
    }
    printf("N:3 ÖRNEK 2\n");
    colorMatrix[0][0] = KIRMIZI;
    colorMatrix[0][1] = MAVI;
    colorMatrix[0][2] = YESIL;

    colorMatrix[1][0] = YESIL;
    colorMatrix[1][1] = MAVI;
    colorMatrix[1][2] = KIRMIZI;

    colorMatrix[2][0] = KIRMIZI;
    colorMatrix[2][1] = YESIL;
    colorMatrix[2][2] = MAVI;

    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,3);
    value = solveTheColorMatrix(colorMatrix, 3, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Sonuc bulundu. Arrayin son durumu\n");
        printArray(colorMatrix,3);
    }
    
    
    printf("N:4 ÖRNEK 1\n");
    colorMatrix[0][0] = KIRMIZI;
    colorMatrix[0][1] = MAVI;
    colorMatrix[0][2] = YESIL;
    colorMatrix[0][3] = MOR;
    
    colorMatrix[1][0] = MAVI;
    colorMatrix[1][1] = YESIL;
    colorMatrix[1][2] = MOR;
    colorMatrix[1][3] = KIRMIZI;

    colorMatrix[2][0] = YESIL;
    colorMatrix[2][1] = MOR;
    colorMatrix[2][2] = KIRMIZI;
    colorMatrix[2][3] = MAVI;

    colorMatrix[3][0] = MOR;
    colorMatrix[3][1] = KIRMIZI;
    colorMatrix[3][2] = MAVI;
    colorMatrix[3][3] = YESIL;


    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,4);
    value = solveTheColorMatrix(colorMatrix, 4, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Sonuc bulundu. Arrayin son durumu\n");
        printArray(colorMatrix,4);
    }

    printf("N:4 ÖRNEK 2\n");
    colorMatrix[0][0] = KIRMIZI;
    colorMatrix[0][1] = KAHVERENGI;
    colorMatrix[0][2] = YESIL;
    colorMatrix[0][3] = MOR;
    
    colorMatrix[1][0] = KAHVERENGI;
    colorMatrix[1][1] = YESIL;
    colorMatrix[1][2] = MOR;
    colorMatrix[1][3] = KIRMIZI;

    colorMatrix[2][0] = YESIL;
    colorMatrix[2][1] = KAHVERENGI;
    colorMatrix[2][2] = KIRMIZI;
    colorMatrix[2][3] = MOR;

    colorMatrix[3][0] = MOR;
    colorMatrix[3][1] = KIRMIZI;
    colorMatrix[3][2] = KAHVERENGI;
    colorMatrix[3][3] = YESIL;


    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,4);
    value = solveTheColorMatrix(colorMatrix, 4, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Sonuc bulundu. Arrayin son durumu\n");
        printArray(colorMatrix,4);
    }

    printf("N:5 ÖRNEK 1\n");
    colorMatrix[0][0] = KIRMIZI;
    colorMatrix[0][1] = SARI;
    colorMatrix[0][2] = MOR;
    colorMatrix[0][3] = YESIL;
    colorMatrix[0][4] = LACIVERT;

    colorMatrix[1][0] = LACIVERT;
    colorMatrix[1][1] = KIRMIZI;
    colorMatrix[1][2] = SARI;
    colorMatrix[1][3] = MOR;
    colorMatrix[1][4] = YESIL;

    colorMatrix[2][0] = SARI;
    colorMatrix[2][1] = MOR;
    colorMatrix[2][2] = YESIL;
    colorMatrix[2][3] = LACIVERT;
    colorMatrix[2][4] = KIRMIZI;

    colorMatrix[3][0] = SARI;
    colorMatrix[3][1] = YESIL;
    colorMatrix[3][2] = LACIVERT;
    colorMatrix[3][3] = KIRMIZI;
    colorMatrix[3][4] = MOR;

    colorMatrix[4][0] = YESIL;
    colorMatrix[4][1] = MOR;
    colorMatrix[4][2] = SARI;
    colorMatrix[4][3] = KIRMIZI;
    colorMatrix[4][4] = LACIVERT;

    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,5);
    value = solveTheColorMatrix(colorMatrix, 5, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Sonuc bulundu. Arrayin son durumu\n");
        printArray(colorMatrix,5);
    }
    printf("N:5 ÖRNEK 2\n");
    colorMatrix[0][0] = KIRMIZI;
    colorMatrix[0][1] = SARI;
    colorMatrix[0][2] = MOR;
    colorMatrix[0][3] = YESIL;
    colorMatrix[0][4] = LACIVERT;

    colorMatrix[1][0] = LACIVERT;
    colorMatrix[1][1] = KIRMIZI;
    colorMatrix[1][2] = SARI;
    colorMatrix[1][3] = MOR;
    colorMatrix[1][4] = YESIL;

    colorMatrix[2][0] = SARI;
    colorMatrix[2][1] = MOR;
    colorMatrix[2][2] = YESIL;
    colorMatrix[2][3] = LACIVERT;
    colorMatrix[2][4] = KIRMIZI;

    colorMatrix[3][0] = MOR;
    colorMatrix[3][1] = YESIL;
    colorMatrix[3][2] = KIRMIZI;
    colorMatrix[3][3] = LACIVERT;
    colorMatrix[3][4] = SARI;

    colorMatrix[4][0] = YESIL;
    colorMatrix[4][1] = MOR;
    colorMatrix[4][2] = SARI;
    colorMatrix[4][3] = KIRMIZI;
    colorMatrix[4][4] = LACIVERT;

    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,5);
    value = solveTheColorMatrix(colorMatrix, 5, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Sonuc bulundu. Arrayin son durumu\n");
        printArray(colorMatrix,5);
    }
    printf("N:5 ÖRNEK 3\n");
    colorMatrix[0][0] = KIRMIZI;
    colorMatrix[0][1] = SARI;
    colorMatrix[0][2] = MOR;
    colorMatrix[0][3] = YESIL;
    colorMatrix[0][4] = LACIVERT;

    colorMatrix[1][0] = KIRMIZI;
    colorMatrix[1][1] = SARI;
    colorMatrix[1][2] = MOR;
    colorMatrix[1][3] = YESIL;
    colorMatrix[1][4] = LACIVERT;
    
    colorMatrix[2][0] = KIRMIZI;
    colorMatrix[2][1] = SARI;
    colorMatrix[2][2] = MOR;
    colorMatrix[2][3] = YESIL;
    colorMatrix[2][4] = LACIVERT;

    colorMatrix[3][0] = KIRMIZI;
    colorMatrix[3][1] = SARI;
    colorMatrix[3][2] = MOR;
    colorMatrix[3][3] = YESIL;
    colorMatrix[3][4] = LACIVERT;

    colorMatrix[4][0] = KIRMIZI;
    colorMatrix[4][1] = SARI;
    colorMatrix[4][2] = MOR;
    colorMatrix[4][3] = YESIL;
    colorMatrix[4][4] = LACIVERT;

    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,5);
    value = solveTheColorMatrix(colorMatrix, 5, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Arrayin son durumu\n");
        printArray(colorMatrix,5);
    }
    printf("N:6 ÖRNEK 1\n");
    colorMatrix[0][0] = MOR;
    colorMatrix[0][1] = MAVI;
    colorMatrix[0][2] = SIYAH;
    colorMatrix[0][3] = YESIL;
    colorMatrix[0][4] = KIRMIZI;
    colorMatrix[0][5] = SARI;

    colorMatrix[1][0] = SIYAH;
    colorMatrix[1][1] = YESIL;
    colorMatrix[1][2] = KIRMIZI;
    colorMatrix[1][3] = SARI;
    colorMatrix[1][4] = MOR;
    colorMatrix[1][5] = MAVI;

    colorMatrix[2][0] = MOR;
    colorMatrix[2][1] = MAVI;
    colorMatrix[2][2] = SIYAH;
    colorMatrix[2][3] = YESIL;
    colorMatrix[2][4] = KIRMIZI;
    colorMatrix[2][5] = SARI;
    
    colorMatrix[3][0] = SARI;
    colorMatrix[3][1] = MOR;
    colorMatrix[3][2] = MAVI;
    colorMatrix[3][3] = SIYAH;
    colorMatrix[3][4] = YESIL;
    colorMatrix[3][5] = KIRMIZI;
    
    colorMatrix[4][0] = SIYAH;
    colorMatrix[4][1] = YESIL;
    colorMatrix[4][2] = KIRMIZI;
    colorMatrix[4][3] = SARI;
    colorMatrix[4][4] = MOR;
    colorMatrix[4][5] = MAVI;
    
    colorMatrix[5][0] = YESIL;
    colorMatrix[5][1] = KIRMIZI;
    colorMatrix[5][2] = SARI;
    colorMatrix[5][3] = MOR;
    colorMatrix[5][4] = MAVI;
    colorMatrix[5][5] = SIYAH;

    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,5);
    value = solveTheColorMatrix(colorMatrix, 5, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Arrayin son durumu\n");
        printArray(colorMatrix,5);
    }
    printf("N:6 ÖRNEK 2\n");
    colorMatrix[0][0] = MOR;
    colorMatrix[0][1] = MAVI;
    colorMatrix[0][2] = SIYAH;
    colorMatrix[0][3] = YESIL;
    colorMatrix[0][4] = KIRMIZI;
    colorMatrix[0][5] = SARI;

    colorMatrix[1][0] = MOR;
    colorMatrix[1][1] = MAVI;
    colorMatrix[1][2] = SIYAH;
    colorMatrix[1][3] = YESIL;
    colorMatrix[1][4] = KIRMIZI;
    colorMatrix[1][5] = SARI;

    colorMatrix[2][0] = MOR;
    colorMatrix[2][1] = MAVI;
    colorMatrix[2][2] = SIYAH;
    colorMatrix[2][3] = YESIL;
    colorMatrix[2][4] = KIRMIZI;
    colorMatrix[2][5] = SARI;

    colorMatrix[3][0] = MOR;
    colorMatrix[3][1] = MAVI;
    colorMatrix[3][2] = SIYAH;
    colorMatrix[3][3] = YESIL;
    colorMatrix[3][4] = KIRMIZI;
    colorMatrix[3][5] = SARI;

    colorMatrix[4][0] = MOR;
    colorMatrix[4][1] = MAVI;
    colorMatrix[4][2] = SIYAH;
    colorMatrix[4][3] = YESIL;
    colorMatrix[4][4] = KIRMIZI;
    colorMatrix[4][5] = SARI;

    colorMatrix[5][0] = MOR;
    colorMatrix[5][1] = MAVI;
    colorMatrix[5][2] = SIYAH;
    colorMatrix[5][3] = YESIL;
    colorMatrix[5][4] = KIRMIZI;
    colorMatrix[5][5] = SARI;
    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,5);
    value = solveTheColorMatrix(colorMatrix, 5, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Arrayin son durumu\n");
        printArray(colorMatrix,5);
    }
    printf("N:6 ÖRNEK 3\n");
    colorMatrix[0][0] = MOR;
    colorMatrix[0][1] = MAVI;
    colorMatrix[0][2] = SIYAH;
    colorMatrix[0][3] = YESIL;
    colorMatrix[0][4] = KIRMIZI;
    colorMatrix[0][5] = SARI;

    colorMatrix[1][0] = MOR;
    colorMatrix[1][1] = MAVI;
    colorMatrix[1][2] = SIYAH;
    colorMatrix[1][3] = YESIL;
    colorMatrix[1][4] = KIRMIZI;
    colorMatrix[1][5] = SARI;

    colorMatrix[2][0] = MOR;
    colorMatrix[2][1] = MAVI;
    colorMatrix[2][2] = SIYAH;
    colorMatrix[2][3] = YESIL;
    colorMatrix[2][4] = KIRMIZI;
    colorMatrix[2][5] = SARI;

    colorMatrix[3][0] = MOR;
    colorMatrix[3][1] = MAVI;
    colorMatrix[3][2] = SIYAH;
    colorMatrix[3][3] = YESIL;
    colorMatrix[3][4] = KIRMIZI;
    colorMatrix[3][5] = SARI;

    colorMatrix[4][0] = MOR;
    colorMatrix[4][1] = MAVI;
    colorMatrix[4][2] = SIYAH;
    colorMatrix[4][3] = YESIL;
    colorMatrix[4][4] = KIRMIZI;
    colorMatrix[4][5] = SARI;

    colorMatrix[5][0] = SARI;
    colorMatrix[5][1] = MOR;
    colorMatrix[5][2] = MAVI;
    colorMatrix[5][3] = SIYAH;
    colorMatrix[5][4] = YESIL;
    colorMatrix[5][5] = KIRMIZI;
    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,5);
    value = solveTheColorMatrix(colorMatrix, 5, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Arrayin son durumu\n");
        printArray(colorMatrix,5);
    }

    printf("N:6 ÖRNEK 4\n");
    colorMatrix[0][0] = MOR;
    colorMatrix[0][1] = MAVI;
    colorMatrix[0][2] = SIYAH;
    colorMatrix[0][3] = LACIVERT;
    colorMatrix[0][4] = KIRMIZI;
    colorMatrix[0][5] = SARI;

    colorMatrix[1][0] = MOR;
    colorMatrix[1][1] = MAVI;
    colorMatrix[1][2] = SIYAH;
    colorMatrix[1][3] = LACIVERT;
    colorMatrix[1][4] = KIRMIZI;
    colorMatrix[1][5] = SARI;

    colorMatrix[2][0] = MOR;
    colorMatrix[2][1] = MAVI;
    colorMatrix[2][2] = SIYAH;
    colorMatrix[2][3] = LACIVERT;
    colorMatrix[2][4] = KIRMIZI;
    colorMatrix[2][5] = SARI;

    colorMatrix[3][0] = MOR;
    colorMatrix[3][1] = MAVI;
    colorMatrix[3][2] = SIYAH;
    colorMatrix[3][3] = LACIVERT;
    colorMatrix[3][4] = KIRMIZI;
    colorMatrix[3][5] = SARI;

    colorMatrix[4][0] = MOR;
    colorMatrix[4][1] = MAVI;
    colorMatrix[4][2] = SIYAH;
    colorMatrix[4][3] = LACIVERT;
    colorMatrix[4][4] = KIRMIZI;
    colorMatrix[4][5] = SARI;

    colorMatrix[5][0] = SARI;
    colorMatrix[5][1] = MOR;
    colorMatrix[5][2] = MAVI;
    colorMatrix[5][3] = SIYAH;
    colorMatrix[5][4] = LACIVERT;
    colorMatrix[5][5] = KIRMIZI;
    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,5);
    value = solveTheColorMatrix(colorMatrix, 5, 0);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Arrayin son durumu\n");
        printArray(colorMatrix,5);
    }
    return 0;
}
