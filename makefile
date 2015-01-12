ifdef WINDOW
    X = :
    ifeq ($(WINDOW), false)
	X = console_ihm
    endif
    ifeq ($(WINDOW), true)
	X = graph_ihm
    endif
  else
    X = graph_ihm
  endif

all: bdd.o ihm.o heart.o
	gcc source/code/main.c -o mydevin -Wall -ansi include/$(X).o include/bddcode.o include/heart.o -lMLV
ihm.o:
	gcc -c source/code/$(X).c -o include/$(X).o
bdd.o:
	gcc -c source/code/bddacces.c -o include/bddcode.o
heart.o:
	gcc -c source/code/heart.c -o include/heart.o
clean2:
	rm include/*.o;
clean:
	rm mydevin;
d_test: bdd.o ihm.o heart.o
	gcc source/code_test/d_main.c -o test_mydevin -Wall -ansi include/$(X).o include/bddcode.o include/heart.o -lMLV
d_clean:
	rm test_mydevin;
test:
	gcc source/code/bddacces.c -Wall -ansi -lMLV -o test
cleanTest:
	rm test;