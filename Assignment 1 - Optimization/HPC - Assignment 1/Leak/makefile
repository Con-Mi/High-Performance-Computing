

check : ./a.out
 	valgrind ./a.out > check.txt > 2>&1

a.out : leak.c
	 gcc leak.c

.PHONY : 
	clean
	rm a.out
	
