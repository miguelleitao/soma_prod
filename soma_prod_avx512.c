/*

   Implementacao de soma de produtos

*/


#include <stdio.h>
#include <stdlib.h>

#include <immintrin.h>

extern float resultado;

float soma_prod_avx512(float *v_a, float *v_b, int size)
{
  register int i;
  __m512 v_soma_r;
  float *soma_p;
  soma_p = (float *) &v_soma_r;
  v_soma_r = _mm512_set_ps(0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.);

  for( int j=0 ; j<nCycles ; j++ )
  for( i=0 ; i<size ; i+=16 ) 
	v_soma_r = _mm512_add_ps(v_soma_r, _mm512_mul_ps( _mm512_load_ps(v_a+i), _mm512_load_ps(v_b+i)));

  /*
   * ou
   * {
   *   __m512 a, b, c;
   *   a = _mm512(v_a+i);
   *   b = _mm512(v_b+i);
   *   c = _mm512(a,b);
   *   v_soma_r = _mm512(v_soma_r,c);
   * }
   *
   */

  return resultado = soma_p[0] + soma_p[1] + soma_p[2]  + soma_p[3]  + soma_p[4]  + soma_p[5]  + soma_p[6]  + soma_p[7] +
		     soma_p[8] + soma_p[9] + soma_p[10] + soma_p[11] + soma_p[12] + soma_p[13] + soma_p[14] + soma_p[15];
}


