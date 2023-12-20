/*

   Implementacao de soma de produtos

*/


#include <stdio.h>
#include <stdlib.h>

extern float resultado;

#ifdef SOFT_FP
float soma_prod_softfp(float *v_a, float *v_b, int size)
#else
float soma_prod_fpu(float *v_a, float *v_b, int size)
#endif
{
  register int i;
  float soma = 0.;
  for( int j=0 ; j<1 ; j++ )
  for( i=0 ; i<size; i++ ) {
          soma += v_a[i]*v_b[i];
  }

  resultado = soma;
  return (float)soma;
}


