#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "pso.h"

int main(int argc, char** argv)
{
    if(!strcmp(argv[1],"pso"))
    {
        int population_size=stoi(argv[2]);
        int dimension=stoi(argv[3]);
        double w=stod(argv[4]);
        double a1=stod(argv[5]);
        double a2=stod(argv[6]);

        PSO psomachine(population_size,dimension,w,a1,a2);
        psomachine.run();
    }
}