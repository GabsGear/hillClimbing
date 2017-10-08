/*
    Gabriel Ghellere    
    netlist class: FIle manipulation, log generator and execute ltspice
    createNtl=> create a netlist for analysis with variable values
    runNtl=> run netlist into Ltspice
    readelog => read for the ltspice log and search the objectives values 
*/
#ifndef NETLIST_H_
#define NETLIST_H_
#include <string>
#include<fstream>
#include<string>
#include<stdlib.h>
#include <iostream>
using namespace std;

class Netlist {
public:
    void createNtl();//double newn);
    void runNtl();
    double readlog();
protected:
    ofstream outFile;
    ifstream inFile;
};

void Netlist::createNtl(){//*double newn*/) {
    string ntl = "generated_netlist.cir";
    outFile.open(ntl);

    if(outFile.is_open()){
        string gain;
        outFile << "* Circuit Name" << endl;
        outFile << "M1 Vout VIN 0 0 N_1u l=1.5u w=3u" << endl;
        outFile << "Rd VDD Vout 25000 " << endl;
        outFile << "VDD VDD 0 5" << endl;
        outFile << "vgss VIN N001 SINE(0 0.5 1) AC 1" << endl;
        outFile << "VGS N001 0 1.5" << endl;
        outFile << ".model NMOS NMOS" << endl;
        outFile << ".model PMOS PMOS" << endl;
        outFile << ".include cmosedu_models.txt" << endl;
        outFile << ".meas gain FIND V(Vout)/V(Vin) AT 1" << endl;
        outFile << ".tran 1s" << endl;
        outFile << ".backanno" << endl;
        outFile << ".end" << endl;
        outFile.close();       
    }
    else
    cerr << "Erro ao criar netlist" << endl;
};

void Netlist::runNtl(){
       system("ltspice_linux -b generated_netlist.cir");
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
