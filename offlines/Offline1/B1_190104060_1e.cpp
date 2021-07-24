#include<stdio.h>

bool binary_search(int x, int *arr, int start, int end)
{
    if(start+1 == end){
        if (arr[start] == x)
            return true;
        else
            return false;
    }

    int mid = (start + end) / 2;
    if (arr[mid] == x)
        return true;
    else if (x < arr[mid])
        return binary_search(x, arr, start, mid);
    else
        return binary_search(x, arr, mid, end);
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

    bool found = binary_search(x, arr, 0, n);

    if(found)
        printf("%d is in the given array.\n", x);
    else
        printf("%d is not in the given array.\n", x);


    return 0;
}

