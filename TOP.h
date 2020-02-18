#include "FFT8.h"
#include "Output.h"
#include "Input.h"
#include "systemc.h"


SC_MODULE (TOP) {
  // signals
 
public:
  sc_clock_in clk;
  sc_fifo<float> fifo_FFT_input, fifo_FFT_output;
	
  // instanciate
  INPUT		Input;
  OUTPUT	Output;
  FFT8		fft8; 	

  SC_CTOR(TOP):
	Input("input")
	Output("output")
	fft8("fft8")
      {
	Input.out(fifo_FFT_input);
	Input.clk(clk);
	Output.in_data(fifo_FFT_output);
	Output.clk(clk);
	fft8.in_data(fifo_FFT_input);
	fft8.out_data(fifo_FFT_output);
	fft8.clk(clk);
      }
};

