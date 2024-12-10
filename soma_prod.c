/*

   Implementacao de soma de produtos

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>


#define V_SIZE 100000000
//#define V_SIZE 80

#define TIME_DIF(t2,t1)	( ((t2).tv_sec-(t1).tv_sec) * 1000000L + ((t2).tv_usec-(t1).tv_usec) )


float v_a[V_SIZE] __attribute__ ((aligned (64)));
float v_b[V_SIZE] __attribute__ ((aligned (64)));
		/* Vectores de Entrada */
		/*  Resultado = Sum(v_a[i]*v_b[i])  */


float soma_prod_fpu(float*, float*, int);
float soma_prod_sse(float*, float*, int);
float soma_prod_assemb(float*, float*, int);
float soma_prod_softfp(float*, float*, int);
float soma_prod_avx(float*, float*, int);
float soma_prod_avx512(float*, float*, int);

extern float res_soft;
float resultado;
int main()
{
  struct timeval  t0, t1;
  struct timezone tz;

  register int i;

  for( i=0 ; i<V_SIZE ; i++ )		/* Preenche os Vectores de entrada com valores aleatorios */
  {
	  v_a[i] = (float)(200.*rand()/RAND_MAX)-100.;
	  v_b[i] = (float)(200.*rand()/RAND_MAX)-100.;
  }

  printf("Entradas prontas\n");
  sleep(2);
  /*
   * FPU
   *
   */
  gettimeofday(&t0,&tz);
  soma_prod_fpu(v_a, v_b, V_SIZE);
  gettimeofday(&t1,&tz);
  if ( resultado!=0. ) printf("FPU:       %7ld useg, soma=%f\n", TIME_DIF(t1,t0), resultado);
  sleep(1);



  /*
   * Soft Floating Point
   *
   */
  gettimeofday(&t0,&tz);
  soma_prod_softfp(v_a, v_b, V_SIZE);
  gettimeofday(&t1,&tz);
  if ( resultado!=0. ) printf("SoftFP:    %7ld useg, soma=%f\n", TIME_DIF(t1,t0), resultado);
  sleep(1);

  /*
   * 	SSE Assembly
   *
   */
  gettimeofday(&t0,&tz);
  soma_prod_assemb(v_a, v_b, V_SIZE);;
  gettimeofday(&t1,&tz);
  if ( resultado!=0. ) printf("SSEassemb: %7ld useg, soma=%f\n", TIME_DIF(t1,t0), resultado);
  sleep(1);

  /*
   *    SEE Intrinsic
   *
   */
  gettimeofday(&t0,&tz);
  soma_prod_sse(v_a, v_b, V_SIZE);
  gettimeofday(&t1,&tz);
  if ( resultado!=0. ) printf("SSE:       %7ld useg, soma=%f\n", TIME_DIF(t1,t0), resultado);
  sleep(1);
  /*
   *    AVX 
   *
   */
  gettimeofday(&t0,&tz);
  soma_prod_avx(v_a, v_b, V_SIZE);;
  gettimeofday(&t1,&tz);
  if ( resultado!=0. ) printf("AVX:       %7ld useg, soma=%f\n", TIME_DIF(t1,t0), resultado);
  sleep(1);

  /*
   *    AVX512
   *
   */
  gettimeofday(&t0,&tz);
  soma_prod_avx512(v_a, v_b, V_SIZE);;
  gettimeofday(&t1,&tz);
  if ( resultado!=0. ) printf("AVX512:    %7ld useg, soma=%f\n", TIME_DIF(t1,t0), resultado);
  return 0;

}

