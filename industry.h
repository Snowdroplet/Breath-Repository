#ifndef INDUSTRY_H_INCLUDED
#define INDUSTRY_H_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <cmath>

#include "industryindex.h"
#include "inventoryindex.h"

#include "calendar.h"

enum enumJobStates
{
    JOB_STATE_INSUFFICIENT_INPUTS,

    JOB_STATE_DEDUCTIONS_NECESSARY,
    JOB_STATE_NORMAL,
    JOB_STATE_HARVEST_READY
};

class Industry
{
public:
    //static std::map<int, float>ItemBaseValue;

/// Job status
    int jobState;

    //bool jobPaused;
    float jobPauseTicks;
    float jobPauseThreshold;

    //bool jobHarvestReady;

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

    float productionPerTick;

/// Aesthetic
    float productionProgressBarFill; // 0.0 to 1.0
    float pauseProgressBarFill;

    bool productionProgressBarNeedsRollover;
    bool pauseProgressBarNeedsRollover;

/// Constructor
    Industry(int id, float baseProd);
    ~Industry();

/// Job state function;
    void ProgressJobPause();

    void SetJobStateInsufficientInputs(int thresh);
    void SetJobStateDeductionsNecessary();
    void SetJobStateNormal();
    void SetJobStateHarvestReady();


/// Production functions
    void SetProductionPerTick(float ppt);
    void ProgressJobNormalState();

/// Aesthetic functions
    void UpdateProgressBar(); // Unlike ProgressJob(); which is meant to be called on an (hourly) production tick, UpdateProgressBar is meant to be called on frame timer tick.

};

#endif // INDUSTRY_H_INCLUDED
