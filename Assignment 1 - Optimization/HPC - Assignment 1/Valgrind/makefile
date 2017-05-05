

leak.o : leak.c
	gcc -o leak leak.c	

log.txt : leak.o
	valgrind ./leak > log.txt 2>&1

.PHONY : clean
clean : 
	-rm log.txt leak 
