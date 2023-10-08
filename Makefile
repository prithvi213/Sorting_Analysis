CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: sorting

sorting: sorting.o stats.o insert.o shell.o heap.o quick.o
	$(CC) $(CFLAGS) -o sorting $^ $(LFLAGS)

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f sorting *.o

format:
	$(CC)-format -i -style=file *.[ch]

scan-build: clean
	scan-build make
