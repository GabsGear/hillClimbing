//gabriel ghellere 
// para compilar use  g++ hill_climbing.cpp -std=c++11 -o hc

#include"netlist.h"
#include"hill.h"
#include "gnuplot.h"
#include<iostream>
#define it 1000

using namespace std;


int main(){
    HillClimbing test;
    test.algoritmo();
    //Gnuplot plot;
    //plot("plot 'graphlog.txt' title 'Otimizacao' with points pointtype 7"); 
    //getchar();
     return 0;
}
