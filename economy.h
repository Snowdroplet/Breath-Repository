#ifndef ECONOMY_H_INCLUDED
#define ECONOMY_H_INCLUDED

#include <vector>

#include "job.h"
#include "jobindex.h"

class Economy
{
    std::vector<Job*>jobs;

    std::map<int,float>production;  // per day

    std::map<int,float>demand;

    std::map<int,float>consumption;

public:
    Economy();
    ~Economy();

    //void AdjustProduction(int a, float b);
    //void AdjustDemand(int a, float b);
    void AddJob(int whichIndustry);
    void AdjustConsumption(int a, float b);

    void EvaluateEconomy();
    void EvaluateProduction();
    void EvaluateDemand();
    void EvaluateConsumption();
};

#endif // ECONOMY_H_INCLUDED
