#include<stdio.h>
#include <fstream>
#include <iostream>

  using std::cout;
  using std::endl;
int main(){

  std::ifstream fileStream1("./AcqReq/output_ref.txt");
  std::ifstream fileStream2("./AcqReq/output.txt");

  float var1, var2;
  float tmp_val1, tmp_val2;

  if(!fileStream1 || !fileStream2)
    cout<<"The file is not opened"<<endl;

  while(!fileStream1.eof() || !fileStream2.eof()){
      fileStream1 >> tmp_val1 >> tmp_val2;
      fileStream2 >> var1 >> var2;
      if (abs(tmp_val1 - var1) < 0.001 && abs(tmp_val2 - var2) < 0.001){
        cout << "Correcto" << " "  << tmp_val1 << "-" << var1 << " / "  << tmp_val2 << "-"  << var2 << endl;
      }else{
          cout << "Incorrecto" << " "  << tmp_val1 << "-" << var1 << " / "  << tmp_val2 << "-"  << var2 << endl;
      }
    }
    cout << "End of File" << endl;
return 0;
}
