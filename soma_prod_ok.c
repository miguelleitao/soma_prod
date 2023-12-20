/*

   Implementacao de soma de produtos

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <xmmintrin.h>

//#define V_SIZE 8000000
#define V_SIZE 8

#define TIME_DIF(t2,t1)	( ((t2).tv_sec-(t1).tv_sec) * 1000000L + ((t2).tv_usec-(t1).tv_usec) )


float v_a[V_SIZE], v_b[V_SIZE];		/* Vectores de Entrada */
					/*  Resultado = Sum(v_a[i]*v_b[i])  */
float soma1, soma2, soma3;

float v_soma[4];

soma_prod1()
{
  register int i;
  soma1 = 0.;
  for( i=0 ; i<V_SIZE ; i++ )
          soma1 += v_a[i]*v_b[i];
}

soma_prod2()
{
  register int i;
  __m128 v_soma_r;
  float *soma_p;
  soma_p = (float *) &v_soma_r;
  v_soma_r = _mm_set_ps(0., 0., 0., 0.);
  for( i=0 ; i<V_SIZE ; i+=4 )
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
  soma2 = soma_p[0] + soma_p[1] + soma_p[2] + soma_p[3];
}

soma_prod3()
{

          asm (  "V_SIZE = 8	                       \n"
                "       mov $0x0, %ebx                  \n"     // ponteiro
                "       subps %xmm3, %xmm3              \n"     // total = 0
                "myLoop_3:                                  \n"
                "       movaps v_a(%ebx), %xmm2         \n"
                "       mulps  v_b(%ebx), %xmm2         \n"
                "       add $0x10, %ebx                 \n"     // 0x10 = 4 * 4 Bytes
                "       addps  %xmm2, %xmm3             \n"
                "       cmp $(V_SIZE*4), %ebx           \n"
                "       jl myLoop_3                         \n"
                "       movaps %xmm3, v_soma            \n"
             );
  soma3 = v_soma[0] + v_soma[1] + v_soma[2] + v_soma[3];
}


int main()
{
  struct timeval  t0, t1, t2, t3, t4;
  struct timezone tz;
  register int i;

  for( i=0 ; i<V_SIZE ; i++ )		/* Preenche os Vectores de entrada com valores aleatorios */
  {
	  v_a[i] = (float)(200.*rand()/RAND_MAX)-100.;
	  v_b[i] = (float)(200.*rand()/RAND_MAX)-100.;
	  v_a[i] = (float)(200.*rand()/RAND_MAX)-100.;

printf("%f, %f\n", v_a[i] ,v_b[i] );
  }

  printf("Entradas prontas\n");
  sleep(1);
  /*
   * FPU
   *
   */
  gettimeofday(&t0,&tz);
  soma_prod1();
  gettimeofday(&t1,&tz);
  printf("FPU:       %ld useg, soma=%f\n", TIME_DIF(t1,t0), soma1);
  sleep(1);
  /*
   *    SEE Intrinsic
   *    
   */
  gettimeofday(&t0,&tz);
  soma_prod2();
  gettimeofday(&t1,&tz);
  printf("SSEintrin: %ld useg, soma=%f\n", TIME_DIF(t1,t0), soma2);
  sleep(1);

  /*
   * 	SSE Assembly
   *
   */
  gettimeofday(&t0,&tz);
  soma_prod3();
  gettimeofday(&t1,&tz);
  printf("SSEassemb: %ld useg, soma=%f\n", TIME_DIF(t1,t0), soma3);
  return 0;
}

