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
#include "encyclopedia.h"


void InterpretInput();
void ProgressWorld();
void UpdateUI();

void ChangeUI(int whichUI, int whichSubUI);

void DrawUI();

void InitObjects();
void CleanupObjects();

void MouseLeftOnCaravanInventoryBubble();
void MouseLeftOnCaravanTradeRecordsBubble();
void MouseLeftOnCaravanPathfindingBubble();

void MouseLeftOnPlacePopulationBubble();
void MouseLeftOnPlaceCaravanseraiBubble();
void MouseLeftOnPlaceSurplusBubble();
void MouseLeftOnPlaceDeficitBubble();
void MouseLeftOnPlaceMarketBubble();
void MouseLeftOnPlaceIndustriesBubble();

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
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    PHYSFS_init(argv[0]);
    if(!PHYSFS_mount("./gamedata.zip", "/", 1))
    {
        al_show_native_message_box(al_get_current_display(),"Initialization Failed", "", "gamedata.zip not found!", NULL, 0);
        return false;
    }

    al_set_physfs_file_interface();

    AllegroCustomColours();
    LoadResources();

    InitCalendar(22,30,12,2023);

    InitObjects();

    ChangeUI(UI_OVERWORLD,SUBUI_OVERWORLD_NONE);

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

        if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            InputMouseXY();
            InputMousewheel();
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            InputMouseDown();
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            InputMouseUp();

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

    if(mousewheelInput[MOUSEWHEEL_UP])
    {
        if(cameraZoomScale < CAMERA_SCALE_MAX)
        {
            cameraZoomScale += 0.1;
            cameraZoomTranslateX -= SCREEN_W*0.05; // Ten 0.05s = 0.5
            cameraZoomTranslateY -= SCREEN_H*0.05;
        }

        al_set_mouse_z(0);
    }
    else if(mousewheelInput[MOUSEWHEEL_DOWN])
    {
        if(cameraZoomScale > CAMERA_SCALE_MIN)
        {
            cameraZoomScale -= 0.1;
            cameraZoomTranslateX += SCREEN_W*0.05;
            cameraZoomTranslateY += SCREEN_H*0.05;
        }

        al_set_mouse_z(0);
    }
    else if(mouseInput[MOUSE_MIDDLE])
    {
        cameraZoomScale = 1;
        cameraZoomTranslateX = 0;
        cameraZoomTranslateY = 0;
    }


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

            if(mouseInput[MOUSE_LEFT])
            {
                if(caravanInventoryBubbleOpen)
                    MouseLeftOnCaravanInventoryBubble();
                if(caravanTradeRecordsBubbleOpen)
                    MouseLeftOnCaravanTradeRecordsBubble();
                if(caravanPathfindingBubbleOpen)
                    MouseLeftOnCaravanPathfindingBubble();

                //if(placePopulationBubbleOpen)

                //if(placeCaravanseraiBubbleOpen)

                //if(placeSurplusBubbleOpen)

                //if(placeDeficitBubbleOpen)

                //if(placeMarketBubbleOpen)

                //if(placeIndustriesBubbleOpen)


            }

        }


        if(!UIChangeDelay)
        {


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
            ((*it).second)->ProgressPlaceIndustriesBubbleProgressBars();

            if(hourChangeTick)
            {
                ((*it).second)->ProgressProduction();

                ((*it).second)->ProgressMaintainenceConsumption();
                ((*it).second)->UpdateSurplusesDescending();
                ((*it).second)->UpdateDeficitsDescending();


            }

            if(dayChangeTick)
            {
                //((*it).second)->UpdateEconomyData();
            }

        }

        /*
        for(std::map<int,Road*>::iterator it = Road::roads.begin(); it != Road::roads.end(); ++it)
        {

        }
        */

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


void ChangeUI(int whichUI, int whichSubUI)
{
    UIChangeDelay = true;

    if(whichUI != activeUI)
        previousActiveUI = activeUI;
    if(whichSubUI != activeSubUI)
        previousActiveSubUI = activeSubUI;

    activeUI = whichUI;
    activeSubUI = whichSubUI;

    if(activeUI == UI_OVERWORLD)
    {
        currentClearColor = COL_JADE_3;
    }
}


void DrawUI()
{
    if(activeUI == UI_OVERWORLD)
    {

        al_identity_transform(&cameraZoom);
        al_scale_transform(&cameraZoom,cameraZoomScale,cameraZoomScale);
        al_translate_transform(&cameraZoom,cameraZoomTranslateX,cameraZoomTranslateY);
        al_use_transform(&cameraZoom);

        OverworldDrawGridUnderlay();
        OverworldDrawGridCameraCrosshair();

        for(unsigned i = 0; i < Place::places.size(); i++)
            Place::places[i]->DrawSpriteOnOverworld();

        for(unsigned i = 0; i < Road::roads.size(); i++)
            Road::roads[i]->DrawSegmentsOnOverworld();

        for(unsigned i = 0; i < Caravan::caravans.size(); i++)
            Caravan::caravans[i]->DrawSpriteOnOverworld();

        for(std::map<int, Place*>::iterator it = Place::places.begin(); it != Place::places.end(); ++it)
            (*it).second->DrawFlyingTexts();

        al_identity_transform(&cameraZoom);
        al_use_transform(&cameraZoom);

        if(overworldCameraPlace != nullptr)
        {
            overworldCameraPlace->DrawPlacePopulationBubble();
            overworldCameraPlace->DrawPlaceCaravanseraiBubble();

            overworldCameraPlace->DrawPlaceSurplusBubble();
            overworldCameraPlace->DrawPlaceDeficitBubble();

            overworldCameraPlace->DrawPlaceMarketBubble();
            overworldCameraPlace->DrawPlaceIndustriesBubble();
        }
        else if(overworldCameraCaravan != nullptr)
        {
            overworldCameraCaravan->DrawCaravanInventoryBubble();
            overworldCameraCaravan->DrawCaravanTradeRecordsBubble();
            overworldCameraCaravan->DrawCaravanPathfindingBubble();

            if(overworldCameraCaravan->atPlace)
            {
                overworldCameraCaravan->whichPlace->DrawPlacePopulationBubble();
                overworldCameraCaravan->whichPlace->DrawPlaceCaravanseraiBubble();

                overworldCameraCaravan->whichPlace->DrawPlaceSurplusBubble();
                overworldCameraCaravan->whichPlace->DrawPlaceDeficitBubble();

                overworldCameraCaravan->whichPlace->DrawPlaceMarketBubble();
                overworldCameraCaravan->whichPlace->DrawPlaceIndustriesBubble();
            }
        }

        //OverworldDrawGridMouseCrosshair(mouseX, mouseY);

        OverworldDrawGridText(mouseX, mouseY);

        DrawCalendar();
    }
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
    player->SetAncestry(ANCESTRY_VERIT);
    player->SetPortrait(ANCESTRY_VERIT,1);
    Being::people.push_back(player);
    */

    /*
    for(unsigned i = 0; i < Caravan::caravans.size(); i++)
    {
        for(unsigned j = 0; j < rand()%((unsigned)3+1); j++)
        {
            unsigned item = rand()%(IT_MARKER_FIRST + IT_MARKER_LAST + 1);
            unsigned quanitity = rand()%9 + 1;
            Caravan::caravans[i]->AddInventoryStock(item,quanitity);
        }
    }
    */

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

void MouseLeftOnCaravanInventoryBubble()
{
    if(mouseX > caravanInventoryBubbleDrawX
       && mouseX < caravanInventoryBubbleDrawX + overworldCameraCaravan->caravanInventoryBubbleWidth
       && mouseY > caravanInventoryBubbleDrawY
       && mouseY < caravanInventoryBubbleDrawY + overworldCameraCaravan->caravanInventoryBubbleHeight)
    {
        int x = mouseX - caravanInventoryBubbleDrawX;
        int y = mouseY - caravanInventoryBubbleDrawY;

        int xCell = x/TILE_W;
        int yCell = y/(TILE_H+caravanInventoryBubbleRowSpacing);

        unsigned position = yCell*(overworldCameraCaravan->caravanInventoryBubbleNumCols) + xCell;

        std::cout << "Test: clicky clicky " << position << std::endl;

        if(position < overworldCameraCaravan->inventory.cargo.size())
        {
            std::map<int,float>::iterator it = overworldCameraCaravan->inventory.cargo.begin();
            std::advance(it, position);

            std::cout << itemNames.at((*it).first) << std::endl;
        }
    }
}

void MouseLeftOnCaravanTradeRecordsBubble()
{

}

void MouseLeftOnCaravanPathfindingBubble()
{

}

void MouseLeftOnPlacePopulationBubble()
{

}

void MouseLeftOnPlaceCaravanseraiBubble()
{

}

void MouseLeftOnPlaceSurplusBubble()
{

}

void MouseLeftOnPlaceDeficitBubble()
{

}

void MouseLeftOnPlaceMarketBubble()
{

}

void MouseLeftOnPlaceIndustriesBubble()
{

}
