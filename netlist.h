//Cria netlist para a analise no ltspice
#ifdef NETLIST_H_
#define NETLIST_H_

#include<fstream>
#include<iostream>
#include<string>
using namespace std;

class Netlist{
public:
   Netlist(double x);
private:
    ofstream outFile;
}

Netlist::Netlist(double x){
    string netlist = "generated_netlist.cir";
    outFile.open(netlist);

    if(outFile.is_open()){
        outFile << "* Circuit Name" << endl;
        outFile << "V1 N001 0 10" << endl;
        outFile << "R1 N001 out" << x << endl;
        outFile << "R2 out 0 5k" << endl;
        outFile << ".tran 1ms" << endl;
        outFile << ".measure TRAN vout FIND V(out) AT=1ms " << endl;
        outFile << ".end" << endl;
        outFile.close();
    }
    else
    cerr << "Erro ao criar netlist" << endl;
}
#endif