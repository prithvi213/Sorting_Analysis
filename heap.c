#include "heap.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Used pseudocode from assignment 3 pdf
// Inspired from Professor Long
uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first, right = left + 1;

    if (right <= last && cmp(stats, A[right - 1], A[left - 1]) == 1) {
        return right;
    }

    return left;
}

// Used pseudocode from assignment 3 pdf
// Inspired from Professor Long
void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first, great = max_child(stats, A, mother, last);

    while (mother <= (last / 2) && !found) {

        // if A[mother - 1] < A[great - 1] -> swap them and set mother = great
        // Then, set great to the max child
        if (cmp(stats, A[mother - 1], A[great - 1]) == -1) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}

// Used pseudocode from assignment 3 pdf
// Inspired from Professor Long
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = (last / 2); father > first - 1; father--) {
        fix_heap(stats, A, father, last);
    }
}

// Used pseudocode from assignment 3 pdf
// Inspired from Professor Long
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1, last = n;
    build_heap(stats, A, first, last);

    for (uint32_t i = last; i > first; i--) {
        // Swap A[first - 1] and A[i - 1]
        // Then call fix_heap
        swap(stats, &A[first - 1], &A[i - 1]);
        fix_heap(stats, A, first, i - 1);
    }
}
