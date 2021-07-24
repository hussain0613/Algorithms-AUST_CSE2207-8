#include<stdio.h>
#include<stdlib.h>

void insertion_sort(int *arr, int n)
{
    for (int i = 1; i<n; ++i){
        int key = arr[i];
        int j = i-1;
        while (key < arr[j] &&  j >=0){
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = key;
    }
}

int main()
{
    srand(60);

    int n = rand()%100;
    int arr[n];
    for(int i =0; i<n; ++i) arr[i] = rand()%1500 - 500;

    printf("given array, before sort: ");
    for(int i = 0; i<n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    insertion_sort(arr, n);

    printf("given array, after sort: ");
    for(int i = 0; i<n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");


    return 0;
}
