#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CANDIDATES 12
#define MAX_VOTES 500000

typedef struct {
    int candidate_number;
    int votes;
} Result;

int compare_results(const void *x, const void *y) {
    const Result *a = (const Result *)x;
    const Result *b = (const Result *)y;
    if (a->votes != b->votes) return (b->votes > a->votes) - (b->votes < a->votes);
    return a->candidate_number - b->candidate_number;
}

int main(void) {
    int candidates, total_votes;
    int count[MAX_CANDIDATES + 1] = {0};
    int valid = 0, invalid = 0;
    double count_seconds;
    int *votes;

    printf("Enter number of candidates (1-%d): ", MAX_CANDIDATES);
    if (scanf("%d", &candidates) != 1 || candidates < 1 ||
        candidates > MAX_CANDIDATES) {
        fprintf(stderr, "Invalid candidate count.\n");
        return 1;
    }
    printf("Enter number of votes (0-%d): ", MAX_VOTES);
    if (scanf("%d", &total_votes) != 1 || total_votes < 0 ||
        total_votes > MAX_VOTES) {
        fprintf(stderr, "Invalid vote count.\n");
        return 1;
    }

    votes = malloc((size_t)(total_votes > 0 ? total_votes : 1) * sizeof *votes);
    if (!votes) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    puts("Enter each vote as a candidate number:");
    for (int i = 0; i < total_votes; i++) {
        if (scanf("%d", &votes[i]) != 1) {
            fprintf(stderr, "Invalid input while reading votes.\n");
            free(votes);
            return 1;
        }
    }

    /* Time the single-pass counting/validation stage, excluding keyboard input. */
    clock_t start = clock();
    for (int i = 0; i < total_votes; i++) {
        if (votes[i] >= 1 && votes[i] <= candidates) {
            count[votes[i]]++;
            valid++;
        } else {
            invalid++;
        }
    }
    count_seconds = (double)(clock() - start) / CLOCKS_PER_SEC;

    Result results[MAX_CANDIDATES];
    for (int i = 0; i < candidates; i++) {
        results[i].candidate_number = i + 1;
        results[i].votes = count[i + 1];
    }
    qsort(results, (size_t)candidates, sizeof results[0], compare_results);

    printf("\nValid votes: %d\nInvalid votes: %d\n", valid, invalid);
    printf("Counting/validation time: %.6f seconds for %d votes\n", count_seconds, total_votes);
    puts("\nCandidate results (descending vote count):");
    for (int i = 0; i < candidates; i++)
        printf("Candidate %d: %d votes\n",
               results[i].candidate_number, results[i].votes);

    if (results[0].votes == 0) {
        puts("No valid votes were recorded; there is no winner.");
    } else {
        int tied = 0;
        for (int i = 1; i < candidates; i++) {
            if (results[i].votes == results[0].votes) tied = 1;
            else break;
        }
        if (tied) {
            printf("Tie for first place with %d votes: ", results[0].votes);
            for (int i = 0; i < candidates; i++) {
                if (results[i].votes == results[0].votes)
                    printf("Candidate %d ", results[i].candidate_number);
                else break;
            }
            putchar('\n');
        } else {
            printf("Winner: Candidate %d with %d votes\n",
                   results[0].candidate_number, results[0].votes);
        }
    }

    free(votes);
    return 0;
}
