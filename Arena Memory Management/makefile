CC = gcc
CFLAGS = -Wall -I../Exception

vpath %.h ../Exception
vpath %.c ../Exception

arena.o:arena.c arena.h except.h Assert.h
	$(CC) $(CFLAGS) -c $<
except.o: except.c except.h
	$(CC) $(CFLAGS) -c $<
assert.o: assert.c Assert.h
	$(CC) $(CFLAGS) -c $<
Assert.h: except.o
clean:
	rm *.o
