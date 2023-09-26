#ifndef INDUSTRY_H_INCLUDED
#define INDUSTRY_H_INCLUDED

#include <iostream>
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

/// Job status
    int jobState;

    float jobPauseTicks;
    const float jobPauseThreshold = 4;

    std::string remainingTimeText;

/// Job identity
    //std::string industryName;

/// Inputs and outputs
    std::map<unsigned,float>inputs;
    std::map<unsigned,float>outputs;

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

    void SetJobStateInsufficientInputs(/*int thresh*/);
    void SetJobStateDeductionsNecessary();
    void SetJobStateNormal();
    void SetJobStateHarvestReady();

/// Input and output calculation

    //float CalculateAverageInput(int whichItem, int period); // Period in in-world hours

/// Production functions
    void SetProductionPerTick(float ppt);
    void ProgressJobNormalState();

/// Aesthetic functions
    void UpdateProgressBar(); // Unlike ProgressJobNormalState(); which is meant to be called on an (hourly) production tick, UpdateProgressBar is meant to be called on frame timer tick.



};

#endif // INDUSTRY_H_INCLUDED
