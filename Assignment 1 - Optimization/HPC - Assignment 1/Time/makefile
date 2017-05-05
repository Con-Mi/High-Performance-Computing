# Makefile for timing

## Compiler
cc = gcc 

time : exam.c
	$(cc) -O0 -o O0 $^
	$(cc) -O1 -o O1 $^
	$(cc) -O2 -o O2 $^
	$(cc) -O3 -o O3 $^
	$(cc) -Os -o Os $^
	$(cc) -Og -o Og $^


.PHONY : clean

clean : 
	-rm time
