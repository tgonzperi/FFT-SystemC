#include "Output.h"
#include <fstream>
#include <iostream>

void OUTPUT::comportement(){

	std::ofstream fileStream("output.txt");

	sc_fixed<23,18> tmp_val1, tmp_val2;

	if(!fileStream)
		cout<<"Can not write the output"<<endl;
	data_req = false;
	wait();

	while(true){
		if(data_valid && data_req) {
			data_req = false;
			tmp_val1 = in_data_real.read();
			tmp_val2 = in_data_imag.read();
			fileStream << tmp_val1 << " " << tmp_val2 << endl;
			cout << "writing" << endl;
		}else{
		data_req = true;
		}
		wait();
	}
}
