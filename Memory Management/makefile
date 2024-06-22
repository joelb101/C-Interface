CC = gcc
CFLAGS = -Wall -I../Exception

vpath %.h ../Exception
vpath %.c ../Exception

sample: sample.o mem.o except.o assert.o
	$(CC) $(CFLAGS) -o $@ $^
sample.o: sample.c except.h mem.h
	$(CC) $(CFLAGS) -c $<
mem.o: mem.c mem.h except.h Assert.h
	$(CC) $(CFLAGS) -c $<
except.o: except.c except.h
	$(CC) $(CFLAGS) -c $<
assert.o: assert.c Assert.h
	$(CC) $(CFLAGS) -c $<
Assert.h: except.o
clean:
	rm *.o sample

