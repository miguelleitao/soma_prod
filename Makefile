
TARGET=soma_prod


OBJ= 	soma_prod.o \
	soma_prod_fpu.o \
	soma_prod_softfp.o \
	soma_prod_assemb.o \
	soma_prod_sse.o \
	soma_prod_avx.o \
	soma_prod_avx512.o \
	fp-bit-f.o \
	fp-bit-d.o

CFLAGS = -g -mstackrealign -O1 -DnCycles=1 -Wall

all: $(TARGET)

$(TARGET): $(OBJ)
	cc -o $@ $^

soma_prod_fpu.o: soma_prod_fpu.c
	cc $(CFLAGS)   -c -o $@ -mfpmath=387 $<

soma_prod_sse.o: soma_prod_sse.c
	cc $(CFLAGS)   -c -o $@ -march=native $<

soma_prod_avx.o: soma_prod_avx.c
	cc $(CFLAGS)   -c -o $@ -march=native $<

soma_prod_avx512.o: soma_prod_avx512.c
	cc $(CFLAGS)   -c -o $@ -march=native $<

soma_prod_softfp.o: soma_prod_fpu.c
	cc $(CFLAGS)   -c -o $@ -mfpmath=387 -msoft-float -mno-fp-ret-in-387 -DSOFT_FP $<

fp-bit-f.o: fp-bit.c
	cc $(CFLAGS)   -c -o $@ -msoft-float -mno-fp-ret-in-387 -DFLOAT -DNO_NANS $<

fp-bit-d.o: fp-bit.c
	cc $(CFLAGS)   -c -o $@ -msoft-float -mno-fp-ret-in-387 -DNO_NANS $<


clean:
	rm $(OBJ) $(TARGET)
