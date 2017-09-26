//
#ifndef NETLIST_H_
#define NETLIST_H_
#include <string>
#include<fstream>
#include <iostream>
using namespace std;

class Netlist {
public:
    void createNtl(double newn);
    void runNtl();
protected:
    ofstream outFile;
    FILE *ltspicepipe;
};

void Netlist::createNtl(double newn) {
    string ntl = "generated_netlist.cir";
    outFile.open(ntl);

    if(outFile.is_open()){
        outFile << "* Circuit Name" << endl;
        outFile << "V1 N001 0 10" << endl;
        outFile << "R1 N001 out " << newn << endl;
        outFile << "R2 out 0 5k" << endl;
        outFile << ".tran 1ms" << endl;
        outFile << ".measure TRAN vout FIND V(out) AT=1ms " << endl;
        outFile << ".end" << endl;
        outFile.close();
    }
    else
    cerr << "Erro ao criar netlist" << endl;
};

void Netlist::runNtl(){
    ltspicepipe = popen("env WINEPREFIX=""/home/gabs/.wine"" wine C:\\Program/ Files\\LTC\\LTspiceXVII\\XVIIx64.exe ", "w");
    if (!ltspicepipe) {
		cerr << ("Ltspice não encontrado !"); //gera erro 
    }
    else{
        fprintf(ltspicepipe, "generated_netlist.cir"); //printar no arquivo
        fflush(ltspicepipe); //limpar o buffer 
    }
};

#endif
