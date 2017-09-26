#ifndef HILLCLIMBING_H_
#define HILLCLIMBING_H_
#include <string>
#include"netlist.h"
#include"gnuplot.h"
#include<fstream>
#include <iostream>
#include<chrono>
#include<random>
#define it 1000

using namespace std;

class HillClimbing {
public:
    double getRandom();
    double cost(double x);
    double algoritmo();
};

double HillClimbing::getRandom(){
    //gerador de numeros aleatorios baseados no tempo (normal desvio padrao 1)
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution (0.0,1.0);
    return distribution(generator);
};

double HillClimbing::cost(double x){
    //função custo
    Netlist net;
    net.createNtl(x);
   //net.runNtl();
    double meas = net.readlog();
    double objective = 5;
   return (meas-objective)*(meas-objective);
};

double HillClimbing::algoritmo(){
     int lb = 100;
     int ub = 20000;
     int x = 1000;
     //x = lb + (ub-lb)*gerRandom;
    //double x = getRandom();
    double atualCost = cost(x);
    for(int i = 0; i < it; i++){
        double tweak = x*(1 + 0.1 * getRandom());
        while(tweak < lb || tweak > ub)
             tweak = x*(1 + 0.1 * getRandom());
        double newCost = cost(tweak);
        if(newCost < atualCost){
            atualCost = newCost;
            x = tweak;
        }
    }
    return x;
};
#endif