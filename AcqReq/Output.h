#include <systemc.h>
#ifndef OUTPUT_H
#define OUTPUT_H

SC_MODULE(OUTPUT)
{

 public :
  sc_in<float> in_data_real;
  sc_in<float> in_data_imag;
  sc_in<bool>  data_valid;
  sc_out<bool> data_req;
  sc_in_clk  clk;


  SC_CTOR(OUTPUT)
    {
      SC_THREAD(comportement);
      sensitive << clk.pos() ;
    }
 private :
  void comportement();
};
#endif
