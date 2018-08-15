#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define P1 900000000

double suma(){
	double ac=0, den=1;
	for(double i=0; i<P1;i++){
		ac+=(double)(1/den);
		den+=2;
		ac-=(double)(1/den);
		den+=2;
	}
	return ac;
}
int main()
{
	clock_t start = clock();//tomamos el tiempo de inicio

	printf("%1.8lf\n", suma()*4);//calcula pi con 1 hilo//ideal is 3.141592653589793238

	clock_t stop = clock();//tomamos el tiempo de terminación

	double total_ms = 1000 * (stop-start)/CLOCKS_PER_SEC;//calcula el intervalo de tiempo
	printf("%.0lf ms\n", total_ms);
	return 0;
}
