#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ------------ Problem 4A: Insertion Sort with Pointers ------------ */
void insertionSort(int *arr, int n) {
    int *i, *j, key;
    for (i = arr + 1; i < arr + n; i++) {
        key = *i;
        j = i - 1;
        while (j >= arr && *j > key) {
            *(j + 1) = *j;
            j--;
        }
        *(j + 1) = key;
    }
}

/* ------------ Problem 4B: Custom strtok() Implementation ------------ */
char *my_strtok(char *str, const char *delim) {
    static char *saved;
    if (str) saved = str;
    if (!saved) return NULL;

    saved += strspn(saved, delim);
    if (*saved == '\0') return NULL;

    char *token = saved;
    saved = strpbrk(saved, delim);
    if (saved) {
        *saved = '\0';
        saved++;
    }
    return token;
}

/* ------------ Problem 4C: Shell Sort Algorithm ------------ */
void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
                arr[j] = arr[j-gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    // Problem 4A Test
    int arr[] = {9, 5, 1, 4, 3};
    int n = 5;
    insertionSort(arr, n);
    printf("Sorted with Insertion Sort: ");
    for (int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");

    // Problem 4B Test
    char str[] = "C,Java;Python|Go";
    char *token = my_strtok(str, ",;|");
    printf("Tokens: ");
    while (token) {
        printf("%s ", token);
        token = my_strtok(NULL, ",;|");
    }
    printf("\n");

    // Problem 4C Test
    int arr2[] = {12, 34, 54, 2, 3};
    int m = 5;
    shellSort(arr2, m);
    printf("Sorted with Shell Sort: ");
    for (int i=0; i<m; i++) printf("%d ", arr2[i]);
    printf("\n");

    return 0;
}
