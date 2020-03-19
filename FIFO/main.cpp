#include <systemc.h>
#include "TOP.h"

int sc_main ( int argc, char *argv[])
{
	//Instanciation du TOP
	TOP mainTop("top");

	//Creation des traces 
	sc_trace_file *tf = sc_create_vcd_trace_file("trace");
	tf->set_time_unit(1, SC_NS);
	

	mainTop.fifo_FFT_input.trace(tf);
	mainTop.fifo_FFT_output.trace(tf);


	sc_start(2000, SC_NS);
	//fin
	cout<< "Finished at" << sc_time_stamp() << "\n";
	//Fermeture du fichier de traces
	sc_close_vcd_trace_file(tf);

	return 0;
}
