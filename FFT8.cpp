#include "FFT8.h"


void FFT8::comportement(){
  float aux[16];
  int i=0;
  while(true){
	i=0;
    while(i<16){
      while(in_data.num_available()>0){
        aux[i] = in_data.read();
        if(16 == ++i)
          break;
	cout << i << endl;
      }
      wait();
    }
    i = 0;
    while(i<16){
      while(out_data.num_free()>0){
        out_data.write(aux[i]);
        if(16 == ++i)
          break;
      }
      wait();
    }
  }
}
