#ifndef SET_H
#define SET_H

#include "list.h"

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ran(long *idum);  //obtiene numero aleatorio entre 0 y 1

void inicializar(); //

int set(); //algoritmo simulacion

#endif
