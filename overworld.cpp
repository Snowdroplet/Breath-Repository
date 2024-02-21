#include "overworld.h"

int overworldParallelSampleInstanceCurrentPart;

/// Audio functions
void OverworldAudioUpdate()
{

    if(overworldParallelSampleInstanceCurrentPart == OPS_COTTAGES)
    {
        if(al_get_sample_instance_gain(Resource::cottagesSampleInstance) < 1.0)
            al_set_sample_instance_gain(Resource::cottagesSampleInstance, al_get_sample_instance_gain(Resource::cottagesSampleInstance) + 0.05);

        if(al_get_sample_instance_gain(Resource::manorSampleInstance) > 0.0)
            al_set_sample_instance_gain(Resource::manorSampleInstance, al_get_sample_instance_gain(Resource::manorSampleInstance) - 0.05);
    }

    if(overworldParallelSampleInstanceCurrentPart == OPS_MANOR) // Don't else if
    {
        if(al_get_sample_instance_gain(Resource::manorSampleInstance) < 1.0)
            al_set_sample_instance_gain(Resource::manorSampleInstance, al_get_sample_instance_gain(Resource::manorSampleInstance) + 0.05);

        if(al_get_sample_instance_gain(Resource::cottagesSampleInstance) > 0.0)
            al_set_sample_instance_gain(Resource::cottagesSampleInstance, al_get_sample_instance_gain(Resource::cottagesSampleInstance) - 0.05);
    }

}

void OverworldBeginParallelBackgroundAudio()
{
    al_set_sample_instance_playmode(Resource::cottagesSampleInstance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(Resource::manorSampleInstance, ALLEGRO_PLAYMODE_LOOP);

    al_set_sample_instance_gain(Resource::cottagesSampleInstance, 0.0);
    al_set_sample_instance_gain(Resource::manorSampleInstance, 0.0);

    al_play_sample_instance(Resource::cottagesSampleInstance);
    al_play_sample_instance(Resource::manorSampleInstance);

    overworldParallelSampleInstanceCurrentPart = OPS_COTTAGES;
}

void OverworldEndParallelBackgroundAudio()
{
    al_stop_sample_instance(Resource::cottagesSampleInstance);
    al_stop_sample_instance(Resource::manorSampleInstance);
}

void OverworldSwapParallelBackgroundAudioToPlace()
{
    overworldParallelSampleInstanceCurrentPart = OPS_MANOR;
}

void OverworldSwapParallelBackgroundAudioToField()
{
    overworldParallelSampleInstanceCurrentPart = OPS_COTTAGES;
}
