## Sorting: Putting your affairs in order

This program is a program which takes an array of numbers and uses various different functions to sort numbers from smallest to largest. This program sorts numbers using heapsort, insertion sort, selection sort, and quicksort. In addition, we also measure the number of moves and comparisons each sort takes. The number of elements you can sort in this program is modifiable.

## Building

To build the 'sorting' program:

make/make all

or

clang -Wall -Wextra -Werror -Wpedantic -o sorting *.o -lm
clang -Wall -Wextra -Werror -Wpedantic -c *.c

## Running

To run the 'sorting' program:

./sorting -[haeisqr:n:p:]

Running the program requires at least an additional command-line argument inside the square brackets. For the -n argument, you need to input a size variable, for the -p option, you need to input the number of prints variable, and for the -r argument, you need to input a random seed value.

## Cleaning

To clean the folder:

make clean

or

rm -f *.o sorting

## Formatting

To format all the files:

make format

## Scan Build

To run a scan-build:

scan-build make
