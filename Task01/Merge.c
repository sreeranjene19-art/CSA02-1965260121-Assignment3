#include <stdio.h>
#include <stdlib.h>

long long merge_comparisons;

int merge_descending(const int a[], int na, const int b[], int nb, int out[]) {
    int i = 0, j = 0, k = 0;
    merge_comparisons = 0;

    while (i < na && j < nb) {
        merge_comparisons++;
        if (a[i] >= b[j]) out[k++] = a[i++];
        else out[k++] = b[j++];
    }
    while (i < na) out[k++] = a[i++];
    while (j < nb) out[k++] = b[j++];
    return k;
}

int int_compare(const void *x, const void *y) {
    int a = *(const int *)x, b = *(const int *)y;
    return (b > a) - (b < a); /* descending */
}

int main(void) {
    int campusA[] = {98, 91, 85, 72};
    int campusB[] = {95, 91, 80};
    int merged[7];
    int n = merge_descending(campusA, 4, campusB, 3, merged);

    printf("Merged merit list: ");
    for (int i = 0; i < n; i++) printf("%d ", merged[i]);
    printf("\nMerge comparisons: %lld\n", merge_comparisons);

    /* Empty-list test */
    int onlyB[] = {88, 77, 66}, empty_result[3];
    n = merge_descending(NULL, 0, onlyB, 3, empty_result);
    printf("One empty list: ");
    for (int i = 0; i < n; i++) printf("%d ", empty_result[i]);
    putchar('\n');

    /* Compare merge with joining and qsort for equal-sized lists. */
    const int sizes[] = {1000, 10000};
    for (int s = 0; s < 2; s++) {
        int m = sizes[s], total = 2 * m;
        int *a = malloc((size_t)m * sizeof *a);
        int *b = malloc((size_t)m * sizeof *b);
        int *out = malloc((size_t)total * sizeof *out);
        int *joined = malloc((size_t)total * sizeof *joined);
        if (!a || !b || !out || !joined) return 1;
        for (int i = 0; i < m; i++) {
            a[i] = 100000 - 2 * i;
            b[i] = 99999 - 2 * i;
        }
        merge_descending(a, m, b, m, out);
        long long mc = merge_comparisons;
        for (int i = 0; i < m; i++) { joined[i] = a[i]; joined[m + i] = b[i]; }
        qsort(joined, (size_t)total, sizeof *joined, int_compare);
        printf("m=n=%d: merge comparisons=%lld; qsort input elements=%d\n", m, mc, total);
        free(a); free(b); free(out); free(joined);
    }
    return 0;
}
