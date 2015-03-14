CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic -g

all: index

index: indexer.o sorted-list.o
	$(CC) $(CFLAGS) -o index main.c indexer.o sorted-list.o

indexer.o: sorted-list.o indexer.h
	$(CC) $(CFLAGS) -c indexer.c
	
sorted-list.o: sorted-list.h
	$(CC) $(CFLAGS) -c sorted-list.c
	
clean:
	rm -rf *.o index