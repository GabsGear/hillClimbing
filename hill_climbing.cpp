//gabriel ghellere 
// para compilar use  g++ hill_climbing.cpp -std=c++11 -o hc

#include"netlist.h"
#include"hill.h"
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<chrono>
#include<random>
#define it 1000

using namespace std;


int main(){
    //cout << hillClimbing() << endl;
     //Netlist a;
    // a.createNtl(5.555);
    // a.runNtl();
    HillClimbing test;
    cout << test.algoritmo() << endl; 
    return 0;
}