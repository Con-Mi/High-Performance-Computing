#Assignment 1 - Marios Aspris
# Civic code: 880415-T994
## Task 1 - Timing.
#### Timing the sum using Newtons method with the different optimization levels. This is not the general implementation of the sum, $(b-a)*((b-a)+1)/2$, with $b<a$, so I can avoid the if statement. Therefore it is implemented the formula for the sum, $n*(n+1)/2$ using a macro. The -O0 level is basic no optimization, only the rest. The following table shows the optimization timing results.
| Optimization Level | Timing |
|----------------		|	---	|
| 	-O0			| 0.000054 secs |
| 	-O1			| 0.000053 secs |
|	-O2			| 0.000055 secs |
| 	-03			| 0.000050 secs |
|	-Os			| 0.000057 secs |
|	-Og			| 0.000051 secs |

#### In the assembly code of the optimization levels, the -O2 and -O3 do not seem to change.   

##
## Task 2 - Inlining.
#### Timing the inlining programs. First for using a function from a separate file I use:
####' gcc -c mul_cpx.c '
####' gcc -c Inlining.c ' 
####' gcc -o Inlining mul_cpx.o Inlining.o '
#### The following results are obtained by compiling the programs ' Inlining.c,  mul_cpx.c, Inlining1.c, Inlining2.c '
|  Different Inlining Versions |  Timing|
| -----------------------------| ------------------|
|  Inilining.c, Inlining with outside function|  0.004161 secs |
|  Inlining1.c, Inlining with function inside the program |   0.0041044 secs |
| Inlining2.c, Inlining by hand | 0.004307 secs  | 

#### Here we can observe that the fastest way is to have the function inside of the program. Calling a function takes time for C when I compile and run it. I assume that the gcc compiler does something automatically when the function is inside the program.

##
## Task 3 - Locality
#### The following results are obtained from doing row sums and column sums with naive, and fast implementations.
| Optimization Level 	| Timing Naive Implementation |	 Timing Fast Implementation | 
| ------------ | ---------------- | ------- |
|	-O0 No Optmization level  | 	   0.047373	|   0.037556	|
|	-O3	|   0.021678	|   0.022130 	|


##
## Task 4 - Indirect Adressing
#### Comparing timings for indirect adressing and direct adressing, with and without optimization. For te optimization level I use -Ofast to compare.

|  | Indirect Adressing Time |	 Direct Adressing Time | 
| ------------ | ---------------- | ------- |
|	Optimization with -Ofast  | 0.000000 sec	|  0.000000 sec	|
|	No Optimization	|  0.00000 sec	|  0.000000 sec	|

#### It seems that I do not see any differences in the timing.

##
## Task 5 - Valgrind
#### I create the program with allocating memory with the command malloc() and then I do not free it. It seems that the program takes some time to run. Then use the command valgrind ./a.out, it outputs details on memory leak. The valgrind command has as a degault option --tools=memcheck according to documentation, so it does not need to be specified. Then I output the report from valgrind command. Since with malloc we are doing dynamic memory allocation, the heap summary says that 4000 bytes were in use at exit, and there were definitely lost. Hence there is a leak in memory. In the C language as far as I know there is no garbage collector, and checking if there are memory leaks in a program are important. 


##
## Task 5 - Profiling
####
#### Using gprof for profiling I first use the following commands.
#### gcc -Wall -pg locality.c -o test_gprof
#### gprof test_gprof gmon.out > analysis.txt
#### gedit analysis.txt
#### //////
#### gcc -Wall -pg localityFast.c -o test_gprof_fast
#### gprof test_gprof_fast gmon.out > analysisFast.txt
#### gedit analysisFast.txt
#### //////
#### Comparing the analysis text for the two implementations, it seems that we have two calls of the loop in the fast implementation and two seperate calls for the for loops in the naive implementations. 
#### For gcov I used the following:
#### gcc -fprofile-arcs -ftest-coverage locality.c
#### gcov locality.c
#### gedit locality.c.gcov
#### // Similar for the fast implementation//
#### gcc -fprofile-arcs -ftest-coverage localityFast.c
#### gcov localityFast.c
#### gedit localityFast.c.gcov
#### The number of for loops executed are shown on the left. For the naive implementation the number of loops executed is much more bigger as there are executed separately.
