#include <stdio.h>
#include <stdlib.h>

static long long steps;

int linear_search(const int a[], int n, int key) {
    steps = 0;
    for (int i = 0; i < n; i++) {
        steps++;
        if (a[i] == key) return i;
    }
    return -1;
}

int binary_search(const int a[], int n, int key) {
    int low = 0, high = n - 1;
    steps = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2; /* avoids low + high overflow */
        steps++;
        if (a[mid] == key) return mid;
        if (a[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int int_compare(const void *x, const void *y) {
    int a = *(const int *)x, b = *(const int *)y;
    return (a > b) - (a < b);
}

int main(void) {
    int sorted[] = {1021, 1048, 1103, 1190, 1222, 1305, 1377, 1402, 1460, 1533};
    int n = (int)(sizeof sorted / sizeof sorted[0]);
    int keys[] = {1021, 1305, 1533, 1400};

    puts("Binary search on the sorted catalogue:");
    for (int k = 0; k < 4; k++) {
        int pos = binary_search(sorted, n, keys[k]);
        printf("Book %d -> index %d, comparisons = %lld\n", keys[k], pos, steps);
    }

    /* Compare linear and binary search on generated catalogue sizes. */
    const int sizes[] = {1000, 10000, 100000};
    puts("\nScalability experiment (successful key at end, then missing key):");
    puts("n\tlinear-found\tbinary-found\tlinear-missing\tbinary-missing");
    for (int s = 0; s < 3; s++) {
        int count = sizes[s];
        int *a = malloc((size_t)count * sizeof *a);
        if (!a) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
        for (int i = 0; i < count; i++) a[i] = 100000 + i * 3;

        int key_found = a[count - 1];
        int key_missing = -1;
        (void)linear_search(a, count, key_found);
        long long lf = steps;
        (void)binary_search(a, count, key_found);
        long long bf = steps;
        (void)linear_search(a, count, key_missing);
        long long lm = steps;
        (void)binary_search(a, count, key_missing);
        long long bm = steps;
        printf("%d\t%lld\t\t%lld\t\t%lld\t\t%lld\n", count, lf, bf, lm, bm);
        free(a);
    }
    return 0;
}
