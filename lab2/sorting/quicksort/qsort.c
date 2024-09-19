#include <stdio.h>

int partition(int arr[], int low, int high)
{
    int pivot = low;
    int i = low + 1;
    int j = high;
    do
    {
        while (arr[i] < arr[pivot])
        {
            i++;
        }
        while (arr[j] > arr[pivot])
        {
            j--;
        }
        if (i < j)
        {
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    } while (i < j);
    int temp = arr[pivot];
    arr[pivot] = arr[j];
    arr[j] = temp;
    return j;
}

void quicksort(int arr[], int low, int high)
{
    int partitionindex;
    if (low < high)
    {
        partitionindex = partition(arr, low, high);
        quicksort(arr, low, partitionindex - 1);
        quicksort(arr, partitionindex + 1, high);
    }
}

void printarray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
            printf("%d", arr[i]);
        else
            printf("%d, ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {5, 4, 8, 9, 3, 54, 89, 4, 5, 69};
    int n = 10;
    printarray(arr, n);
    quicksort(arr, 0, n - 1);
    printarray(arr, n);
    return 0;
}
