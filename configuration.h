#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include <allegro5/allegro5.h>

#include <iostream>
#include <sstream>

struct Configuration
{
    static ALLEGRO_CONFIG* cargoCfg;
    static ALLEGRO_CONFIG* placeCfg;

    static void LoadConfigurations()
    {
        al_set_standard_file_interface();
        cargoCfg = al_load_config_file("configurations/cargoCfg.cfg");
        if(!cargoCfg)
            std::cout << "beep boop cargo" << std::endl;
        placeCfg = al_load_config_file("configurations/placeCfg.cfg");
        if(!placeCfg)
            std::cout << "beep boop place" << std::endl;

    }

    static void UnloadConfigurations()
    {
        al_destroy_config(cargoCfg);
        al_destroy_config(placeCfg);
    }


    static std::string ReturnString(const ALLEGRO_CONFIG* config, const char* section, const char* key)
    {
        return al_get_config_value(config, section, key);
    }

    static int ReturnInt(const ALLEGRO_CONFIG* config, const char* section, const char* key)
    {
        std::stringstream strValue;
        strValue << al_get_config_value(config, section, key);

        int intValue;
        strValue >> intValue;

        return intValue;
    }

};

#endif // CONFIGURATION_H_INCLUDED
