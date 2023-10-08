#include "insert.h"

#include <stdio.h>
#include <stdlib.h>

// Used pseudocode for Insertion sort on assignment 3
// Inspired by Professor Long
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 1; i < n; i++) {
        uint32_t j = i, temp = move(stats, A[i]);

        // If j > 0 and temp < A[j - 1] -> set A[j] to A[j - 1]
        while (j > 0 && cmp(stats, temp, A[j - 1]) == -1) {
            A[j] = move(stats, A[j - 1]);
            j -= 1;
        }

        // Set A[j] to temp
        A[j] = move(stats, temp);
    }
}
