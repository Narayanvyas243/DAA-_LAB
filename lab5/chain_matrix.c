#include <stdio.h>
#include <stdlib.h>
#define INF 99999999

int matrixChainOrder(int p[], int n, int s[][n]) {
    int m[n][n];

    // Initialize the diagonal elements
    for (int i = 0; i < n; i++) {
        m[i][i] = 0;
    }

    // Loop for chain lengths from 2 to n
    for (int chainLength = 2; chainLength < n; chainLength++) {
        for (int i = 0; i < n - chainLength + 1; i++) {
            int j = i + chainLength - 1;
            m[i][j] = INF;

            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    return m[0][n - 1];
}

void printOptimalParenthesization(int s[][100], int i, int j) {
    if (i == j) {
        printf("A%d", i + 1);
    } else {
        printf("(");
        printOptimalParenthesization(s, i, s[i][j]);
        printOptimalParenthesization(s, s[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    // Example matrix dimensions: A1(1x2), A2(2x3), A3(3x4), A4(4x3)
    int arr[] = {1, 2, 3, 4, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    int s[n][n];

    int minMultiplications = matrixChainOrder(arr, n, s);
    printf("Minimum number of multiplications: %d\n", minMultiplications);

    printf("Optimal Parenthesization: ");
    printOptimalParenthesization(s, 0, n - 2);
    printf("\n");

    return 0;
}