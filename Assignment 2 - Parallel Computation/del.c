#include <math.h>
#include <complex.h>
#include <stdlib.h>
#include <stdio.h>


struct card{
	int a;
	int b;
};
 
struct card f(struct card xx);

int main(void)
{
	//complex double y = 2 + 4 * I;
	int tt = 4;
	int bb = 6;
	struct card x_in = {tt, bb};
	struct card y_in;
	y_in = f(x_in);
	printf("%d %d\n", y_in.a, y_in.b);

	return 0;

}

struct card f(struct card xx){
	//struct card r;
	int y;
	y = 3*xx.a + 4*xx.b;
	xx.a = 3 * y;
	xx.b = 2 * pow(y,2);
	return xx;	
}
