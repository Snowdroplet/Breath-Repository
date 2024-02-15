#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

struct Scene
{
    enum enumScenes
    {
        SCENE_OVERWORLD
    };
    static int activeScene;
    static int previousActiveScene;

    enum enumSubScenes
    {
        SUBSCENE_OVERWORLD_NONE = -1,

        SUBSCENE_ENCYCLOPEDIA = 0
    };
    static int activeSubscene;
    static int previousActiveSubscene;

    static void Initialize()
    {
        activeScene = SCENE_OVERWORLD;
        previousActiveScene = SCENE_OVERWORLD;

        activeSubscene = SUBSCENE_OVERWORLD_NONE;
        previousActiveSubscene = SUBSCENE_OVERWORLD_NONE;
    }

    static void ChangeScene(int whichScene, int whichSubscene)
    {
        if(whichScene != activeScene)
            previousActiveScene = activeScene;
        if(whichSubscene != activeSubscene)
            previousActiveSubscene = activeSubscene;

        activeScene = whichScene;
        activeSubscene = whichSubscene;
    }

};

#endif // SCENE_H_INCLUDED
