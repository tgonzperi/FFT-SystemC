#include "Input.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;


void INPUT::COMPORTEMENT(){
  std::ifstream fileStream("input_samples.txt");

  sc_fixed<wl,iwl> tmp_val1, tmp_val2;
  data_valid = false;

  if(!fileStream)
    cerr<<"The file is not opened"<<endl;

  wait();
  sc_int<7> i = 0;
  while(true){
    //we decided to use NUM_INPUT as stop for reading after problems detecting the eof.
    if(i < NUM_INPUT){
      if(!data_valid){
        fileStream >> tmp_val1 >> tmp_val2;
        out_real.write(tmp_val1);
        out_imag.write(tmp_val2);
        data_valid = true;
        i++;
      }else if(data_req){
        data_valid = false;
      }
    }else if(i == NUM_INPUT){
      cout << "End of File" << endl;
      data_valid = false;
      i++;
    }
	wait();
  }
}
