CC=gcc
CFLAGS= -Wall -Werror
OBJS= memory.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) main.c

cpu.o: cpu.c
	$(CC) $(CFLAGS) -c memory.c

clean:
	rm *.o *.out
