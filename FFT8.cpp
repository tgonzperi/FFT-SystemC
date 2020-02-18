#include "FFT8.h"


void FFT8::comportement(){
  float aux[16];
  int i=0;
  while(true){
    while(i<16){
      while(in_data.num_available()>0){
        aux[i] = in_data.read();
        if(i++ == 16)
          break;
      }
      wait();
    }
    i = 0;
    while(i<16){
      while(out_data.num_free()>0){
        out_data.write(aux[i]);
        if(i++ == 16)
          break;
      }
      wait();
    }
  }
}
