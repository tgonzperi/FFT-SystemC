#include<systemc.h>
#ifndef INPUT_H
#define INPUT_H

  SC_MODULE(INPUT){
    sc_in_clk clk;
    sc_in<bool> data_req;

    sc_out<bool> data_valid;
    sc_out<float> out_real, out_imag;

    void COMPORTEMENT();

    SC_CTOR(INPUT){
      SC_THREAD(COMPORTEMENT);
      sensitive << clk.pos();
    }
  };
#endif
