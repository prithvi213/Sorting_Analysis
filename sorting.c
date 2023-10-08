#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Set of command-line options
#define OPTIONS "haeisqn:p:r:"

// Enum is used to help us keep track of command-line preference
typedef enum { HEAP, INSERTION, SHELL, QUICK, DEFAULT } Sorts;

int main(int argc, char **argv) {
    int opt = 0;

    // Default random seed, size, and printed outputs
    uint32_t random_seed = 13371453, size = 100, prints = 100;

    // Using a Set to keep track of command-line options
    Set set = empty_set();
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;

    // If there aren't enough arguments entered -> displayed message
    if (argc == 1) {
        printf("Select at least one sort to perform.\n");
        set = insert_set(DEFAULT, set);
    }

    // Each of the command line options
    // Will insert enum item into the set based on the command-line argument
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            set = insert_set(HEAP, set);
            set = insert_set(SHELL, set);
            set = insert_set(INSERTION, set);
            set = insert_set(QUICK, set);
            break;
        case 'e': set = insert_set(HEAP, set); break;
        case 'i': set = insert_set(INSERTION, set); break;
        case 's': set = insert_set(SHELL, set); break;
        case 'q': set = insert_set(QUICK, set); break;
        case 'r': random_seed = atoi(optarg); break;
        case 'n': size = atoi(optarg); break;
        case 'p': prints = atoi(optarg); break;
        case 'h': set = insert_set(DEFAULT, set); break;
        default:
            // Reaches here if there is invalid input
            printf("Select at least one sort to perform.\n");
            set = insert_set(DEFAULT, set);
            break;
        }
    }

    // Initializes a pseudorandom test array consisting of 30-bit ints
    uint32_t *test_array = (uint32_t *) malloc(sizeof(uint32_t) * size);
    srandom(random_seed);

    if (prints > size) {
        prints = size;
    }

    // Sets values in pseudorandom test array
    for (uint32_t i = 0; i < size; i++) {
        uint32_t random_num = random() & 0x3fffffff;
        test_array[i] = random_num;
    }

    // Checks whether each enum exists in the set or not
    // This checks if DEFAULT exists in the set or not
    if (member_set(DEFAULT, set)) {
        printf("SYNOPSIS\n");
        printf("   A collection of comparison-based sorting algorithms.\n\n");
        printf("USAGE\n");
        printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
        printf("OPTIONS\n");
        printf("   -h              display program help and usage.\n");
        printf("   -a              enable all sorts.\n");
        printf("   -e              enable Heap sort.\n");
        printf("   -i              enable Insertion sort.\n");
        printf("   -s              enable Shell sort.\n");
        printf("   -q              enable Quick sort.\n");
        printf("   -n length       specify number of array elements (default: 100).\n");
        printf("   -p elements     specify number of elements to print (default: 100).\n");
        printf("   -r seed         specify random seed (default: 13371453).\n");
    }

    // If HEAP is a member -> perform a heapsort
    if (member_set(HEAP, set) && !member_set(DEFAULT, set)) {
        reset(&stats);

        // Creates a temporary array (applies to each option)
        uint32_t *temp_array = (uint32_t *) malloc(sizeof(uint32_t) * size);

        // Copies elements from the test array into the temporary array
        for (uint32_t i = 0; i < size; i++) {
            temp_array[i] = test_array[i];
        }

        // Performs heapsort on temporary array
        heap_sort(&stats, temp_array, size);

        printf(
            "Heap Sort, %d elements, %lu moves, %lu compares\n", size, stats.moves, stats.compares);
        for (uint32_t i = 0, j = 0; i < prints; i++, j++) {
            // Prints out the temp array in this format
            printf("%13d", temp_array[i]);

            if (j % 5 == 4) {
                printf("\n");
            }
        }

        if (prints % 5 != 0) {
            printf("\n");
        }

        // Frees the memory of the temp array
        free(temp_array);
    }

    // Just like the HEAP option, except it performs shell sort algorithm
    if (member_set(SHELL, set) && !member_set(DEFAULT, set)) {
        reset(&stats);

        uint32_t *temp_array = (uint32_t *) malloc(sizeof(uint32_t) * size);

        for (uint32_t i = 0; i < size; i++) {
            temp_array[i] = test_array[i];
        }

        shell_sort(&stats, temp_array, size);

        printf("Shell Sort, %d elements, %lu moves, %lu compares\n", size, stats.moves,
            stats.compares);
        for (uint32_t i = 0, j = 0; i < prints; i++, j++) {
            printf("%13d", temp_array[i]);

            if (j % 5 == 4) {
                printf("\n");
            }
        }

        if (prints % 5 != 0) {
            printf("\n");
        }

        free(temp_array);
    }

    // Just like HEAP option, except it performs insertion algorithm
    if (member_set(INSERTION, set) && !member_set(DEFAULT, set)) {
        reset(&stats);

        uint32_t *temp_array = (uint32_t *) malloc(sizeof(uint32_t) * size);

        for (uint32_t i = 0; i < size; i++) {
            temp_array[i] = test_array[i];
        }

        insertion_sort(&stats, temp_array, size);

        printf("Insertion Sort, %d elements, %lu moves, %lu compares\n", size, stats.moves,
            stats.compares);
        for (uint32_t i = 0, j = 0; i < prints; i++, j++) {
            printf("%13d", temp_array[i]);

            if (j % 5 == 4) {
                printf("\n");
            }
        }

        if (prints % 5 != 0) {
            printf("\n");
        }
        free(temp_array);
    }

    // Just like HEAP option, except it performs quicksort algorithm
    if (member_set(QUICK, set) && !member_set(DEFAULT, set)) {
        reset(&stats);

        uint32_t *temp_array = (uint32_t *) malloc(sizeof(uint32_t) * size);

        for (uint32_t i = 0; i < size; i++) {
            temp_array[i] = test_array[i];
        }

        quick_sort(&stats, temp_array, size);

        printf("Quick Sort, %d elements, %lu moves, %lu compares\n", size, stats.moves,
            stats.compares);
        for (uint32_t i = 0, j = 0; i < prints; i++, j++) {
            printf("%13d", temp_array[i]);

            if (j % 5 == 4) {
                printf("\n");
            }
        }

        if (prints % 5 != 0) {
            printf("\n");
        }
        free(temp_array);
    }

    // Frees all the memory from the test array
    free(test_array);
    return 0;
}
