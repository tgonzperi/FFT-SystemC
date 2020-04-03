#include "FFT8.h"
#include<stdio.h>

#define W {\
	{1, 0}, \
	{0.7071067812, -0.7071067812}, \
	{0, -1}, \
	{-0.7071067812, -0.7071067812}\
}


struct complex_t {
	sc_fixed<23,18> real;
	sc_fixed<23,18> imag;
};


struct  complex_w {
	sc_fixed<24,2> real;
	sc_fixed<24,2> imag;
};

void fft(complex_t in[8], complex_t out[8]);



void FFT8::comportement(){
  sc_fixed<23,18> aux[16];
  sc_int<6> i=0;
  complex_t in[8],out[8];


  while(true){
	i=0;
  data_req_fft = false;
  data_valid_fft = false;
  wait();
    while(i<16){
      if(data_valid_input && data_req_fft){
        aux[i]  = in_data_real.read();
        i++;
        aux[i]  = in_data_imag.read();
        data_req_fft = false;
        if(16 == ++i){
          break;
        }
      }else{
      data_req_fft = 1;
      }
      wait();
    }
	for(int j = 0; j<8; j++){
		in[j].real = aux[j*2];
		in[j].imag = aux[j*2+1];
	}

	fft(in, out);
	for(int j = 0; j<8; j++){
		aux[j*2] = out[j].real;
		aux[j*2+1] = out[j].imag;
	}

    i = 0;
    while(i<16){
      if(!data_valid_fft){
        out_data_real.write(aux[i]);
        i++;
        out_data_imag.write(aux[i]);
        data_valid_fft = true;
        // if(16 == ++i){
        //   //data_valid_fft = false;
        //   break;
        // }
        i++;
      }else if(data_req_output){
        data_valid_fft = false;
      }
      wait();
    }
  }
}



complex_w weights[4] = W;

void but(complex_w *weight,
					complex_t *in0,
					complex_t *in1,
					complex_t *out0,
					complex_t *out1)
{
      out0->real = (in0->real + ((in1->real * weight->real) - (in1->imag * weight->imag)));
      out0->imag = (in0->imag + ((in1->real * weight->imag) + (in1->imag * weight->real)));
      out1->real = (in0->real - ((in1->real * weight->real) - (in1->imag * weight->imag)));
      out1->imag = (in0->imag - ((in1->real * weight->imag) + (in1->imag * weight->real)));
}
void fft(complex_t in[8], complex_t out[8])
{
	complex_t stage1[8], stage2[8];

	// First stage
	but(&weights[0], &in[0], &in[4], &stage1[0], &stage1[1]);
	but(&weights[0], &in[2], &in[6], &stage1[2], &stage1[3]);
	but(&weights[0], &in[1], &in[5], &stage1[4], &stage1[5]);
	but(&weights[0], &in[3], &in[7], &stage1[6], &stage1[7]);

	// Second stage
	but(&weights[0], &stage1[0], &stage1[2], &stage2[0], &stage2[2]);
	but(&weights[2], &stage1[1], &stage1[3], &stage2[1], &stage2[3]);
	but(&weights[0], &stage1[4], &stage1[6], &stage2[4], &stage2[6]);
	but(&weights[2], &stage1[5], &stage1[7], &stage2[5], &stage2[7]);

	// Etape 3
	but(&weights[0], &stage2[0], &stage2[4], &out[0], &out[4]);
	but(&weights[1], &stage2[1], &stage2[5], &out[1], &out[5]);
	but(&weights[2], &stage2[2], &stage2[6], &out[2], &out[6]);
	but(&weights[3], &stage2[3], &stage2[7], &out[3], &out[7]);
}
