    return (unsigned char)*a - (unsigned char)*b;
}

int binary_search_name(const char key[], int count) {
    int low = 0, high = count - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int result = strcmp(names[indices[mid]], key);
        strcmp_calls++;
        if (result == 0) return mid;
        if (result < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main(void) {
    int count;
    char buffer[256];
    printf("Enter number of residents (1-%d): ", MAX_NAMES);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_NAMES) {
        fprintf(stderr, "Invalid number of residents.\n");
        return 1;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }

    for (int i = 0; i < count; i++) {
        printf("Name %d: ", i + 1);
        if (!fgets(buffer, sizeof buffer, stdin)) return 1;
        buffer[strcspn(buffer, "\n")] = '\0';
        /* Copy safely into the fixed-width destination. */
        snprintf(names[i], sizeof names[i], "%s", buffer);
        indices[i] = i;
    }

    strcmp_calls = 0;
    qsort(indices, (size_t)count, sizeof indices[0], compare_indices);
    printf("\nSorted resident directory:\n");
    for (int i = 0; i < count; i++)
        printf("%s\n", names[indices[i]]);
    printf("strcmp calls used by qsort: %lld\n", strcmp_calls);

    printf("\nEnter a name to search: ");
    if (!fgets(buffer, sizeof buffer, stdin)) return 1;
    buffer[strcspn(buffer, "\n")] = '\0';
    strcmp_calls = 0;
    int pos = binary_search_name(buffer, count);
    if (pos >= 0) printf("Found at sorted position %d\n", pos + 1);
    else puts("Name not found");
    printf("Search comparisons: %lld\n", strcmp_calls);

    puts("\nDuplicate names:");
    int duplicates = 0;
    for (int i = 1; i < count; i++) {
        if (strcmp(names[indices[i - 1]], names[indices[i]]) == 0) {
            printf("%s\n", names[indices[i]]);
            duplicates = 1;
        }
    }
    if (!duplicates) puts("No duplicate names found.");
    return 0;
}
