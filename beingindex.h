#ifndef BEINGINDEX_H_INCLUDED
#define BEINGINDEX_H_INCLUDED

#include <map>

enum enumBeingAncestries
{
    ANCESTRY_GENERAL = -4,

    ANCESTRY_VERIT = 0,   // Hares of Verus
    ANCESTRY_YETI = 1,    // Greathares of Rumnir
    ANCESTRY_MAKHI = 2,   // Felines of Xenia
    ANCESTRY_BEYU = 3,    // Anglerfish of the thousand isles
    ANCESTRY_MESERA = 4,  // Plants of Hathsera
    ANCESTRY_ORDON = 5,   // Salamanders of Ordozaal
    ANCESTRY_HAPHAE = 6   // Avians of Haphaedee

};
const int ANCESTRY_MARKER_FIRST = ANCESTRY_VERIT;
const int ANCESTRY_MARKER_LAST = ANCESTRY_HAPHAE;
const int NUM_ANCESTRIES = ANCESTRY_MARKER_LAST+1;

const std::map<unsigned,std::string>beingAncestryNames
{
    {ANCESTRY_VERIT, "Verit"},
    {ANCESTRY_YETI, "Yeti"},
    {ANCESTRY_MAKHI, "Makhi"},
    {ANCESTRY_BEYU, "Beyu"},
    {ANCESTRY_MESERA, "Mesera"},
    {ANCESTRY_ORDON, "Ordon"},
    {ANCESTRY_HAPHAE, "Haphae"}
};

enum enumBeingActivities
{
    ACT_WALKING = 0
};

#endif // BEINGINDEX_H_INCLUDED
