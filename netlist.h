//
#ifndef NETLIST_H_
#define NETLIST_H_
#include <string>
#include<fstream>
#include<string>
#include <iostream>
using namespace std;

class Netlist {
public:
    void createNtl(double newn);
    void runNtl();
    double readlog();
protected:
    ofstream outFile;
    ifstream inFile;
    FILE *ngspicepipe;
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
    ngspicepipe = popen("ngspice", "w");
    if (!ngspicepipe) {
		cerr << ("NGspice não encontrado !"); //gera erro 
    }
    else{
        fprintf(ngspicepipe, "generated_netlist.cir"); //printar no arquivo
        fflush(ngspicepipe); //limpar o buffer 
    }
};
 
double Netlist::readlog(){
    double v;
    string log = "generated_netlist.log";
    inFile.open(log);
    if (inFile.is_open()){
        //while(inFile){
            string line;
            getline(inFile, line, '=');
            inFile >> v;
       // }
        inFile.close();
    }
    else
        cerr << "Nao foi possivel abrir o log" << endl;
    
    return v;
}


#endif
