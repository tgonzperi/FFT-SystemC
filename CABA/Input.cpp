#include "Input.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

const int NUM_INPUT = 32;

void INPUT::COMPORTEMENT(){
  std::ifstream fileStream("input_samples.txt");

  sc_fixed<23,18> tmp_val1, tmp_val2;
  data_valid = false;

  if(!fileStream)
    cerr<<"The file is not opened"<<endl;

  wait();
  int i = 0;
  while(true){
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
