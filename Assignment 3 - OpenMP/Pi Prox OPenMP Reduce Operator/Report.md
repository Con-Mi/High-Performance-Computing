# Report 
## This program calculates the number PI, and outputs the first 15 decimal points of it.
## Correct pi in 15 decimal points is: 3.14159265358979 
## Output of the program is: 					 3.14159265358965
###
## Here I use OpenMP for calculating pi from the model:
## Sum(4/1+x^2) * dx.
## Since summing a vector is a + reduce operator due to associativity and commutativity, here
## we can implement this with OpenMP.
