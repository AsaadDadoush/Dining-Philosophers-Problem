CC=gcc
CFLAGS=-c -o 
LIBS= -lSDL_bgi -lSDL2 -lpthread -lm
LDFLAGS=


all: cp 

cp: DP.o
	 $(CC) DiningTable.o DP.o -o dp $(LIBS) $(LDFLAGS)

DPHP.o:
	$(CC) DP.c $(CFLAGS) DP.o

clean:
	rm DP.o dp
