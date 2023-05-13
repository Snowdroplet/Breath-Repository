#ifndef INDUSTRY_H_INCLUDED
#define INDUSTRY_H_INCLUDED

#include <iostream>
#include <string>
#include <map>

#include "industryindex.h"
#include "inventoryindex.h"

class Industry
{
public:
    //static std::map<int, float>ItemBaseValue;

/// Job state
    bool jobActive;
    bool jobActivationPaused;
    int jobActivationPauseTicks;

    bool jobComplete;
    bool jobRepeating;

/// Job identity
    std::string industryName;
    int expertiseType;
    float expertiseLevelRequired;

/// Inputs and outputs
    std::map<int,float>inputs;
    std::map<int,float>outputs;

    float inputMultiplier;
    float outputMultiplier;

/// Production
    float productionMultiplier;

    float productionContributed;
    float productionToComplete;
    float baseProductionPerTick;

/// Constructor
    Industry(int id, float baseProd);
    ~Industry();

/// Job state functions
    void PauseJobActivation(int ticks);
    void CountdownPausedJobActivation(int ticks);

/// Production functions
    void SetBaseProductionPerTick(float bppt);
    void ProgressJob();

};

#endif // INDUSTRY_H_INCLUDED
