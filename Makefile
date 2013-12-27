test : clean wordkit.o list.o peg.o prefix.o
	gcc -o wordkit_test.out wordkit.o list.o peg.o prefix.o ;\
	clear; ./wordkit_test.out;

wordkit.o : wordkit.c
	gcc -c wordkit.c

prefix.o : prefix.h prefix.c
	gcc -c prefix.c

list.o : list.h list.c
	gcc -c list.c

peg.o : peg.h peg.c
	gcc -c peg.c

clean : 
	rm -f *.o wordkit_test
