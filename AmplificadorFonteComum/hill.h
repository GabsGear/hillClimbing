/**
    Gabriel Ghellere
     Hillclimbing class:
     getRandom => generate a random number, normal distribution with standard deviation
     cost => function for optimization, return a atualcost
     algoritmo => hillCimbing algorithm adapted, returns a optimal value and plot historic
**/

#ifndef HILLCLIMBING_H_
#define HILLCLIMBING_H_
#include <string>
#include"netlist.h"
#include"gnuplot.h"
#include<fstream>
#include <iostream>
#include<chrono>
#include<random>
#include <cmath>
#define it 5000

using namespace std;

class HillClimbing {
public:
    double getTweak(double x, int lb, int ub);
    double getRandom();
    double cost(double rd, double vgs, double w, double l);
    void algoritmo();
protected:
    ofstream outFile;
    ofstream outFile2;
};

double HillClimbing::getTweak(double x, int lb, int ub){
    double tweak = x*(1 + 0.1 * getRandom());
    while(tweak < lb || tweak > ub)
        tweak = x*(1 + 0.1 * getRandom());
    return tweak;
};

double HillClimbing::getRandom(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution (0.0,1.0);
    return distribution(generator);
};

double HillClimbing::cost(double rd, double vgs, double w, double l){
    Netlist net;
    net.createNtl(rd, vgs, w, l);
    net.runNtl();
    double meas = net.readlog();
    return (exp(-meas/10));
};

void HillClimbing::algoritmo(){
    double rdMin = 100; double vgsMin = 1; double wMin = 3; double lMin = 1.5;
    double rdMax = 100000; double vgsMax = 5; double wMax = 100; double lMax = 10; 
    string graphlog = "graphlog.txt";
    string gainlog = "gainlog.txt";
    Netlist read;

    double rd = rdMax;//(rdMax-rdMin)/2;//rdMin + (rdMax-rdMin)*getRandom();
    double vgs = vgsMax;//(vgsMax-vgsMin)/2;//vgsMin + (vgsMax-vgsMin)*getRandom();
    double w = wMax;//(wMax-wMin)/2;//wMin + (wMax-wMin)*getRandom();
    double l = lMax;//(lMax-lMin)/2;//lMin + (lMax-lMin)*getRandom();
    int ic = 0;
    double atualCost = cost(rd, vgs, w, l);

    outFile.open(graphlog);    
    outFile2.open(gainlog);

    if(outFile.is_open() && outFile2.is_open()){
        for(int i = 0; i < it; i++){
            double rdtweak = getTweak(rd, rdMin, rdMax);
            double vgstweak = getTweak(vgs, vgsMin, vgsMax);
            double wtweak = getTweak(w, wMin, wMax);
            double ltweak = getTweak(l, lMin, lMax);
            double newCost = cost(rdtweak, vgstweak, wtweak, ltweak);

            if(newCost < atualCost){
                atualCost = newCost;
                rd = rdtweak; vgs = vgstweak; w = wtweak; l = ltweak;
            } 

            cout << "Iteração n: " << i << " " << "Valor rd modificado: " << rd << endl; 
            cout << "               Valor de vgs modificado " << vgs << endl;
            cout << "               Valor de w modificado " << w << endl;
            cout << "               Valor de l modificado " << l << endl;   
            cout << "               Ganho atual " <<  read.readlog() << endl;
            cout << "Novo custo: " << atualCost << endl; 
            cout << "----------------------------------------------" << endl;
            outFile << i << " " << atualCost << endl;
            outFile2 << i << " " << read.readlog() << endl; 
            i++;
            ic++;
        }
    outFile2.close();
    outFile.close();
    }
    cout << "=========================  VALORES OTIMOS =====================================" << endl;
    cout << "Iteração n: " << ic << " " << "Valor rd modificado= " << rd << endl;
    cout << "               Valor de vgs modificado= " << vgs << endl;
    cout << "               Valor de w modificado= " << w << endl; 
    cout << "               Valor de l modificado= " << l << endl;  
    cout << "               Ganho atual " <<  read.readlog() << endl; 
    cout << "Custo Otimo= "  << atualCost << endl; 
    
    Gnuplot plot;
    plot("plot 'graphlog.txt' title 'Otimizacao' with points pointtype 7"); 
    Gnuplot plot2;
    plot2("plot 'gainlog.txt' title 'OtimizacaoGanho' with points pointtype 5");

    getchar();
};
#endif