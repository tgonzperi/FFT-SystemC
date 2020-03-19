#include <systemc.h>
#ifndef FFT8_H
#define FFT8_H

SC_MODULE(FFT8)
{

 public : 
  sc_fifo_in<float> in_data;
  sc_fifo_out<float> out_data;
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
