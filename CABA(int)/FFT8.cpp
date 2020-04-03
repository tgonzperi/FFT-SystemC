#include "FFT8.h"
#include<stdio.h>

#define W {\
	{round(1.0*pow(2,(L-1))),round(0.0*pow(2,(L-1)))},\
	{round(0.7071067812*pow(2,(L-1))), round(-0.7071067812*pow(2,(L-1)))}, \
	{round(0.0*pow(2,(L-1))), round(-1.0*pow(2,(L-1)))}, \
	{round(-0.7071067812*pow(2,(L-1))), round(-0.7071067812*pow(2,(L-1)))}, \
}

/**
#define W {\
	{1, 0}, \
	{0.7071067812, -0.7071067812}, \
	{0, -1}, \
	{-0.7071067812, -0.7071067812}\
}
*/
/**
constant w0_r : std_logic_vector(w downto 0) := std_logic_vector(to_signed(integer(round(1.0*real(2**(w-1)))),w+1));
constant w0_i : std_logic_vector(w downto 0) := std_logic_vector(to_signed(integer(round(0.0*real(2**(w-1)))),w+1));
constant w1_r : std_logic_vector(w downto 0) := std_logic_vector(to_signed(integer(round(0.7071067812*real(2**(w-1)))),w+1));
constant w1_i : std_logic_vector(w downto 0) := std_logic_vector(to_signed(integer(round(-0.7071067812*real(2**(w-1)))),w+1));
constant w2_r : std_logic_vector(w downto 0) := std_logic_vector(to_signed(integer(round(0.0*real(2**(w-1)))),w+1));
constant w2_i : std_logic_vector(w downto 0) := std_logic_vector(to_signed(integer(round(-1.0*real(2**(w-1)))),w+1));
constant w3_r : std_logic_vector(w downto 0) := std_logic_vector(to_signed(integer(round(-0.7071067812*real(2**(w-1)))),w+1));
constant w3_i : std_logic_vector(w downto 0) := std_logic_vector(to_signed(integer(round(-0.7071067812*real(2**(w-1)))),w+1));
*/


typedef struct complex_s complex_t;

struct complex_s {
	sc_int<L> real;
	sc_int<L> imag;
};
void fft(complex_t in[8], complex_t out[8]);


void FFT8::comportement(){
  sc_int<L> aux[16];
  int i=0;
  complex_t in[8],out[8];


  while(true){
	i=0;
  data_req_fft = false;
  data_valid_fft = false;
  wait();
    while(i<16){
      if(data_valid_input && data_req_fft){
				cout << "Saving to aux" << endl;
        aux[i]  = in_data_real.read();
        i++;
        aux[i]  = in_data_imag.read();
        cout << i << endl;
        data_req_fft = false;
        if(16 == ++i){
          break;
        }
      }else{
      data_req_fft = 1;
      }
      cout << "hola"<< data_req_fft << endl;
      wait();
    }
	for(int j = 0; j<8; j++){
		in[j].real = aux[j*2];
		in[j].imag = aux[j*2+1];
    cout << "Parte real " << j << ":" << in[j].real << endl;
    cout << "Parte imag " << j << ":" << in[j].imag << endl;
	}

	fft(in, out);
	for(int j = 0; j<8; j++){
		aux[j*2] = out[j].real;
		aux[j*2+1] = out[j].imag;
    cout << "Parte real " << j << ":" << out[j].real << endl;
    cout << "Parte imag " << j << ":" << out[j].imag << endl;
	}

    i = 0;
    while(i<16){
      if(!data_valid_fft){
        cout << "data_valid_fft = false" << endl;
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



sc_int<L+2> round_bit(sc_int<64> in){
	sc_int<L+2> r;
	int i = 63;
	while(in[i]==0){
		i=i-1;
	}
	cout<<"Max bit" << i<<endl;
  int output_size = L+2;
	if ( in[i-output_size] = 1){
	 r = in.range(i, i-output_size-1) + 1;
	}else{
	 r = in.range(i, i-output_size-1);
	}
	cout<< "Size after round"<< r.length() << endl;
	return r;
}


sc_int<L+1> resize(sc_int<L+2> in){
    int output_size = L;
    return in.range(output_size -1 ,0) ;
}

/**
const sc_int<L> w0_r = round(1.0*pow(2,(L-1)));
const sc_int<L> w0_i = round(0.0*pow(2,(L-1)));
const sc_int<L> w1_r = round(0.7071067812*pow(2,(L-1)));
const sc_int<L> w1_i = round(-0.7071067812*pow(2,(L-1)));
const sc_int<L> w2_r = round(0.0*pow(2,(L-1)));
const sc_int<L> w2_i = round(-1.0*pow(2,(L-1)));
const sc_int<L> w3_r = round(-0.7071067812*pow(2,(L-1)));
const sc_int<L> w3_i = round(-0.7071067812*pow(2,(L-1)));
*/
/**omplex_t weights[4];
	weights[0].real = w0_r;
	weights[0].imag = w0_i;
	weights[1].real = w1_r;
	weights[1].imag = w1_i;
	weights[2].real = w2_r;
	weights[2].imag = w2_i;
	weights[3].real = w3_r;
	weights[3].imag = w3_i;
*/
complex_t weights[4] = W;

void but(complex_t *weight,
					complex_t *in0,
					complex_t *in1,
					complex_t *out0,
					complex_t *out1)
{
		/**
		out0->real = (in0->real + ((in1->real * weight->real) - (in1->imag * weight->imag)));
		out0->imag = (in0->imag + ((in1->real * weight->imag) + (in1->imag * weight->real)));
		out1->real = (in0->real - ((in1->real * weight->real) - (in1->imag * weight->imag)));
		out1->imag = (in0->imag - ((in1->real * weight->imag) + (in1->imag * weight->real)));
		*/
			printf("BUT en Action\n");
			cout<< "weight " << weight->real << endl;
			sc_int<L+2> r_r = round_bit(in1->real * weight->real);
			sc_int<L+2> r_i = round_bit(in1->real * weight->imag);
			sc_int<L+2> i_r = round_bit(in1->imag * weight->real);
			sc_int<L+2> i_i = round_bit(in1->imag * weight->imag);
			cout<< "Size "<< r_r << endl;
      out0->real = resize(in0->real) + resize((r_r)) - resize((i_i));
      out0->imag = resize(in0->imag) + resize((r_i)) + resize((i_r));
      out1->real = resize(in0->real) - resize((r_r)) - resize((i_i));
      out1->imag = resize(in0->imag) - resize((r_i)) + resize((i_r));

}
void fft(complex_t in[8], complex_t out[8])
{
	complex_t stage1[8], stage2[8];
	printf("FFT en Action\n");
	// First stage
	cout<< "weight raiz de 2" << weights[1].real << endl;
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
