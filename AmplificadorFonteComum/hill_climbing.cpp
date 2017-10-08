//gabriel ghellere 
// para compilar use  g++ hill_climbing.cpp -std=c++11 -o hc

#include"netlist.h"
//#include"hill.h"
//#include "gnuplot.h"
#include<iostream>
#define it 1000

using namespace std;


int main(){
      //HillClimbing test;
     //cout << "Valor otimo encontrado = " << test.algoritmo() << endl; 
     Netlist list;

     list.createNtl();
     list.runNtl();
     cout << "log= " << list.readlog()<< endl;
     return 0;
}
