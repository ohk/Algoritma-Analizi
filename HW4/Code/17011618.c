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
 * Renkleri yazdırır.
 */ 
void printColors(){
    printf("1 -> MOR\n2 -> MAVI\n3 -> SIYAH\n4 -> YESIL\n5 -> KIRMIZI\n6 -> SARI\n7 -> KAHVERENGI\n8 -> LACIVERT\n");
}
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
int solveTheColorMatrix(int colorMatrix[10][10], int size, int step,int debug){
    int innerShiftCount = 0,returnValue, i = 0;

    if(step >= size)
        return 0;
    
    while(i < size + 1){
        if (arrayCheck(colorMatrix,size,step) != 0) { 
           arrayShifter(colorMatrix,size,step);
        } else {
            if(debug == 0){
                printf("Adım: %d, Üst satırlara göre düzgün. Array Son durum\n",step);
                printArray(colorMatrix,size);
            }
            if(solveTheColorMatrix(colorMatrix, size, step +1,debug) == 0){
                return 0;
            } else {
                if(debug == 0)
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
    int colorMatrix[10][10], size=-9999 ,value,i,t;
    int debug = 0;
    while(size<3 || size>9){
        if(size != -9999){
            printf("Hatalı giriş yaptınız. Girilen değer 2 den büyük 9 dan küçük olmalıdır.\n");
        } 
        printf("Lütfen matris boyutunu veriniz?(N)\n>");
        scanf ("%d",&size);
    }
    printf("Lütfen loglama sistemini seçiniz?\n0. Her satırda\n1. Sadece sonda\n>");
    scanf("%d",&debug);
    printf("Lütfen elemanları girerken aşağıdaki renk kodlarına göre giriniz\n");
    printColors();
    for ( i = 0; i < size; i++)
    {
        for ( t = 0; t < size; t++)
        {
            printf("colorMatrix[%d][%d] elemanını giriniz: ",i,t);
            scanf("%d",&colorMatrix[i][t]);
        }
        
    }
    
    

    printf("Başlangıç Array'i\n");
    printArray(colorMatrix,size);
    value = solveTheColorMatrix(colorMatrix, size, 0,debug);
    if(value == -1){
        printf("Sonuç Bulunamadı!\n");
    } else {
        printf("Sonuc bulundu. Arrayin son durumu\n");
        printArray(colorMatrix,size);
    }
    return 0;
}
