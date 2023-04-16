#include <iostream>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_physfs.h>
#include <physfs.h>
#include "allegrocustom.h"

#include "gamestate.h"
#include "input.h"
#include "resource.h"
#include "being.h"
#include "caravan.h"
#include "road.h"
#include "place.h"
#include "overworld.h"

//Place *playerLocationPtr = nullptr;

//Caravan *playerCrew = nullptr;
Caravan *testCrew1 = nullptr;
Caravan *testCrew2 = nullptr;
Caravan *testCrew3 = nullptr;

Being *crewDetailPtr = nullptr;
Being *player = nullptr;
Being *crewZynes = nullptr;
Being *crewRukhra = nullptr;
Being *crewPurp = nullptr;
Being *crewYubi = nullptr;
Being *crewBel = nullptr;
Being *crewPaul = nullptr;
Being *crewWindow = nullptr;
Being *crewEmily = nullptr;
Being *crewLala = nullptr;

std::vector<Being*>people;
std::vector<Caravan*>caravans;
std::map<int,Place*>places;
std::map<int,Road*>roads;

void InterpretInput();
void ProgressWorld();
void ChangeUI(int whichUI, int whichSubUI, int whichTab);
//void ChangePlayerLocation(int whichLocation);

void DrawUI();

void InitObjects();
void CleanupObjects();

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    al_install_system(ALLEGRO_VERSION_INT,NULL);
    al_init_native_dialog_addon();

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        al_show_native_message_box(NULL,"Initialization Failed", "", "al_create_display() failed", NULL, 0);
        return -1;
    }

    if(!al_install_keyboard())
    {
        al_show_native_message_box(al_get_current_display(),"Initialization Failed", "", "!al_install_keyboard()", NULL, 0);
        return -1;
    }
    if(!al_install_mouse())
    {
        al_show_native_message_box(al_get_current_display(),"Initialization Failed", "", "!al_install_mouse()", NULL, 0);
        return -1;
    }

    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    FPSTimer = al_create_timer(1.0/FPS);

    eventQueue = al_create_event_queue();

    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(FPSTimer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    //al_register_event_source(eventQueue, al_get_mouse_event_source());


    PHYSFS_init(argv[0]);
    if(!PHYSFS_mount("./gamedata.zip", "/", 1))
    {
        al_show_native_message_box(al_get_current_display(),"Initialization Failed", "", "gamedata.zip not found!", NULL, 0);
        return false;
    }

    al_set_physfs_file_interface();

    AllegroCustomColours();
    LoadResources();
    InitObjects();
    //ChangePlayerLocation(PL_ERICENNES);

    ChangeUI(UI_OVERWORLD,SUB_OVERWORLD_NONE, TAB_OVERWORLD_NONE);

    al_start_timer(FPSTimer);

    while(!gameExit)
    {
        al_wait_for_event(eventQueue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            gameExit = true;

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
            InputKeydown();

        if(event.type == ALLEGRO_EVENT_KEY_UP)
            InputKeyup();

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            InterpretInput();

            ProgressWorld();

        }

        if(redraw && al_is_event_queue_empty(eventQueue))
        {
            redraw = false;

            al_clear_to_color(currentClearColor);
            DrawUI();
            al_flip_display();
        }

    }

    CleanupObjects();

    UnloadResources();

    PHYSFS_deinit();

    al_destroy_display(display);
    al_destroy_timer(FPSTimer);
    al_destroy_event_queue(eventQueue);

    al_shutdown_native_dialog_addon();
    al_uninstall_system();

    return 0;
}

void InterpretInput()
{
    if(activeUI == UI_OVERWORLD)
    {
            if(keyInput[KEY_PAD_8] || keyInput[KEY_PAD_7] || keyInput[KEY_PAD_9])
                overworldCameraYPosition -= overworldCameraYSensitivity;

            if(keyInput[KEY_PAD_2] || keyInput[KEY_PAD_1] || keyInput[KEY_PAD_3])
                overworldCameraYPosition += overworldCameraYSensitivity;

            if(keyInput[KEY_PAD_4] || keyInput[KEY_PAD_7] || keyInput[KEY_PAD_1])
                overworldCameraXPosition -= overworldCameraXSensitivity;

            if(keyInput[KEY_PAD_6] || keyInput[KEY_PAD_9] || keyInput[KEY_PAD_3])
                overworldCameraXPosition += overworldCameraXSensitivity;
    }

    if(!UIChangeDelay)
    {

        /*
        if(activeUI == UI_PLACE)
        {
            if(activeSubUI == SUB_PLACE_NONE)
            {
                if(keyInput[KEY_1])
                {
                    ChangeUI(UI_BARTER, SUB_BARTER_NONE,TAB_BARTER_ALL);
                }
                else if(keyInput[KEY_2])
                {

                }
                else if(keyInput[KEY_3])
                    ChangeUI(UI_CREW,SUB_CREW_NONE,TAB_CREW_YOUR_CREW);
            }
            else if(activeSubUI == SUB_PLACE_DEPART_CONFIRMATION)
            {
                if(keyInput[KEY_Y])
                {
                    ChangeUI(UI_TRAVEL,SUB_TRAVEL_NONE,TAB_TRAVEL_NONE);
                }
                else if(keyInput[KEY_N] || keyInput[KEY_ESC])
                {
                    activeSubUI = SUB_PLACE_NONE;
                }
            }
        }
        */

        /*
        else if(activeUI == UI_BARTER)
        {
            if(activeSubUI == SUB_BARTER_NONE)
            {
                if(keyInput[KEY_ESC])
                    ChangeUI(UI_PLACE,SUB_PLACE_NONE,TAB_PLACE_NONE);

                for(unsigned k = KEY_1; k <= KEY_7; k++)
                {
                    if(keyInput[k])
                    {
                        ChangeUI(UI_BARTER, SUB_BARTER_NONE, k-KEY_1);
                        break;
                    }
                }

                if(keyInput[KEY_LEFT])
                    barterKeyInputNPCSide = false;

                else if(keyInput[KEY_RIGHT])
                    barterKeyInputNPCSide = true;

                else if(keyInput[KEY_UP])
                {
                    // Scroll inventory up
                }
                else if(keyInput[KEY_DOWN])
                {
                    // Scroll inventory down
                }

                for(unsigned k = KEY_A; k <= KEY_T; k++)
                {
                    if(keyInput[k])
                    {
                        if(barterKeyInputNPCSide)
                        {
                            barterItemType = playerLocationPtr->inventory.GetItemTypeAtInput(k-KEY_A);
                        }
                        else
                        {
                            barterItemType = playerCrew->inventory.GetItemTypeAtInput(k-KEY_A);
                        }

                        if(barterItemType != IT_NONE)
                        {
                            ChangeUI(UI_BARTER, SUB_BARTER_QUANTITY, activeTab);
                        }
                    }
                }


            }
            else if(activeSubUI == SUB_BARTER_QUANTITY)
            {
                if(keyInput[KEY_ESC])
                {
                    ChangeUI(UI_BARTER, SUB_BARTER_NONE, activeTab);
                }
                if(keyInput[KEY_UP])
                {
                    barterItemQuantity ++;
                }
                else if(keyInput[KEY_DOWN])
                {
                    barterItemQuantity --;
                }
                else if(keyInput[KEY_LEFT])
                {
                    barterItemQuantity -= 5;
                }
                else if(keyInput[KEY_RIGHT])
                {
                    barterItemQuantity += 5;
                }

            }
        }
        */

        /*
        else if(activeUI == UI_CREW)
        {
            if(keyInput[KEY_ESC])
            {
                if(playerAtPlace)
                    ChangeUI(UI_PLACE,SUB_PLACE_NONE,TAB_PLACE_NONE);
                else
                    ChangeUI(UI_TRAVEL,SUB_TRAVEL_NONE,TAB_TRAVEL_NONE);
            }

            else if(keyInput[KEY_1])
                activeTab = TAB_CREW_YOUR_CREW;

            else if(keyInput[KEY_2])
                activeTab = TAB_CREW_AVAILABLE;

            else
            {
                for(unsigned k = KEY_A; k < KEY_J; k++) // 0-10
                {
                    if(keyInput[k])
                    {
                        if(activeTab == TAB_CREW_YOUR_CREW && k < playerCrew->members.size())
                        {
                            ChangeUI(UI_CREW_DETAILED, SUB_CREW_DETAILED_NONE, TAB_CREW_DETAILED_NONE);

                            crewDetailPtr = playerCrew->members[k];
                        }

                        else if(activeTab == TAB_CREW_AVAILABLE && k < playerLocationPtr->availableCrew.size())
                        {
                            ChangeUI(UI_CREW_DETAILED, SUB_CREW_DETAILED_NONE, TAB_CREW_DETAILED_NONE);

                            crewDetailPtr = playerLocationPtr->availableCrew[k];
                        }

                        break;
                    }
                }
            }
        }

        else if(activeUI == UI_CREW_DETAILED)
        {
            if(keyInput[KEY_ESC])
            {
                ChangeUI(UI_CREW, SUB_CREW_NONE, previousActiveTab);
                crewDetailPtr = nullptr;
            }
        }
        */


    }
    else
        UIChangeDelay = false;
}

void ProgressWorld()
{
    if(activeUI == UI_OVERWORLD)
    {
        for(std::map<int,Place*>::iterator it = places.begin(); it != places.end(); it++)
        {

        }

        for(std::map<int,Road*>::iterator it = roads.begin(); it != roads.end(); it++)
        {

        }

        for(std::vector<Being*>::iterator it = people.begin(); it != people.end(); it++)
        {

        }

        for(std::vector<Caravan*>::iterator it = caravans.begin(); it != caravans.end(); it++)
        {
            (*it)->Travel();
            /// Here: If caravan is atRoadsEnd, move it to the Place corresponding to its Road's endpointA or B
        }
    }

}


void ChangeUI(int whichUI, int whichSubUI, int whichTab)
{
    UIChangeDelay = true;

    if(whichUI != activeUI)
        previousActiveUI = activeUI;
    if(whichSubUI != activeSubUI)
        previousActiveSubUI = activeSubUI;
    if(whichTab != activeTab)
        previousActiveTab = activeTab;

    activeUI = whichUI;
    activeSubUI = whichSubUI;
    activeTab = whichTab;

    if(activeUI == UI_OVERWORLD)
    {
        currentClearColor = COL_LIGHT_GREEN;
    }

    /*
    if(activeUI == UI_BARTER)
    {
        playerCrew->inventory.RefreshCargoInTab();
        playerLocationPtr->inventory.RefreshCargoInTab();
    }
    */
}


/*
void ChangePlayerLocation(int whichLocation)
{
    if(whichLocation != PL_NONE)
        playerAtPlace = true;

    playerLocation = whichLocation;
    playerLocationPtr = places[whichLocation];
}
*/

void DrawUI()
{
    if(activeUI == UI_OVERWORLD)
    {
        DrawOverworldDebugOverlay();

        for(unsigned i = 0; i < places.size(); i++)
            places[i]->DrawOnOverworld();

        for(unsigned i = 0; i < roads.size(); i++)
            roads[i]->DrawOnOverworld();

        for(unsigned i = 0; i < caravans.size(); i++)
            caravans[i]->DrawOnOverworld();
    }
    /*
    else if(activeUI == UI_PLACE)
    {
        if(activeSubUI == SUB_PLACE_NONE)
        {
            al_draw_bitmap(placePng[playerLocation],0,0,0);

            al_draw_text(builtin, al_map_rgb(0,0,0),
                         UI_PLACE_NAME_CENTRE_X,
                         UI_PLACE_NAME_CENTRE_Y,
                         ALLEGRO_ALIGN_CENTER,
                         UIPlaceNames[playerLocation].c_str());

            for(int i = 0; i < UI_PLACE_NUM_BUTTONS; i++)
            {
                al_draw_bitmap(UIPlaceButtonPng,
                               UI_PLACE_BUTTON_X,
                               UI_PLACE_BUTTON_Y + i*UI_PLACE_BUTTON_Y_SPACING,
                               0);
                al_draw_text(builtin, al_map_rgb(0,0,0),
                             UI_PLACE_BUTTON_CENTRE_X,
                             UI_PLACE_BUTTON_CENTRE_Y + i*UI_PLACE_BUTTON_Y_SPACING,
                             ALLEGRO_ALIGN_CENTER,
                             UIPlaceButtonLabels[i].c_str());
            }
        }
        else if(activeSubUI == SUB_PLACE_DEPART_CONFIRMATION)
        {

        }

    }

    else if(activeUI == UI_BARTER)
    {
        for(int i = 0; i < UI_BARTER_NUM_TABS; i++)
        {
            if(i == activeTab)
                al_draw_bitmap(UIBarterTabPng[PNG_ACTIVE],
                               UI_BARTER_TAB_X + i*UI_BARTER_TAB_X_SPACING,
                               UI_BARTER_TAB_Y,
                               0);

            else
                al_draw_bitmap(UIBarterTabPng[PNG_INACTIVE],
                               UI_BARTER_TAB_X + i*UI_BARTER_TAB_X_SPACING,
                               UI_BARTER_TAB_Y,
                               0);

            al_draw_text(builtin, al_map_rgb(0,0,0),
                         UI_BARTER_TAB_CENTRE_X + i*UI_BARTER_TAB_X_SPACING,
                         UI_BARTER_TAB_CENTRE_Y,
                         ALLEGRO_ALIGN_CENTRE,
                         UIBarterTabLabels[i].c_str());



            playerCrew->inventory.DrawVertical(UI_BARTER_INVENTORY_ROWS, UI_BARTER_INVENTORY_1_X, UI_BARTER_INVENTORY_1_Y);

            playerLocationPtr->inventory.DrawVertical(UI_BARTER_INVENTORY_ROWS, UI_BARTER_INVENTORY_2_X, UI_BARTER_INVENTORY_2_Y);

        }

        if(activeSubUI == SUB_BARTER_QUANTITY)
        {
            //al_draw_text(builtin, al_map_rgb(0,0,0),
                       //  UI_BARTER_QUANTITY_)
        }
    }

    else if(activeUI == UI_CREW)
    {
        for(int i = 0; i < UI_CREW_NUM_TABS; i++)
        {
            if(i == activeTab)
                al_draw_bitmap(UICrewTabPng[PNG_ACTIVE],
                               UI_CREW_TAB_X + i*UI_CREW_TAB_X_SPACING,
                               UI_CREW_TAB_Y,
                               0);
            else
                al_draw_bitmap(UICrewTabPng[PNG_INACTIVE],
                               UI_CREW_TAB_X + i*UI_CREW_TAB_X_SPACING,
                               UI_CREW_TAB_Y,
                               0);


            al_draw_text(builtin, al_map_rgb(0,0,0),
                         UI_CREW_TAB_CENTRE_X + i*UI_CREW_TAB_X_SPACING,
                         UI_CREW_TAB_CENTRE_Y,
                         ALLEGRO_ALIGN_CENTRE,
                         UICrewTabLabels[i].c_str());
        }

        if(activeTab == TAB_CREW_YOUR_CREW)
        {
            for(unsigned i = 0; i < playerCrew->members.size(); i++)
            {
                Being*member = playerCrew->members[i];
                member->DrawPortrait(UI_CREW_PORTRAIT_X, UI_CREW_PORTRAIT_Y + i*UI_CREW_PORTRAIT_Y_SPACING);

                member->DrawName(UI_CREW_NAME_X, UI_CREW_NAME_Y + i*UI_CREW_NAME_Y_SPACING, 0);

                member->DrawSkills(UI_CREW_SKILL_SQUARE_X, UI_CREW_SKILL_SQUARE_Y + i*UI_CREW_SKILL_SQUARE_Y_SPACING);

            }
        }
        else if(activeTab == TAB_CREW_AVAILABLE)
        {
            for(unsigned i = 0; i < playerLocationPtr->availableCrew.size(); i++)
            {
                Being*candidate = playerLocationPtr->availableCrew[i];
                candidate->DrawPortrait(UI_CREW_PORTRAIT_X, UI_CREW_PORTRAIT_Y + i*UI_CREW_PORTRAIT_Y_SPACING);

                candidate->DrawName(UI_CREW_NAME_X, UI_CREW_NAME_Y + i*UI_CREW_NAME_Y_SPACING, 0);

                candidate->DrawSkills(UI_CREW_SKILL_SQUARE_X, UI_CREW_SKILL_SQUARE_Y + i*UI_CREW_SKILL_SQUARE_Y_SPACING);
            }
        }
    }

    else if(activeUI == UI_CREW_DETAILED)
    {
        crewDetailPtr->DrawPortrait(UI_CREW_DETAILED_PORTRAIT_X - BEING_PORTRAIT_W/2, UI_CREW_DETAILED_PORTRAIT_Y - BEING_PORTRAIT_H/2);
        crewDetailPtr->DrawName(UI_CREW_DETAILED_NAME_X, UI_CREW_DETAILED_NAME_Y, ALLEGRO_ALIGN_CENTRE);
        crewDetailPtr->DrawSkillsDetailed(UI_CREW_DETAILED_SKILL_SQUARE_X, UI_CREW_DETAILED_SKILL_SQUARE_Y);
    }
    */
}

void InitObjects()
{
    for(unsigned i = PL_MARKER_FIRST; i <= PL_MARKER_LAST; i++)
        places[i] = new Place(i);

    for(unsigned i = ROAD_MARKER_FIRST; i <= ROAD_MARKER_LAST; i++)
        roads[i] = new Road(i);


    /*
    playerCrew = new Caravan;
    caravans.push_back(playerCrew);
    */

    testCrew1 = new Caravan;
    testCrew2 = new Caravan;
    testCrew3 = new Caravan;

    /*
    player = new Being;
    player->SetName("Player");
    player->SetRace(RACE_VERIT);
    player->SetPortrait(RACE_VERIT,1);
    people.push_back(player);
    */

    crewZynes = new Being;
    crewZynes->SetName("Test Verit Zynes");
    crewZynes->SetRace(RACE_VERIT);
    //crewZynes->SetPortrait(RACE_VERIT,0);
    people.push_back(crewZynes);

    crewRukhra = new Being;
    crewRukhra->SetName("Test Haphae Rukhra");
    crewRukhra->SetRace(RACE_HAPHAE);
    //crewRukhra->SetPortrait(RACE_HAPHAE,0);
    people.push_back(crewRukhra);

    crewPurp = new Being;
    crewPurp->SetName("Test Verit Purp");
    crewPurp->SetRace(RACE_VERIT);
    //crewPurp->SetPortrait(RACE_VERIT,2);
    people.push_back(crewPurp);

    crewYubi = new Being;
    crewYubi->SetName("Test Beyu Yubi");
    crewYubi->SetRace(RACE_BEYU);
    //crewYubi->SetPortrait(RACE_BEYU,2);
    people.push_back(crewYubi);

///

    crewBel = new Being;
    crewBel->SetName ("Test Ordon Bel");
    crewBel->SetRace (RACE_ORDON);
    //crewBel->SetPortrait(RACE_ORDON,2);
    people.push_back(crewBel);

    crewWindow = new Being;
    crewWindow->SetName ("Test Makhi Window");
    crewWindow->SetRace (RACE_MAKHI);
    //crewWindow->SetPortrait(RACE_MAKHI,0);
    //crewWindow->SetSkill(SK_MECHANIC, 1);
    people.push_back(crewWindow);

    crewPaul = new Being;
    crewPaul->SetName("Test Makhi Paul");
    crewPaul->SetRace(RACE_MAKHI);
    //crewPaul->SetPortrait(RACE_MAKHI,2);
    people.push_back(crewPaul);

    crewEmily = new Being;
    crewEmily->SetName("Test Yeti Emily");
    crewEmily->SetRace(RACE_YETI);
    //crewEmily->SetPortrait(RACE_YETI,1);
    people.push_back(crewEmily);

    crewLala = new Being;
    crewLala->SetName("Test Beyu Lala");
    crewLala->SetRace(RACE_BEYU);
    //crewLala->SetPortrait(RACE_BEYU,1);
    people.push_back(crewLala);


    //playerCrew->AddMember(player);

    testCrew1->AddMember(crewZynes);
    testCrew1->AddMember(crewRukhra);
    testCrew1->AddMember(crewPurp);
    caravans.push_back(testCrew1);


    /*
    testCrew2->AddMember(crewYubi);
    testCrew2->AddMember(crewBel);
    caravans.push_back(testCrew2);

    testCrew3->AddMember(crewWindow);
    testCrew3->AddMember(crewPaul);
    testCrew3->AddMember(crewEmily);
    testCrew3->AddMember(crewLala);
    caravans.push_back(testCrew3);
    */

    testCrew1->MoveToRoad(roads[ROAD_ERICENNES_CHORAS],false);

    //ericennes->AddAvailableCrew(crewLala);

    //playerCrew->inventory.SetStock(IT_RICE, 10);
    //playerCrew->inventory.SetStock(IT_WAYBREAD, 2);

    //ericennes->inventory.SetStock(IT_RICE, 10);
    //ericennes->inventory.SetStock(IT_BEAST_FLESH, 4);
    //ericennes->inventory.SetStock(IT_SALVE, 4);
    //ericennes->inventory.SetStock(IT_LEYPOST, 5);

}

void CleanupObjects()
{

    for(std::vector<Being*>::iterator it = people.begin(); it != people.end();)
    {
        delete *it;
        people.erase(it);
    }

    for(std::vector<Caravan*>::iterator it = caravans.begin(); it != caravans.end();)
    {
        delete *it;
        caravans.erase(it);
    }

    for(std::map<int,Place*>::iterator it = places.begin(); it != places.end(); ++it)
        delete it->second;
    places.clear();

    for(std::map<int, Road*>::iterator it = roads.begin(); it != roads.end(); ++it)
        delete it->second;
    roads.clear();
}
