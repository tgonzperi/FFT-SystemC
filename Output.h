#include <systemc.h>
#ifndef OUTPUT_H
#define OUTPUT_H

SC_MODULE(OUTPUT)
{

 public : 
  sc_fifo_in<float> in_data;
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
