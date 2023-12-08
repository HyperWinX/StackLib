all:
	@echo "Use 'make shared' for building shared library, or 'make tests' for building tests/benchmarks"

shared:
	gcc -fPIC -c stack.c -o libstack.o
	gcc -shared -o libstack.so libstack.o
	rm -f libstack.o

perftest:
	gcc -O0 main.c stack.c -o test
	@./test 1024
	gcc -O2 main.c stack.c -o test
	@./test 1024
	@rm -f test

