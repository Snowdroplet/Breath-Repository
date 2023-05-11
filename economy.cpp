#include "economy.h"

Economy::Economy()
{

}

Economy::~Economy()
{
    for(std::vector<Job*>::iterator it = jobs.begin(); it != jobs.end();)
    {
        delete *it;
        jobs.erase(it);
    }
}

void Economy::AddJob(int whichIndustry)
{
    jobs.push_back(new Job(whichIndustry));
}
