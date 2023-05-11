#ifndef JOB_H_INCLUDED
#define JOB_H_INCLUDED

#include <string>
#include <map>

#include "jobindex.h"
#include "inventoryindex.h"

class Job
{
public:
    bool complete;
    bool repeatingJob;

    std::string jobName;

    std::map<int,float>inputs;
    std::map<int,float>outputs;

    int expertiseType;
    int expertiseLevelRequired;

    float inputMultiplier;
    float outputMultiplier;

    float productionMultiplier;

    float productionContributed;
    float productionToComplete;

    Job(int whichIndustry);
    ~Job();

};

#endif // JOB_H_INCLUDED
