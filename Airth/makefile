arith.o: arith.c arith.h
	gcc -c arith.c
sample: sample.o arith.o
	gcc -o sample sample.o arith.o
sample.o: sample.c arith.h
	gcc -c sample.c
clean:
	rm *.o sample
