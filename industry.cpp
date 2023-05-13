#include "industry.h"

Industry::Industry(int id, float baseProd)
{
    jobActive = false;
    jobActivationPaused = false;
    jobActivationPauseTicks = 0;
    jobComplete = false;
    jobRepeating = true;
    industryName = industryNames.at(id);

    inputMultiplier = 1.0;
    outputMultiplier = 1.0;

    productionMultiplier = 1.0;
    productionContributed = 0;
    productionToComplete = baseProductionToComplete.at(id);
    SetBaseProductionPerTick(baseProd);

    switch(id)
    {
    case IND_HUNT_MEAT:
        outputs[IT_MEAT] = 10;
        expertiseType = EXP_HUNT;
        expertiseLevelRequired = 1;
        break;

    case IND_HUNT_COLD_BLOOD:
        outputs[IT_COLD_BLOOD] = 6;
        expertiseType = EXP_HUNT;
        expertiseLevelRequired = 2;
        break;

    case IND_ALCHEMY_CONTRACT:
        inputs[IT_COLD_BLOOD] = 4;
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
}

Industry::~Industry()
{

}

void Industry::PauseJobActivation(int ticks)
{
    jobActivationPaused = true;
    jobActivationPauseTicks = ticks;
}

void Industry::CountdownPausedJobActivation(int ticks)
{
    jobActivationPauseTicks -= ticks;
    if(jobActivationPauseTicks <= 0)
    {
        jobActivationPauseTicks = 0;
        jobActivationPaused = false;
    }
}

void Industry::SetBaseProductionPerTick(float bppt)
{
    baseProductionPerTick = bppt;
}

void Industry::ProgressJob()
{
        jobComplete = false;

        //Todo: productionContributed += the number and quality of workers
        productionContributed += baseProductionPerTick;

        //std::cout << productionContributed << "/" << productionToComplete << std::endl;

        if(productionContributed >= productionToComplete)
        {
            productionContributed -= productionToComplete; // Excess production may roll over
            jobComplete = true;
            jobActive = false;

            //std::cout << "job completed" << std::endl;
        }
}
