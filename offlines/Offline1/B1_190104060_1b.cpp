#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int *arr, int start, int end)
{
    if (start + 1 >= end){
        return;
    }

    int pivot_index = rand()%(end-start) + start;


    int pivot = arr[pivot_index];
    int i = start, j = end - 1;
    while (i < j){
        if(arr[i] > pivot && arr[j] < pivot){
            swap(arr+i, arr+j);
        }
        if (arr[i] <= pivot)
            ++i;
        if ( arr[j] >= pivot)
            --j;
    }
    if (pivot_index < i){
        while (pivot_index < i){
            arr[pivot_index] = arr[pivot_index+1];
            ++pivot_index;
        }

        if(arr[i] < pivot){
            arr[pivot_index] = pivot;
        }
        else{
            arr[--pivot_index] = pivot;
        }
    }
    else if(i < pivot_index){
        while (i < pivot_index){
            arr[pivot_index] = arr[pivot_index - 1];
            --pivot_index;
        }

        if(arr[i] < pivot){
            arr[++pivot_index] = pivot;
        }
        else{
            arr[pivot_index] = pivot;
        }
    }

    quick_sort(arr, start, pivot_index);
    quick_sort(arr, pivot_index+1, end);
}

int main()
{
    srand(60);
    int n = 6;
    int arr[] = {21, 23, 15, 14, 39, 25};


    printf("length: %d\n", n);
    printf("given array, before sort: ");
    for(int i = 0; i<n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    quick_sort(arr, 0, n);

    printf("given array, after sort: ");
    for(int i = 0; i<n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
