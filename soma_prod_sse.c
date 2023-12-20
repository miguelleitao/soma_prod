/*

   Implementacao de soma de produtos

*/


#include <stdio.h>
#include <stdlib.h>

#include <xmmintrin.h>

extern float resultado;

float soma_prod_sse(float *v_a, float *v_b, int size)
{
  register int i;
  __m128 v_soma_r;
  float *soma_p;
  soma_p = (float *) &v_soma_r;
  v_soma_r = _mm_set_ps(0., 0., 0., 0.);

  for( i=0 ; i<size ; i+=4 )
        v_soma_r = _mm_add_ps(v_soma_r,_mm_mul_ps( _mm_load_ps(v_a+i), _mm_load_ps(v_b+i)));
  /*
   * ou
   * {
   *   __m128 a, b, c;
   *   a = _mm_load_ps(v_a+i);
   *   b = _mm_load_ps(v_b+i);
   *   c = _mm_mul_ps(a,b);
   *   v_soma_r = _mm_add_ps(v_soma_r,c);
   * }
   *
   */

  return resultado = soma_p[0] + soma_p[1] + soma_p[2] + soma_p[3];
}


