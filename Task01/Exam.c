    }
    if (order == 1) {
        int changes = n < 20 ? n : 20;
        for (int i = 0; i < changes; i++) {
            int p = rand() % n, q = rand() % n;
            int t = a[p]; a[p] = a[q]; a[q] = t;
        }
    }
}

int main(void) {
    const int sizes[] = {100, 1000, 10000};
    const char *orders[] = {"sorted", "nearly-sorted", "reverse", "random"};
    srand(42);

    for (int si = 0; si < 3; si++) {
        int n = sizes[si];
        printf("\n===== n = %d =====\n", n);
        puts("Input order       Algorithm       Comparisons       Swaps/shifts");
        for (int order = 0; order < 4; order++) {
            for (int alg = 0; alg < 3; alg++) {
                int *a = malloc((size_t)n * sizeof *a);
                if (!a) return 1;
                fill_data(a, n, order);
                Stats st;
                if (alg == 0) bubble_sort(a, n, &st);
                else if (alg == 1) selection_sort(a, n, &st);
                else insertion_sort(a, n, &st);
                printf("%-17s %-15s %-17lld %lld\n", orders[order],
                       alg == 0 ? "Bubble" : alg == 1 ? "Selection" : "Insertion",
                       st.comparisons, st.swaps_or_shifts);
                free(a);
            }
        }
    }
    return 0;
}
