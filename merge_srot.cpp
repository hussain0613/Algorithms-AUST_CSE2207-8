#include<stdio.h>
#include<stdlib.h>

void merge(int *arr, int start, int mid, int end)
{
    int n1 = mid - start, n2 = end - mid;

    int left[n1], right[n2];

    int i, j, k;

    for(i = 0, k = start; i < n1; ++i, ++k) left[i] = arr[k];
    for(j = 0, k = mid; j < n2; ++j, ++k) right[j] = arr[k];

    i = 0; j = 0; k = start;

    while (i < n1 && j < n2){
        if( left[i] > right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];
}

void merge_sort(int *arr, int start, int end)
{
    if (start + 1 >= end){
        return;
    }

    int mid = (start + end) / 2;

    merge_sort(arr, start, mid);
    merge_sort(arr, mid, end);

    merge(arr, start, mid, end);
}

int main()
{
    srand(60);

    int n = rand()%100;
    int arr[n];
    for(int i =0; i<n; ++i) arr[i] = rand()%1500 - 500;


    printf("length: %d\n", n);
    printf("given array, before sort: ");
    for(int i = 0; i<n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    merge_sort(arr, 0, n);

    printf("given array, after sort: ");
    for(int i = 0; i<n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

