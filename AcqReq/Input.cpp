#include "Input.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

void INPUT::COMPORTEMENT(){
  std::ifstream fileStream("input_samples.txt");

  float tmp_val1, tmp_val2;

  if(!fileStream)
    cerr<<"The file is not opened"<<endl;

  wait();

  while(true){
    if(!fileStream.eof()){
      if(out.num_free()>0){
        fileStream >> tmp_val1 >> tmp_val2;
        out.write(tmp_val1);
        out.write(tmp_val2);
	cout << "reading" << endl;
      }else{
        cout << "No space available" << endl;
      }
    }else{
      cout << "End of File" << endl;
    }
	wait();
  }
}
