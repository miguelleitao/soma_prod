/*

   Implementacao de soma de produtos

*/


#include <stdio.h>
#include <stdlib.h>

extern float resultado;

float soma_prod_assemb(float *v_a, float *v_b, int size)
{
	  float v_soma[4];
          asm ( "	mov %0, %%eax"::"m"(size) ); 		// contador
          asm ( "	mov %0, %%ecx"::"m"(v_a) ); 		// v_a
	  asm ( "	mov %0, %%edx"::"m"(v_b) ); 		// v_b
          asm ( "       mov $0x0, %ebx                  \n"     // ponteiro
                "       subps %xmm5, %xmm5              \n"     // total = 0
                "myLoop_3:                              \n"
                "       movaps (%ecx,%ebx), %xmm2       \n"
                "       movaps (%edx,%ebx), %xmm3       \n"

                "       movaps %xmm2, %xmm4             \n"
                "       mulps  %xmm3, %xmm4             \n"
                "       addps  %xmm4, %xmm5             \n"

                "       movaps %xmm2, %xmm4             \n"
                "       mulps  %xmm2, %xmm4             \n"
                "       addps  %xmm4, %xmm5             \n"

                "       movaps %xmm3, %xmm4             \n"
                "       mulps  %xmm3, %xmm4             \n"
                "       addps  %xmm4, %xmm5             \n"

                "       add $0x10, %ebx                 \n"     // 0x10 = 4 * 4 Bytes
                //"       addps  %xmm4, %xmm5             \n"
		"	sub $0x4,%eax			\n"
                "       jnz myLoop_3                    \n");
	  asm ( "	movups %%xmm5, %0"::"m"(*v_soma));	
	  
  return resultado = v_soma[0] + v_soma[1] + v_soma[2] + v_soma[3];
}


