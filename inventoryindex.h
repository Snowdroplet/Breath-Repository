#ifndef INVENTORYINDEX_H_INCLUDED
#define INVENTORYINDEX_H_INCLUDED

#include <iostream>
#include <map>
#include <string>

#include "configuration.h"

struct InventoryIndex
{
    static constexpr int IT_NONE = -1;

    enum enumItems
    {
        IT_CORPUS  = 0, IT_PLASM  = 1, IT_OCULUS    = 2, IT_DORMANT_EGG  = 3,
        IT_BERRIES = 4, IT_HERBS  = 5, IT_MUSHROOMS = 6, IT_SPICE        = 7,
        IT_CLAY    = 8, IT_COPPER = 9, IT_IRON     = 10, IT_LEYSTONE    = 11,

        IT_BRANDY  = 12, IT_MEDICINE  = 13, IT_ETHER  = 14, IT_COUNTERAGENT = 15,
        IT_EFFIGY  = 16, IT_CONTRACT  = 17, IT_VESSEL = 18, IT_GRIMOIRE     = 19,
        IT_FUEL    = 20, IT_CLOCKWORK = 21, IT_TOOLS  = 22, IT_AUTOMATON    = 23
    };
    static const unsigned IT_MARKER_FIRST = IT_CORPUS;
    static const unsigned IT_MARKER_LAST = IT_AUTOMATON;

    static std::map<int,std::string>itemNames;

    static void LoadConfigurations()
    {
        for(unsigned i = IT_MARKER_FIRST; i <= IT_MARKER_LAST; i++)
        {
            std::string section = "cargo " + std::to_string(i);
            //std::cout << section << ": " << std::endl;
            itemNames[i] = Configuration::ReturnString(Configuration::cargoCfg, section.c_str(), "name");
            //std::cout << itemNames[i] << std::endl;
        }
    }
};

#endif // INVENTORYINDEX_H_INCLUDED
