#include "../inc/pso.h"
#include <time.h>
#include <fstream>
#include <windows.h>
#include <cmath>
ofstream filename_pso("result/data_pso.txt");
PSO::PSO(int population_size,int dimension,double w,double a1,double a2)
{
    this->mPopualtion_size=population_size;
    this->mDimension=dimension;
    this->mW=w;
    this->mA1=a1;
    this->mA2=a2;

    unsigned seed;
    seed = (unsigned)time(NULL);
    srand(seed);
}
void PSO::Initialize(vector<vector<double>>&solutions,
                    vector<vector<double>>&local_best_solution,
                    vector<double>&local_best_value,
                    vector<double>&global_best_solution,
                    double &global_best_value,
                    vector<vector<double>>&v)
{
    double temp,min_objective,min_index;
    min_index=0;
    min_objective=INT_MAX;
    for(int i=0;i<this->mPopualtion_size;i++)
    {
        for(int j=0;j<this->mDimension;j++)
        {
            solutions[i][j]=rnd_d(this->lower,this->upper);
            v[i][j]=rnd_d(0.0001,0.05)*(this->upper-this->lower);
            local_best_solution[i][j]=solutions[i][j];
        }
        temp=Compute_Ackley(solutions[i]);
        local_best_value[i]=temp;
        
        if(temp<min_objective)
        {
            min_objective=temp;
            min_index=i;
        }
    }
    global_best_solution=local_best_solution[min_index];
    global_best_value=min_objective;
}
void PSO::LocalBestUpdate(vector<vector<double>>solutions,
                        vector<vector<double>>&local_best_solution,
                        vector<double>&local_best_value)
{
    double temp;
    for(int i=0;i<this->mPopualtion_size;i++)
    {
        temp=Compute_Ackley(solutions[i]);
        if(temp<local_best_value[i])
        {
            local_best_value[i]=temp;
            local_best_solution[i]=solutions[i];
        }
    }
}
void PSO::GlobalBestUpdate(vector<vector<double>>local_best_solution,
                        vector<double>local_best_value,
                        vector<double>&global_best_solution,
                        double &global_best_value)
{
    double min_=local_best_value[0];
    int index=0;
    for(int i=0;i<this->mPopualtion_size;i++)
    {
        if(local_best_value[i]<min_)
        {
            min_=local_best_value[i];
            index=i;
        }
    }
    if(min_<global_best_value)
    {
        global_best_solution=local_best_solution[index];
        global_best_value=min_;
    }
}
void PSO::NewVelocity(vector<vector<double>>solutions,
                    vector<vector<double>>local_best_solution,
                    vector<double>global_best_solution,
                    vector<vector<double>>&v)
{
    for(int i=0;i<this->mPopualtion_size;i++)
        for(int j=0;j<this->mDimension;j++)
            v[i][j]=this->mW*v[i][j]+this->mA1*rnd_d(0,1)*(local_best_solution[i][j]-solutions[i][j])+this->mA2*rnd_d(0,1)*(global_best_solution[j]-solutions[i][j]);
}
void PSO::NewPosition(vector<vector<double>>&solutions,
                    vector<vector<double>>v)
{
    for(int i=0;i<this->mPopualtion_size;i++)
    {
        for(int j=0;j<this->mDimension;j++)
        {
            solutions[i][j]=solutions[i][j]+v[i][j];
            if(solutions[i][j]>this->upper || solutions[i][j]<this->lower)
                solutions[i][j]=rnd_d(this->lower,this->upper);
            // if(solutions[i][j]>this->upper)solutions[i][j]=this->upper;
            // if(solutions[i][j]<this->lower)solutions[i][j]=this->lower;
        }
    }
}
double PSO::Compute_Ackley(vector<double>solution)
{
    double ans,temp1,temp2;
    temp1=0;
    temp2=0;
    for(int i=0;i<this->mDimension;i++)
    {
        temp1+=solution[i]*solution[i];
        temp2+=cos(this->c*solution[i]);
    }
    ans=-1*(this->a)*exp(-1*(this->b)*sqrt((double)temp1/this->mDimension)-exp((double)temp2/this->mDimension))+this->a+exp(1);
    return ans;
}
double PSO::rnd_d(double down,double up)
{
    double rnd_d;
    rnd_d=(double)rand()*(up-down) / RAND_MAX + down;
    return rnd_d;
}
void PSO::Show_Local(vector<vector<double>>s)
{
    for(int i=0;i<this->mPopualtion_size;i++)
    {
        cout<<"Solutions "<<i<<":"<<endl;
        for(int j=0;j<this->mDimension;j++)
            cout<<s[i][j]<<" ";
        cout<<endl;
    }
}
void PSO::Show_Global(vector<double>s)
{
    for(int i=0;i<this->mDimension;i++)
        cout<<s[i]<<" ";
    cout<<endl;
}
void PSO::Output(vector<vector<double>>solutions)
{
    for(int i=0;i<this->mPopualtion_size;i++)
    {
        for(int j=0;j<this->mDimension;j++)
            filename_pso<<solutions[i][j]<<" ";
        filename_pso<<Compute_Ackley(solutions[i])<<endl;
    }
    filename_pso<<endl<<endl;
}
void PSO::run()
{
    int temp;
    int Evaluation=this->mDimension*10000;
    vector<vector<double>>solutions(this->mPopualtion_size,vector<double>(this->mDimension,0));//所有解
    vector<vector<double>>local_best_solution(this->mPopualtion_size,vector<double>(this->mDimension,0));//個體最佳解
    vector<double>local_best_value(this->mPopualtion_size,0);//個體最佳解的值
    vector<double>global_best_solution(this->mDimension,0);//群體最佳解
    double global_best_value;//群體最佳解的值
    vector<vector<double>>v(this->mPopualtion_size,vector<double>(this->mDimension,0));//速度
    DWORD star_time = GetTickCount();
    Initialize(solutions,local_best_solution,local_best_value,global_best_solution,global_best_value,v);

    while(Evaluation--)
    {
        Output(local_best_solution);
        LocalBestUpdate(solutions,local_best_solution,local_best_value);
        GlobalBestUpdate(local_best_solution,local_best_value,global_best_solution,global_best_value);
        NewVelocity(solutions,local_best_solution,global_best_solution,v);
        NewPosition(solutions,v);
    }
    DWORD end_time = GetTickCount();
    temp=(end_time - star_time)/1000;

    cout<<"=====[Ackley function]====="<<endl;
    cout<<"#Algorithm:Particle Swarm Optimization"<<endl;
    cout<<"#Population size:"<<this->mPopualtion_size<<endl;
    cout<<"#Dimesion:"<<this->mDimension<<endl;
    cout<<"#W:"<<this->mW<<endl;
    cout<<"#Alpha1:"<<this->mA1<<endl;
    cout<<"#Alpha2:"<<this->mA2<<endl;
    cout<<"#LocalBestSolution:"<<endl;
    Show_Local(local_best_solution);
    cout<<"#GlobalBestSolution:"<<endl;
    Show_Global(global_best_solution);
    cout<<"#GlobalBestValue:"<<global_best_value<<endl;
    cout<<"#Cost Time:"<<temp<<"s"<<endl;
}