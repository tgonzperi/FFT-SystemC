#include <systemc.h>
#ifndef FFT8_H
#define FFT8_H

SC_MODULE(FFT8)
{

 public :
  sc_in< sc_fixed<23,18> > in_data_real, in_data_imag;
  sc_in<bool> data_valid_input, data_req_output;

  sc_out< sc_fixed<23,18> > out_data_real, out_data_imag;
  sc_out<bool> data_valid_fft, data_req_fft;
  sc_in_clk  clk;

  SC_CTOR(FFT8)
    {
      SC_THREAD(comportement);
      sensitive << clk.pos() ;
    }
 private :
  void comportement();
};
#endif
