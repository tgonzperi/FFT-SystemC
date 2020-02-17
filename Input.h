#include<systemc.h>
#ifndef INPUT_H
#define INPUT_H

  SC_MODULE(INPUT){
    sc_in_clk clk;
    sc_fifo_out<float> out;

    void COMPORTEMENT();

    SC_CTOR(INPUT){
      SC_THREAD(COMPORTEMENT);
      sensitive << clk.pos();
    }
  }
#endif
