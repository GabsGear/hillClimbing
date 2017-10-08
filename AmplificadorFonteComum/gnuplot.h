/*
	Gabriel GHellere 
	GNUPLOT class;
		 send a command to gnuplot
*/

#ifndef GNUPLOT_H_
#define GNUPLOT_H_
#include <string>
#include <iostream>
using namespace std;

class Gnuplot {
public:
	Gnuplot();
	~Gnuplot();
	void operator ()(const string & command); // send the command

protected:
	FILE *gnuplotpipe;
};

Gnuplot::Gnuplot() { //open gnuplot 
	gnuplotpipe = popen("gnuplot", "w");

	if (!gnuplotpipe) {
		cerr << ("Gnuplot not found !"); 
	}
}

Gnuplot::~Gnuplot() {//Close gnuplot
	fprintf(gnuplotpipe, "exit\n");
	pclose(gnuplotpipe);
}

void Gnuplot::operator()(const string & command) {
	fprintf(gnuplotpipe, "%s\n", command.c_str()); //sedn command
	fflush(gnuplotpipe); //buffer clear 
};

#endif
