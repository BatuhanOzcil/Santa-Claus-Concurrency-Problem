#include <stdio.h>
#include <stdlib.h>
/* BATUHAN ÖZÇİL ID:125200023 */
/* Problem functions */
void swap(int *a, int *b);
void countOddEven(int arr[], int size);
int findLargest(int arr[], int size);

int main() {

    printf("===== EXERCISES =====\n");

    /* 1 ARRAY MEMORY ADDRESSES */
    int arr[5] = {10,20,30,40,50};

    printf("Array element addresses:\n");
    for(int i=0;i<5;i++){
        printf("arr[%d] address = %p\n", i, &arr[i]);
    }


    /* 2 FLOAT + POINTER */
    float number = 5.5;
    float *ptr = &number;

    printf("\nVariable address: %p\n",&number);
    printf("Pointer value: %p\n",ptr);


    /* 3 GET DOUBLE FROM USER */
    double d;

    printf("\nEnter a double value: ");
    scanf("%lf",&d);

    printf("You entered: %lf\n",d);


    /* 4 NULL POINTER */
    int *p = NULL;

    int x = 25;
    p = &x;

    printf("\nPointer now points to value: %d\n", *p);


    /* 5 MALLOC ARRAY */
    int *dynamicArray;

    dynamicArray = (int*) malloc(5 * sizeof(int));

    printf("\nDynamic array values:\n");

    for(int i=0;i<5;i++){
        dynamicArray[i] = i+1;
        printf("%d ",dynamicArray[i]);
    }

    free(dynamicArray);


    printf("\n\n===== PROBLEMS =====\n");


    /* 1 SUM OF 5 INTEGERS */
    int numbers[5];
    int sum=0;

    printf("Enter 5 integers:\n");

    for(int i=0;i<5;i++){
        scanf("%d",&numbers[i]);
        sum += numbers[i];
    }

    printf("Total sum = %d\n",sum);


    /* 2 POWER CALCULATION */
    int base,exp,result=1;

    printf("\nEnter base: ");
    scanf("%d",&base);

    printf("Enter exponent: ");
    scanf("%d",&exp);

    for(int i=0;i<exp;i++){
        result *= base;
    }

    printf("Result = %d\n",result);


    /* 3 SWAP USING POINTERS */
    int a=5,b=10;

    printf("\nBefore swap: a=%d b=%d\n",a,b);

    swap(&a,&b);

    printf("After swap: a=%d b=%d\n",a,b);


    /* 4 COUNT ODD EVEN */
    countOddEven(numbers,5);


    /* 5 FIND LARGEST NUMBER */
    int max = findLargest(numbers,5);

    printf("Largest number = %d\n",max);


    return 0;
}



/* SWAP FUNCTION */
void swap(int *a, int *b){

    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}


/* COUNT ODD EVEN */
void countOddEven(int arr[], int size){

    int odd=0,even=0;

    for(int i=0;i<size;i++){

        if(arr[i] % 2 == 0)
            even++;
        else
            odd++;
    }

    printf("\nEven numbers = %d\n",even);
    printf("Odd numbers = %d\n",odd);
}


/* FIND LARGEST */
int findLargest(int arr[], int size){

    int max = arr[0];

    for(int i=1;i<size;i++){

        if(arr[i] > max)
            max = arr[i];
    }

    return max;
}