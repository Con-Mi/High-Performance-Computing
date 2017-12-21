SHELL:=/bin/bash
.PHONY : all

all : 
	gcc -Ofast -march=native newton.c -lpthread -lm
	time ./a.out -l800 -t4 -d1
