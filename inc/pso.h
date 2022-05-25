#ifndef __PSO_H__
#define __PSO_H__

#include <iostream>
#include <string>
#include <vector>
#define PI 3.14
using namespace std;

class PSO
{
public:
    PSO(int population_size,int dimension,double w,double a1,double a2);
    void run();
private:
    void Initialize(vector<vector<double>>&solutions,
                    vector<vector<double>>&local_best_solution,
                    vector<double>&local_best_value,
                    vector<double>&global_best_solution,
                    double &global_best_value,
                    vector<vector<double>>&v);
    void LocalBestUpdate(vector<vector<double>>solutions,
                        vector<vector<double>>&local_best_solution,
                        vector<double>&local_best_value);
    void GlobalBestUpdate(vector<vector<double>>local_best_solution,
                        vector<double>local_best_value,
                        vector<double>&global_best_solution,
                        double &global_best_value);
    void NewVelocity(vector<vector<double>>solutions,
                    vector<vector<double>>local_best_solution,
                    vector<double>global_best_solution,
                    vector<vector<double>>&v);
    void NewPosition(vector<vector<double>>&solutions,
                    vector<vector<double>>v);
    double Compute_Ackley(vector<double>solution);
    double rnd_d(double down,double up);
    void Show_Local(vector<vector<double>>s);
    void Show_Global(vector<double>s);
    void Output(vector<vector<double>>solutions);

    int mPopualtion_size;
    int mDimension;
    double mW;
    double mA1;
    double mA2;

    int lower=-32;
    int upper=32;

    //Ackley function
    int a=20;
    double b=0.2;
    double c=2*PI;
};

#endif