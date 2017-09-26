//gabriel ghellere Hill climbing + aleatorios dist norm
// para compilar use  g++ hill_climbing.cpp -std=c++11 -o hc

#include"netlist.h"
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<chrono>
#include<random>
#define it 1000

using namespace std;

double getRandom(){
    //gerador de numeros aleatorios baseados no tempo
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution (0.0,1.0);
    return distribution(generator);
}

double cost(double x){
    return x*x; //funcao x² 
}

double hillClimbing(){
    double x = getRandom();
    double atualCost = cost(x);
    for(int i = 0; i < it; i++){
        double tweak = x + getRandom();
        double newCost = cost(tweak);
        if(newCost < atualCost){
            atualCost = newCost;
            x = tweak;
        }
    }
    return x;
}

int main(){
    //cout << hillClimbing() << endl;

    Netlist a;
    a.createNtl(5.555);
    return 0;
}