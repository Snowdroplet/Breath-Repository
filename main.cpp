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
#include "calendar.h"

//Place *playerLocationPtr = nullptr;
//Caravan *playerCrew = nullptr;

void InterpretInput();
void ProgressWorld();
void UpdateUI();

void ChangeUI(int whichUI, int whichSubUI, int whichTab);
//void ChangePlayerLocation(int whichLocation);

void DrawUI();

void InitObjects();
void CleanupObjects();

int main(int argc, char *argv[])
{
    srand(time(NULL));

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
    InitCalendar(22,30,12,2023);

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
            UpdateUI();
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
        if(!overworldCameraLocked)
        {
            if(keyInput[KEY_PAD_8] || keyInput[KEY_PAD_7] || keyInput[KEY_PAD_9])
                overworldCameraYPosition -= overworldCameraYSensitivity;

            if(keyInput[KEY_PAD_2] || keyInput[KEY_PAD_1] || keyInput[KEY_PAD_3])
                overworldCameraYPosition += overworldCameraYSensitivity;

            if(keyInput[KEY_PAD_4] || keyInput[KEY_PAD_7] || keyInput[KEY_PAD_1])
                overworldCameraXPosition -= overworldCameraXSensitivity;

            if(keyInput[KEY_PAD_6] || keyInput[KEY_PAD_9] || keyInput[KEY_PAD_3])
                overworldCameraXPosition += overworldCameraXSensitivity;

            if(keyInput[KEY_SPACE])
            {
                for(std::vector<Caravan*>::iterator it = Caravan::caravans.begin(); it != Caravan::caravans.end(); ++it)
                {
                    float x = (*it)->overworldXPosition;
                    float y = (*it)->overworldYPosition;
                    float w = (*it)->caravanLeader->spriteWidth;
                    float h = (*it)->caravanLeader->spriteHeight;

                    if((overworldCameraXPosition + SCREEN_W/2) > x - w/2
                            && (overworldCameraXPosition + SCREEN_W/2) < x + w/2
                            && (overworldCameraYPosition + SCREEN_H/2) > y - h/2
                            && (overworldCameraYPosition + SCREEN_H/2) < y + h/2)
                    {
                        OverworldLockCameraCaravan(*it);
                        break;
                    }
                }

                for(std::map<int,Place*>::iterator it = Place::places.begin(); it != Place::places.end(); ++it)
                {
                    float x = (*it).second->overworldXPosition;
                    float y = (*it).second->overworldYPosition;
                    float w = Place::OVERWORLD_SPRITE_W;
                    float h = Place::OVERWORLD_SPRITE_H;

                    if((overworldCameraXPosition + SCREEN_W/2) > x - w/2
                            && (overworldCameraXPosition + SCREEN_W/2) < x + w/2
                            && (overworldCameraYPosition + SCREEN_H/2) > y - h/2
                            && (overworldCameraYPosition + SCREEN_H/2) < y + h/2)
                    {
                        OverworldLockCameraPlace((*it).second);
                        (*it).second->UpdateAllBubbles();
                        break;
                    }
                }
            }
        }
        else if(overworldCameraLocked)
        {
            if(keyInput[KEY_ESC])
                OverworldUnlockCamera();
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
}

void ProgressWorld()
{
    if(activeUI == UI_OVERWORLD)
    {
        AdvanceHourFrame();
        UpdateCalendarText();

        for(std::map<int,Place*>::iterator it = Place::places.begin(); it != Place::places.end(); ++it)
        {
            ((*it).second)->ProgressFlyingTexts();
            ((*it).second)->ProgressIndustriesBubbleProgressBars();

            if(hourChangeTick)
            {
                ((*it).second)->ProgressProduction();
                ((*it).second)->ProgressMaintainenceConsumption();

                ((*it).second)->UpdateSurplusesTopTen();
                ((*it).second)->UpdateDeficitsTopTen();
            }

            /*
            if(dayChangeTick)
            {
                ((*it).second)->UpdateEconomyData();
            }
            */


        }

        for(std::map<int,Road*>::iterator it = Road::roads.begin(); it != Road::roads.end(); ++it)
        {

        }

        for(std::vector<Being*>::iterator it = Being::people.begin(); it != Being::people.end(); ++it)
        {
            (*it)->Progress();

        }

        for(std::vector<Caravan*>::iterator it = Caravan::caravans.begin(); it != Caravan::caravans.end(); ++it)
        {
            (*it)->OverworldLogic();
        }
    }

}

void UpdateUI()
{
    if(activeUI == UI_OVERWORLD)
    {
        if(overworldCameraLocked)
        {
            if(overworldCameraLockedOnPlace)
            {
                overworldCameraXPosition = overworldCameraPlace->overworldXPosition-SCREEN_W/2;
                overworldCameraYPosition = overworldCameraPlace->overworldYPosition-SCREEN_H/2;
            }
            else if(overworldCameraLockedOnCaravan)
            {
                overworldCameraXPosition = overworldCameraCaravan->overworldXPosition-SCREEN_W/2;
                overworldCameraYPosition = overworldCameraCaravan->overworldYPosition-SCREEN_H/2;
            }
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
    playerLocationPtr = Place::places[whichLocation];
}
*/

void DrawUI()
{
    if(activeUI == UI_OVERWORLD)
    {
        OverworldDrawGridUnderlay();

        for(unsigned i = 0; i < Place::places.size(); i++)
            Place::places[i]->DrawSpriteOnOverworld();

        for(unsigned i = 0; i < Road::roads.size(); i++)
            Road::roads[i]->DrawSegmentsOnOverworld();

        for(unsigned i = 0; i < Caravan::caravans.size(); i++)
            Caravan::caravans[i]->DrawSpriteOnOverworld();

        for(std::map<int, Place*>::iterator it = Place::places.begin(); it != Place::places.end(); ++it)
            (*it).second->DrawCaravanseraiBubbleOnOverworld();

        for(std::map<int, Place*>::iterator it = Place::places.begin(); it != Place::places.end(); ++it)
            (*it).second->DrawFlyingTexts();

        if(overworldCameraPlace != nullptr)
        {
            overworldCameraPlace->DrawPopulationBubble();
            overworldCameraPlace->DrawCitizensBubble();
            overworldCameraPlace->DrawSurplusBubble();
            overworldCameraPlace->DrawDeficitBubble();
            overworldCameraPlace->DrawInventoryBubbles();
            overworldCameraPlace->DrawIndustriesBubble();
        }
        else if(overworldCameraCaravan != nullptr)
        {
            overworldCameraCaravan->DrawInventoryBubble();
            overworldCameraCaravan->DrawPathfindingBubble();

            if(overworldCameraCaravan->atPlace)
            {
                overworldCameraCaravan->whichPlace->DrawPopulationBubble();
                overworldCameraCaravan->whichPlace->DrawCitizensBubble();
                overworldCameraCaravan->whichPlace->DrawSurplusBubble();
                overworldCameraCaravan->whichPlace->DrawDeficitBubble();
                overworldCameraCaravan->whichPlace->DrawInventoryBubbles();
                overworldCameraCaravan->whichPlace->DrawIndustriesBubble();
            }
        }


/// End Draw Bubbles

        DrawCalendar();
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
        Place::places[i] = new Place(i);

    for(unsigned i = ROAD_MARKER_FIRST; i <= ROAD_MARKER_LAST; i++)
    {
        Road::roads[i] = new Road(i);

        Road* r = Road::roads[i];

        WorldGraph::AddRoadToBaseGraph(r->endpointA, r->endpointB, r->length);

        Place::places[r->endpointA]->connections.push_back(r);
        Place::places[r->endpointB]->connections.push_back(r);

    }

    for(std::map<int, Place*>::iterator it = Place::places.begin(); it != Place::places.end(); ++it)
    {

        ((*it).second)->GenerateCitizenCaravans();
    }


    /*
    playerCrew = new Caravan;
    Caravan::caravans.push_back(playerCrew);
    */

    /*
    player = new Being;
    player->SetName("Player");
    player->SetRace(RACE_VERIT);
    player->SetPortrait(RACE_VERIT,1);
    Being::people.push_back(player);
    */

    for(unsigned i = 0; i < Caravan::caravans.size(); i++)
    {
        for(unsigned j = 0; j < rand()%((unsigned)3+1); j++)
        {
            unsigned item = rand()%(IT_MARKER_FIRST + IT_MARKER_LAST + 1);
            unsigned quanitity = rand()%9 + 1;
            Caravan::caravans[i]->AddInventoryStock(item,quanitity);
        }


    }

}

void CleanupObjects()
{

    for(std::vector<Being*>::iterator it = Being::people.begin(); it != Being::people.end();)
    {
        delete *it;
        Being::people.erase(it);
    }

    for(std::vector<Caravan*>::iterator it = Caravan::caravans.begin(); it != Caravan::caravans.end();)
    {
        delete *it;
        Caravan::caravans.erase(it);
    }

    for(std::map<int,Place*>::iterator it = Place::places.begin(); it != Place::places.end(); ++it)
        delete it->second;
    Place::places.clear();

    for(std::map<int, Road*>::iterator it = Road::roads.begin(); it != Road::roads.end(); ++it)
        delete it->second;
    Road::roads.clear();
}
