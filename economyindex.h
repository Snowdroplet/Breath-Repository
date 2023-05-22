#ifndef ECONOMYINDEX_H_INCLUDED
#define ECONOMYINDEX_H_INCLUDED

#include <array>
#include <map>

#include "inventoryindex.h"

enum enumConsumptionTier
{
    CON_TIER_DESTITUTE = 0,   // City has < 0.5x its maitainence
    CON_TIER_POOR = 1,        // City has < 1x of its maintainence
    CON_TIER_COMFORTABLE = 2, // City has 1x of its maintainence
    CON_TIER_WEALTHY = 3,     // City has 3x of its maintainence
    CON_TIER_PROFLIGATE = 4   // City has 10x of its maintaienece
};

const std::map<int, std::array<float,5>>baseMaintainenceConsumption = // Also known as "household consumption" or whatever, as opposed to industrial consumption
{                    // D    P    C     W     P
    {IT_MEAT,        { 0.0, 0.0, 2.0,  0.0,  0.0}},
    {IT_COLD_BREATH, { 0.0, 0.0, 0.0,  0.0,  0.0}},
    {IT_CONTRACT,    { 0.0, 0.0, 0.5,  0.0,  0.0}},
    {IT_SPELLBOOK,   { 0.0, 0.0, 0.0,  0.0,  0.0}},
    {IT_RICE,        { 0.0, 0.0, 7.0,  0.0,  0.0}},
    {IT_ALCOHOL,     { 0.0, 0.0, 1.0,  0.0,  0.0}},
    {IT_MUSHROOMS,   { 0.0, 0.0, 4.0,  0.0,  0.0}},
    {IT_HERBS,       { 0.0, 0.0, 0.5,  0.0,  0.0}},
    {IT_MEDICINE,    { 0.0, 0.0, 0.5,  0.0,  0.0}},
    {IT_SPICE,       { 0.0, 0.0, 0.0,  0.0,  0.0}},
    {IT_CLAY,        { 0.0, 0.0, 0.5,  0.0,  0.0}},
    {IT_POTTERY,     { 0.0, 0.0, 1.0,  0.0,  0.0}},
    {IT_SILVER,      { 0.0, 0.0, 0.0,  0.0,  0.0}},
    {IT_JEWELRY,     { 0.0, 0.0, 0.0,  0.0,  0.0}},
    {IT_LEYSTONE,    { 0.0, 0.0, 0.0,  0.0,  0.0}},
    {IT_CLOCKWORK,   { 0.0, 0.0, 0.0,  0.0,  0.0}},
    {IT_AUTOMATON,   { 0.0, 0.0, 0.0,  0.0,  0.0}}
};

/// Better just keep a blank copy of the array around just in case
/*
     IT_MEAT,        { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_COLD_BREATH, { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_CONTRACT,    { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_SPELLBOOK,   { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_RICE,        { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_ALCOHOL,     { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_MUSHROOMS,   { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_HERBS,       { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_MEDICINE,    { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_SPICE,       { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_CLAY,        { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_POTTERY,     { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_SILVER,      { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_JEWELRY,     { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_LEYSTONE,    { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_CLOCKWORK,   { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_AUTOMATON,   { 0.0, 0.0, 0.0, 0.0, 0.0}}
*/

#endif // ECONOMYINDEX_H_INCLUDED
