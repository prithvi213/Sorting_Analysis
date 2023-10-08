#include "shell.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    // Creates variables which keep track of the gap array size
    // Creates a gaps array keeping track of future gap sizes
    uint32_t gap_size = 0, gap_array_size = (uint32_t)(log(3.0 + 2.0 * n) / log(3.0));
    uint32_t *gaps_array = (uint32_t *) malloc(sizeof(uint32_t) * gap_array_size);
    uint32_t temp_value = 0, index = 0;

    // Initializes the gap array with the right elements
    for (uint32_t i = gap_array_size; i > 0; i--) {
        temp_value = ((uint32_t) pow(3.0, (1.0) * i)) / 2;
        gaps_array[index] = temp_value;
        index++;
    }

    // Performs the shell sort
    for (uint32_t k = 0; k < gap_array_size; k++) {
        gap_size = gaps_array[k];

        /* To perform shell sort, we compare two elements whose distance
	   is measured by the gap size*/
        for (uint32_t i = gap_size; i < n; i++) {
            uint32_t j = i, temp = move(stats, A[i]);

            // If temp < A[j - gap_size] -> set A[j] to A[j - gap_size]
            // Subtract gap_size from j
            while (j >= gap_size && cmp(stats, temp, A[j - gap_size]) == -1) {
                A[j] = move(stats, A[j - gap_size]);
                j -= gap_size;
            }

            // Set A[j] to temp
            A[j] = move(stats, temp);
        }

        gap_size--;
    }

    // Free the memory allocated in the gaps array
    free(gaps_array);
}
