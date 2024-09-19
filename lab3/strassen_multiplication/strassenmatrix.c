#include <stdio.h>
#include <stdlib.h>

#define MAX 2  // Change this to the desired matrix size

void add(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mid = size / 2;
    
    // Submatrices
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX], M4[MAX][MAX], M5[MAX][MAX], M6[MAX][MAX], M7[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int temp1[MAX][MAX], temp2[MAX][MAX];

    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, temp1, mid);
    add(B11, B22, temp2, mid);
    strassen(temp1, temp2, M1, mid);

    // M2 = (A21 + A22) * B11
    add(A21, A22, temp1, mid);
    strassen(temp1, B11, M2, mid);

    // M3 = A11 * (B12 - B22)
    subtract(B12, B22, temp1, mid);
    strassen(A11, temp1, M3, mid);

    // M4 = A22 * (B21 - B11)
    subtract(B21, B11, temp1, mid);
    strassen(A22, temp1, M4, mid);

    // M5 = (A11 + A12) * B22
    add(A11, A12, temp1, mid);
    strassen(temp1, B22, M5, mid);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract(A21, A11, temp1, mid);
    add(B11, B12, temp2, mid);
    strassen(temp1, temp2, M6, mid);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract(A12, A22, temp1, mid);
    add(B21, B22, temp2, mid);
    strassen(temp1, temp2, M7, mid);

    // C11 = M1 + M4 - M5 + M7
    add(M1, M4, temp1, mid);
    subtract(temp1, M5, temp2, mid);
    add(temp2, M7, C11, mid);

    // C12 = M3 + M5
    add(M3, M5, C12, mid);

    // C21 = M2 + M4
    add(M2, M4, C21, mid);

    // C22 = M1 - M2 + M3 + M6
    subtract(M1, M2, temp1, mid);
    add(temp1, M3, temp2, mid);
    add(temp2, M6, C22, mid);

    // Combine submatrices into the result matrix C
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }
}

void printMatrix(int matrix[MAX][MAX], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[MAX][MAX] = { {1, 2}, {3, 4} };
    int B[MAX][MAX] = { {5, 6}, {7, 8} };
    int C[MAX][MAX];

    strassen(A, B, C, MAX);

    printf("Resultant Matrix:\n");
    printMatrix(C, MAX);

    return 0;
}
