#include "industry.h"

Industry::Industry(int id, float ppt)
{
    jobState = JOB_STATE_INSUFFICIENT_INPUTS;
    jobPauseTicks = 0;

    //industryName = industryNames.at(id);

    inputMultiplier = 1.0;
    outputMultiplier = 1.0;

    productionMultiplier = 1.0;
    productionContributed = 0;
    productionToComplete = baseProductionToComplete.at(id);
    SetProductionPerTick(ppt);

    if(baseJobInputs.count(id) > 0)
        for(std::map<int, float>::const_iterator it = baseJobInputs.at(id).cbegin(); it != baseJobInputs.at(id).cend(); ++it)
            inputs[(*it).first] = (*it).second;

    if(baseJobOutputs.count(id) > 0)
        for(std::map<int, float>::const_iterator it = baseJobOutputs.at(id).cbegin(); it != baseJobOutputs.at(id).cend(); ++it)
            outputs[(*it).first] = (*it).second;

    pauseProgressBarFill = jobPauseTicks/jobPauseThreshold;
    pauseProgressBarNeedsRollover = false;

    productionProgressBarFill = productionContributed/productionToComplete;
    productionProgressBarNeedsRollover = false;
}

Industry::~Industry()
{

}

void Industry::SetJobStateInsufficientInputs(/*int thresh*/)
{
    jobState = JOB_STATE_INSUFFICIENT_INPUTS;

    jobPauseTicks = 0;
    //jobPauseThreshold = thresh;
}

void Industry::SetJobStateDeductionsNecessary()
{
    jobState = JOB_STATE_DEDUCTIONS_NECESSARY;
}

void Industry::SetJobStateNormal()
{
    jobState = JOB_STATE_NORMAL;
}

void Industry::SetJobStateHarvestReady()
{
    jobState = JOB_STATE_HARVEST_READY;
}

/*
float Industry::CalculateAverageInput(int whichItem, int period)
{
    if(inputs.count(whichItem) > 0)
    {
        float result =
            inputs[whichItem]/baseProductionToComplete.at(whichItem) // consumption per "man hour"
            * period;
        return result;
    }
    else
        return 0;
}
*/

void Industry::ProgressJobPause()
{
    jobPauseTicks++;

    if(jobPauseTicks >= jobPauseThreshold)
    {
        jobPauseTicks = 0;
        pauseProgressBarNeedsRollover = true;
        SetJobStateDeductionsNecessary();
    }
}

void Industry::SetProductionPerTick(float ppt)
{
    productionPerTick = ppt;
}

void Industry::ProgressJobNormalState()
{
    productionContributed += productionPerTick;

    if(productionContributed >= productionToComplete)
    {
        productionContributed -= productionToComplete; // Excess production may roll over
        productionProgressBarNeedsRollover = true;
        SetJobStateHarvestReady();
    }
}

void Industry::UpdateProgressBar()
{
    if(jobState == JOB_STATE_INSUFFICIENT_INPUTS)
    {
        float pauseProgressBarFillAtFull = (jobPauseTicks+1)/jobPauseThreshold;
        float pauseFillRate = 1/jobPauseThreshold/Calendar::FRAMES_PER_HOUR;
        if(pauseProgressBarNeedsRollover)
        {
            pauseProgressBarFill += pauseFillRate;
            if(pauseProgressBarFill >= 1.0)
            {
                pauseProgressBarFill = 0.0;
                pauseProgressBarNeedsRollover = false;
            }
        }
        else
        {
            if(pauseProgressBarFill < pauseProgressBarFillAtFull - pauseFillRate)
                pauseProgressBarFill += pauseFillRate;
            else if(pauseProgressBarFill > pauseProgressBarFillAtFull + pauseFillRate)
                pauseProgressBarFill -= pauseFillRate;
        }

        if(pauseProgressBarFill >= 1.0)
            pauseProgressBarFill = 1.0;
        else if(pauseProgressBarFill < 0.0)
            pauseProgressBarFill = 0.0;

        remainingTimeText = "<PAUSED>";

    }

    else // jobState != JOB_STATE_INSUFFICIENT_INPUTS
    {
        //float progressFillPercentage = productionContributed/productionToComplete; // Original
        float productionProgressBarFillAtFull = (productionContributed+productionPerTick)/productionToComplete; // Updated: Progress bar "visual" is one production tick ahead of "actual"
        float progressFillRate = productionPerTick/productionToComplete/Calendar::FRAMES_PER_HOUR;
        if(productionProgressBarNeedsRollover)
        {
            productionProgressBarFill += progressFillRate;
            if(productionProgressBarFill >= 1.0)
            {
                productionProgressBarNeedsRollover = false;
                productionProgressBarFill = productionContributed/productionToComplete;
            }
        }
        else
        {
            if(productionProgressBarFill < productionProgressBarFillAtFull - progressFillRate)
                productionProgressBarFill += progressFillRate;
            else if(productionProgressBarFill > productionProgressBarFillAtFull + progressFillRate)
                productionProgressBarFill -= progressFillRate;
        }
        if(productionProgressBarFill >= 1.0)
            productionProgressBarFill = 1.0;
        else if(productionProgressBarFill < 0.0)
            productionProgressBarFill = 0.0;

        int remainingTime = (productionToComplete-productionContributed)/productionPerTick;
        int remainingTimeDays = remainingTime/Calendar::HOURS_PER_DAY;
        int remainingTimeHours = remainingTime%Calendar::HOURS_PER_DAY;

        if(remainingTimeDays > 0)
            remainingTimeText = std::to_string(remainingTimeDays) + "d " + std::to_string(remainingTimeHours) + "h";
        else
            remainingTimeText = std::to_string(remainingTimeHours) + "h";
    }

}
