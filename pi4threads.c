#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define P2 500000
// Nilakantha method
typedef struct{//estructura para pasar 2 parametros a los hilos
	double ac, den;
}pair;

void * sum4(void * arg){//funcion para sumar fracciones (4 hilos)
	pair * p = (pair *) arg;//casting para que sepa que es un apuntador al tipo pair
	for(double i = 0; i < P2/8; i++){
		p->ac+=1.0 / (p->den * (p->den + 1) * (p->den + 2));
		p->den+=2;//se va al siguiente termino (es como una trenza doble)
		p->ac-= 1.0 / (p->den * (p->den + 1) * (p->den + 2));
		p->den+=14;//se salta 3 terminos(que son de los otros hilos)
	}
	return NULL;}

int main(){
	pthread_t h1, h2, h3, h4;//crea identificadores de los 4 hilos
	pair p1, p2, p3, p4;//declara límites para repartir el trabajo
	p1.ac=0;//asigna valores iniciales
	p1.den=2;
	p2.ac=0;
	p2.den=6;
	p3.ac=0;
	p3.den=10;
	p4.ac=0;
	p4.den=14;

	clock_t start4 = clock();//tomamos el tiempo de inicio

	pthread_create(&h1, NULL, sum4, (void *) &p1);//crea hilos
	pthread_create(&h2, NULL, sum4, (void *) &p2);
	pthread_create(&h3, NULL, sum4, (void *) &p3);
	sum4((void *)&p4);//hilo principal

	pthread_join(h1 , NULL);//espera hilos
	pthread_join(h2 , NULL);
	pthread_join(h3 , NULL);

	printf("%1.9lf\n", 3.0 + (p1.ac + p2.ac + p3.ac + p4.ac) * 4.0);
	clock_t stop4 = clock();//tomamos el tiempo de terminación
	double total_ms_4 = 1000 * (stop4 - start4)/CLOCKS_PER_SEC;//calcula total time
	printf("%1.0lf ms\n", total_ms_4);//imprime total
	return 0;
}
