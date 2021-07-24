#include<stdio.h>

bool linear_search(int x, int *arr, int n)
{
    for (int i = 1; i<n; ++i){
        if(arr[i] == x) return true;
    }

    return false;
}

int main()
{
    int x = 14;
    int n = 6;
    int arr[] = {21, 23, 15, 14, 39, 25};

    printf("given array: ");
    for(int i = 0; i<n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("searching for: %d\n", x);

    bool found = linear_search(x, arr, n);

    if(found)
        printf("%d is in the given array.\n", x);
    else
        printf("%d is not in the given array.\n", x);


    return 0;
}
