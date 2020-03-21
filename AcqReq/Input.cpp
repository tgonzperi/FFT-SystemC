#include "Input.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

void INPUT::COMPORTEMENT(){
  std::ifstream fileStream("input_samples.txt");

  float tmp_val1, tmp_val2;
  data_valid = false;

  if(!fileStream)
    cerr<<"The file is not opened"<<endl;

  wait();

  while(true){
    if(!fileStream.eof()){
      if(!data_valid){
        fileStream >> tmp_val1 >> tmp_val2;
        cout << "Parte real entr " << ":" << tmp_val1 << endl;
        cout << "Parte imag entr " << ":" << tmp_val2 << endl;
        out_real.write(tmp_val1);
        out_imag.write(tmp_val2);
	      cout << "reading" << endl;
        data_valid = true;
      }else if(data_req){
        data_valid = false;
      }
    }else{
      cout << "End of File" << endl;
      data_valid = false;
    }
	wait();
  }
}
