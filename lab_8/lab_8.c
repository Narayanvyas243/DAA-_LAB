#include <stdio.h>

void findSubset(int arr[], int n, int sum, int subset[], int subsetSize, int index) {
    if (sum == 0) {
        for (int i = 0; i < subsetSize; i++) printf("%d ", subset[i]);
        printf("\n");
        return;
    }
    if (sum < 0 || index == n) return;

    subset[subsetSize] = arr[index];
    findSubset(arr, n, sum - arr[index], subset, subsetSize + 1, index + 1);
    findSubset(arr, n, sum, subset, subsetSize, index + 1);
}

int main() {
    int arr[] = {3, 1, 2, 5, 7};
    int target = 7;
    int n = sizeof(arr) / sizeof(arr[0]);
    int subset[n];
    findSubset(arr, n, target, subset, 0, 0);
    return 0;
}
