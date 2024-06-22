sample: sample.o except.o assert.o
	gcc -o sample sample.o except.o assert.o
sample.o: sample.c except.h
	gcc -c sample.c
except.o: except.c except.h
	gcc -c except.c
assert.o: assert.c Assert.h
	gcc -c assert.c
Assert.h: except.o
clean:
	rm *.o sample
