#include "industry.h"

Industry::Industry(int id, float ppt)
{
    jobState = JOB_STATE_INSUFFICIENT_INPUTS;
    jobPauseTicks = 0;

    industryName = industryNames.at(id);

    inputMultiplier = 1.0;
    outputMultiplier = 1.0;

    productionMultiplier = 1.0;
    productionContributed = 0;
    productionToComplete = baseProductionToComplete.at(id);
    SetProductionPerTick(ppt);

    switch(id)
    {
    case IND_HUNT_MEAT:
        outputs[IT_MEAT] = 10;
        expertiseType = EXP_HUNT;
        expertiseLevelRequired = 1;
        break;

    case IND_HUNT_COLD_BREATH:
        outputs[IT_COLD_BREATH] = 6;
        expertiseType = EXP_HUNT;
        expertiseLevelRequired = 2;
        break;

    case IND_ALCHEMY_CONTRACT:
        inputs[IT_COLD_BREATH] = 4;
        outputs[IT_CONTRACT] = 1;
        expertiseType = EXP_ALCHEMY;
        expertiseLevelRequired = 3;
        break;

    case IND_ALCHEMY_SPELLBOOK:
        inputs[IT_CONTRACT] = 6;
        outputs[IT_SPELLBOOK] = 1;
        expertiseType = EXP_ALCHEMY;
        expertiseLevelRequired = 4;
        break;

    case IND_FARM_RICE:
        outputs[IT_RICE] = 50;
        expertiseType = EXP_FARM;
        expertiseLevelRequired = 1;
        break;

    case IND_ALCHEMY_ALCOHOL:
        inputs[IT_RICE] = 30;
        outputs[IT_ALCOHOL] = 25;
        expertiseType = EXP_ALCHEMY;
        expertiseLevelRequired = 1;
        break;

    case IND_FARM_MUSHROOMS:
        outputs[IT_MUSHROOMS] = 30;
        expertiseType = EXP_FARM;
        expertiseLevelRequired = 2;
        break;

    case IND_FARM_HERBS:
        outputs[IT_HERBS] = 20;
        expertiseType = EXP_FARM;
        break;

    case IND_ALCHEMY_MEDICINE:
        inputs[IT_HERBS] = 2;
        outputs[IT_MEDICINE] = 2;
        expertiseType = EXP_ALCHEMY;
        expertiseLevelRequired = 3;
        break;

    case IND_FARM_SPICE:
        outputs[IT_SPICE] = 10;
        expertiseType = EXP_FARM;
        expertiseLevelRequired = 4;
        break;

    case IND_MINE_CLAY:
        outputs[IT_CLAY] = 10;
        expertiseType = EXP_MINE;
        expertiseLevelRequired = 1;
        break;

    case IND_CRAFT_POTTERY:
        inputs[IT_CLAY] = 4;
        outputs[IT_POTTERY] = 1;
        expertiseType = EXP_CRAFT;
        expertiseLevelRequired = 1;
        break;

    case IND_MINE_SILVER:
        outputs[IT_SILVER] = 5;
        expertiseType = EXP_MINE;
        expertiseLevelRequired = 2;
        break;

    case IND_CRAFT_JEWELRY:
        inputs[IT_SILVER] = 2;
        outputs[IT_JEWELRY] = 1;
        expertiseType = EXP_CRAFT;
        expertiseLevelRequired = 2;
        break;

    case IND_MINE_LEYSTONE:
        outputs[IT_LEYSTONE] = 6;
        expertiseType = EXP_MINE;
        expertiseLevelRequired = 3;
        productionToComplete = 88;
        break;

    case IND_CRAFT_CLOCKWORK:
        inputs[IT_LEYSTONE] = 5;
        outputs[IT_CLOCKWORK] = 10;
        expertiseType = EXP_CRAFT;
        expertiseLevelRequired = 3;
        break;

    case IND_CRAFT_AUTOMATON:
        inputs[IT_CLOCKWORK] = 50;
        outputs[IT_AUTOMATON] = 1;
        expertiseType = EXP_CRAFT;
        expertiseLevelRequired = 4;
        break;
    }

    pauseProgressBarFill = jobPauseTicks/jobPauseThreshold;
    pauseProgressBarNeedsRollover = false;

    productionProgressBarFill = productionContributed/productionToComplete;
    productionProgressBarNeedsRollover = false;
}

Industry::~Industry()
{

}

void Industry::SetJobStateInsufficientInputs(int thresh)
{
    jobState = JOB_STATE_INSUFFICIENT_INPUTS;

    jobPauseTicks = 0;
    jobPauseThreshold = thresh;
}

void Industry::SetJobStateDeductionsNecessary()
{
    jobState = JOB_STATE_DEDUCTIONS_NECESSARY;
}

void Industry::SetJobStateNormal()
{
    jobState = JOB_STATE_NORMAL;

    jobPauseTicks = 0;
    jobPauseThreshold = 0;
}

void Industry::SetJobStateHarvestReady()
{
    jobState = JOB_STATE_HARVEST_READY;
}

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

    float progressFillPercentage = productionContributed/productionToComplete;
    float progressFillRate = productionPerTick/productionToComplete/FRAMES_PER_HOUR;
    if(productionProgressBarNeedsRollover)
    {
        productionProgressBarFill += progressFillRate;
        if(productionProgressBarFill >= 1.0)
        {
            productionProgressBarFill = 0.0;
            productionProgressBarNeedsRollover = false;
        }
    }
    else
    {
        if(productionProgressBarFill < progressFillPercentage - progressFillRate)
            productionProgressBarFill += progressFillRate;
        else if(productionProgressBarFill > progressFillPercentage +progressFillRate)
            productionProgressBarFill -= progressFillRate;
    }
    if(productionProgressBarFill >= 1.0)
        productionProgressBarFill = 1.0;
    else if(productionProgressBarFill < 0.0)
        productionProgressBarFill = 0.0;



    if(jobState == JOB_STATE_INSUFFICIENT_INPUTS)
    {
        float pauseFillPercentage = jobPauseTicks/jobPauseThreshold;
        float pauseFillRate = 1/jobPauseThreshold/FRAMES_PER_HOUR;
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
            if(pauseProgressBarFill < pauseFillPercentage - pauseFillRate)
                pauseProgressBarFill += pauseFillRate;
            else if(pauseProgressBarFill > pauseFillPercentage + pauseFillRate)
                pauseProgressBarFill -= pauseFillRate;
        }

        if(pauseProgressBarFill >= 1.0)
            pauseProgressBarFill = 1.0;
        else if(pauseProgressBarFill < 0.0)
            pauseProgressBarFill = 0.0;
    }
}
