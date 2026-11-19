    printf("\nWettest record: District %d, Month %d = %.1f mm\n",
           max_district + 1, max_month + 1, maximum);
    printf("State annual average per district: %.2f mm\n", state_total / DISTRICTS);
    puts("Deficient districts:");
    deficient_districts(rain, totals, state_total / DISTRICTS);

    /* Hand-checkable 3 x 4 example. */
    {
        int small[3][4] = {{10, 20, 30, 40}, {5, 15, 25, 35}, {2, 4, 6, 8}};
        puts("\nSmall 3x4 row totals: 100, 80, 20");
        for (int i = 0; i < 3; i++) {
            int sum = 0;
            for (int j = 0; j < 4; j++) sum += small[i][j];
            printf("Row %d total = %d\n", i + 1, sum);
        }
    }

    /* Cache traversal experiment: row-major versus column-major. */
    {
        const int N = 2000;
        static int matrix[2000][2000];
        volatile long long checksum = 0;
        clock_t start = clock();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) checksum += matrix[i][j];
        double row_seconds = (double)(clock() - start) / CLOCKS_PER_SEC;

        start = clock();
        for (int j = 0; j < N; j++)
            for (int i = 0; i < N; i++) checksum += matrix[i][j];
        double col_seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
        printf("\nTraversal timing: row-wise %.4f s, column-wise %.4f s (checksum=%lld)\n",
               row_seconds, col_seconds, checksum);
    }
    return 0;
}
