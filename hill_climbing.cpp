//gabriel ghellere 
// para compilar use  g++ hill_climbing.cpp -std=c++11 -o hc

#include"netlist.h"
#include"hill.h"
//#include "gnuplot.h"
#include<iostream>
#define it 1000

using namespace std;


int main(){
     //Netlist a;
     //a.createNtl(1.2323442);
     
     //a.runNtl();
      HillClimbing test;
     // cout << test.cost(2.421) << endl;
     cout << test.algoritmo() << endl; 
     //cout << a.readlog()<< endl;
     
     //getchar();

    return 0;
}
