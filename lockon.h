#ifndef LOCKON_H_INCLUDED
#define LOCKON_H_INCLUDED

// Forward declaration
class Place;
class Caravan;

struct LockOn
{
    static bool isLockedOn;
    static bool IsLockedOnPlace;
    static Place*whichPlace;
    static bool isLockedOnCaravan;
    static Caravan* whichCaravan;

    static void Initialize()
    {
        isLockedOn = false;
        IsLockedOnPlace = false;
        whichPlace = nullptr;
        isLockedOnCaravan = false;
        whichCaravan = nullptr;
    }
};

#endif // LOCKON_H_INCLUDED
