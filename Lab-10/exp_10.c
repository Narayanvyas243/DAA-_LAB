#include <stdio.h>
#include <string.h>

void naiveSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++)
            if (text[i + j] != pattern[j])
                break;
        if (j == m)
            printf("Pattern found at index %d\n", i);
    }
}

int rabinKarpSearch(char *text, char *pattern, int q) {
    int d = 256;
    int m = strlen(pattern);
    int n = strlen(text);
    int h = 1;
    int p = 0;
    int t = 0;

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            int j;
            for (j = 0; j < m; j++)
                if (text[i + j] != pattern[j])
                    break;
            if (j == m)
                printf("Pattern found at index %d\n", i);
        }
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
    return 0;
}

void KMPSearch(char *pattern, char *text) {
    int m = strlen(pattern);
    int n = strlen(text);
    int lps[m];
    int j = 0;

    computeLPSArray(pattern, m, lps);

    int i = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}

void computeLPSArray(char *pattern, int m, int *lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";
    int q = 101;

    printf("Naive Search:\n");
    naiveSearch(text, pattern);

    printf("Rabin-Karp Search:\n");
    rabinKarpSearch(text, pattern, q);

    printf("KMP Search:\n");
    KMPSearch(pattern, text);

    return 0;
}
