/*

   Implementacao de soma de produtos

*/


#include <stdio.h>
#include <stdlib.h>

#include <immintrin.h>

extern float resultado;

float soma_prod_avx(float *v_a, float *v_b, int size)
{
  #ifdef __AVX__
  register int i;
  __m256 v_soma_r;
  float *soma_p;
  soma_p = (float *) &v_soma_r;
  v_soma_r = _mm256_set_ps(0., 0., 0., 0., 0., 0., 0., 0.);

  //for( int j=0 ; j<nCycles ; j++ )
  for( i=0 ; i<size ; i+=8 ) 
	v_soma_r = _mm256_add_ps(v_soma_r,_mm256_mul_ps( _mm256_load_ps(v_a+i), _mm256_load_ps(v_b+i)));
	
  /*
   * ou
   * {
   *   __m256 a, b, c;
   *   a = _mm256_load_ps(v_a+i);
   *   b = _mm256_load_ps(v_b+i);
   *   c = _mm256_mul_ps(a,b);
   *   v_soma_r = _mm256_add_ps(v_soma_r,c);
   * }
   *
   */

  return resultado = soma_p[0] + soma_p[1] + soma_p[2] + soma_p[3] + soma_p[4] + soma_p[5] + soma_p[6] + soma_p[7];
#else
  printf("AVX is not available.\n");
  return resultado = 0.;
#endif
}


