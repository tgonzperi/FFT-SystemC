#include "Output.h"
#include <fstream>
#include <iostream>

void OUTPUT::comportement(){

	std::ofstream fileStream("output.txt");

	float tmp_val1, tmp_val2;

	if(!fileStream)
		cout<<"Can not write the output"<<endl;

	wait();

	while(true){
		if(in_data.num_available() > 0) {	
			tmp_val1 =in_data.read();
			tmp_val2 =in_data.read();
			fileStream << tmp_val1 << " " << tmp_val2 << endl;
			wait();
		} else {
			cout<<"Finished printing"<<endl;
		}
				
	}
		

}

