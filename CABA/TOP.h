#include "FFT8.h"
#include "Output.h"
#include "Input.h"
#include "systemc.h"


SC_MODULE (TOP) {
  // signals

public:
  sc_in_clk clk;
  //sc_fifo<float> fifo_FFT_input, fifo_FFT_output;
  bool s_valid;
  sc_signal< sc_fixed<23,18> > s_input_real, s_input_imag, s_output_real, s_output_imag;
  sc_signal<bool> s_data_valid_input, s_data_req_input, s_data_valid_output, s_data_req_output;
  // instanciate
  INPUT		Input;
  OUTPUT	Output;
  FFT8		fft8;

  SC_CTOR(TOP):
	// clk("clk", 2, SC_NS, 0.5),
	Input("input"),
	Output("output"),
	fft8("fft8")
	// fifo_FFT_input(16),
	// fifo_FFT_output(16)
      {


	Input.out_real(s_input_real);
  Input.out_imag(s_input_imag);
  Input.data_valid(s_data_valid_input);
  Input.data_req(s_data_req_input);
	Input.clk(clk);
  Output.in_data_real(s_output_real);
  Output.in_data_imag(s_output_imag);
  Output.data_valid(s_data_valid_output);
  Output.data_req(s_data_req_output);
	Output.clk(clk);
	fft8.in_data_real(s_input_real);
	fft8.in_data_imag(s_input_imag);
  fft8.out_data_real(s_output_real);
	fft8.out_data_imag(s_output_imag);
	fft8.data_valid_input(s_data_valid_input);
	fft8.data_req_output(s_data_req_output);
	fft8.data_valid_fft(s_data_valid_output);
	fft8.data_req_fft(s_data_req_input);
	fft8.clk(clk);
    //s_valid = s_data_valid_input.read();
      }

};
