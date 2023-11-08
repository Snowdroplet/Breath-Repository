/**
Obscure bugs list:
-If a city has all 23 items in its market inventory, deficits bubble is empty (but the height is still max)

-A city can have -0.00 deficit in an item

*/

/**
Todo next:
-Multiple beings in one party
-Caravan travel viewer bubble with parallax

-Crosshair button to re-lockOn to the caravan viewed in bubble, but not currently locked on to (e.g. when perusing the pathfinding bubble's locations)

-City and soverignty crests that can be clicked on to dispense the encyclopedia entry
*/

#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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

bool MouseLeftOnCaravanCrewBubble();
bool MouseLeftOnCaravanInventoryBubble();
bool MouseLeftOnCaravanTradeRecordsBubble();
bool MouseLeftOnCaravanPathfindingBubble();

bool MouseLeftOnPlacePopulationBubble();
bool MouseLeftOnPlaceCaravanseraiBubble();
bool MouseLeftOnPlaceSurplusBubble();
bool MouseLeftOnPlaceDeficitBubble();
bool MouseLeftOnPlaceMarketBubble();
bool MouseLeftOnPlaceIndustriesBubble();

void SetCameraCenterDestination(float x, float y);
void AttemptCameraLockOn();

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

    al_install_audio();
    al_init_acodec_addon();

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
    LoadFontResources();
    LoadImageResources();
    LoadAudioResources();

    al_identity_transform(&cameraNoTransform);

    InitCalendar(22,30,12,2023);

    InitObjects();

    ChangeUI(UI_OVERWORLD,SUBUI_OVERWORLD_NONE);

    al_start_timer(FPSTimer);

    OverworldBeginParallelBackgroundAudio();

    while(!gameExit)
    {
        al_wait_for_event(eventQueue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            gameExit = true;

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
            InputKeydown();

        if(event.type == ALLEGRO_EVENT_KEY_UP)
            InputKeyup();

        if(event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
            overworldCameraMousePanningDisabled = false;

        if(event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
            overworldCameraMousePanningDisabled = true;


        if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            InputMouseXY();
            InputMousewheel();

            // if(activeUI == UI_OVERWORLD)
            //OverworldUpdateTransformedMouseCoords(mouseDisplayX, mouseDisplayY);
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            InputMouseDown();

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            InputMouseUp();

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            //executionTime += (1.0/FPS);

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

    OverworldEndParallelBackgroundAudio();

    CleanupObjects();

    UnloadFontResources();
    UnloadImageResources();
    UnloadAudioResources();

    PHYSFS_deinit();

    al_uninstall_audio();
    al_destroy_display(display);
    al_destroy_timer(FPSTimer);
    al_destroy_event_queue(eventQueue);

    al_shutdown_native_dialog_addon();
    al_uninstall_system();

    return 0;
}

void InterpretInput()
{
    InputCooldown();

    if(mousewheelInput[MOUSEWHEEL_UP])
    {
        if(cameraZoomScale < CAMERA_SCALE_MAX)
        {
            cameraZoomScale += 0.1;

            cameraZoomTranslateX -= SCREEN_W*0.05; // Ten 0.05s = 0.5
            cameraZoomTranslateY -= SCREEN_H*0.05;

            std::cout << "zoom scale " << cameraZoomScale << " (" << cameraZoomScale*100 << "%)" << std::endl;
        }

        al_set_mouse_z(0);
    }
    else if(mousewheelInput[MOUSEWHEEL_DOWN])
    {
        if(cameraZoomScale > CAMERA_SCALE_MIN)
        {
            cameraZoomScale -= 0.1;

            cameraZoomTranslateX += SCREEN_W*0.05; // Ten 0.05s = 0.5
            cameraZoomTranslateY += SCREEN_H*0.05;

            std::cout << "zoom scale " << cameraZoomScale << " (" << cameraZoomScale*100 << "%)" << std::endl;
        }

        al_set_mouse_z(0);
    }
    else if(mouseInput[MOUSE_MIDDLE])
    {
        cameraZoomScale = 1;
        cameraZoomTranslateX = 0;
        cameraZoomTranslateY = 0;
    }

    if(mouseInput[MOUSE_LEFT])
    {
        CloseEncyclopediaBubble();
        CloseBeingStatusBubble();

        bool mouseLeftOnNoCaravanBubbles = false;
        bool mouseLeftOnNoPlaceBubbles = false;

        if(bubbleViewCaravan != nullptr)
        {
            if(!MouseLeftOnCaravanCrewBubble())
                if(!MouseLeftOnCaravanInventoryBubble())
                    if(!MouseLeftOnCaravanTradeRecordsBubble())
                        if(!MouseLeftOnCaravanPathfindingBubble())
                            mouseLeftOnNoCaravanBubbles = true;
        }
        else // bubbleViewCaravan == nullptr
            mouseLeftOnNoCaravanBubbles = true;

        if(bubbleViewPlace != nullptr)
        {
            if(!MouseLeftOnPlacePopulationBubble())
                if(!MouseLeftOnPlaceCaravanseraiBubble())
                    if(!MouseLeftOnPlaceSurplusBubble())
                        if(!MouseLeftOnPlaceDeficitBubble())
                            if(!MouseLeftOnPlaceMarketBubble())
                                if(!MouseLeftOnPlaceIndustriesBubble())
                                    mouseLeftOnNoPlaceBubbles = true;
        }
        else // bubbleViewPlace = nullptr
            mouseLeftOnNoPlaceBubbles = true;

        if(mouseLeftOnNoCaravanBubbles && mouseLeftOnNoPlaceBubbles)
        {
            mouseTransformedX = mouseDisplayX;
            mouseTransformedY = mouseDisplayY;
            al_invert_transform(&cameraZoom); // Don't need to invert a second time, by the way. On redraw, cameraZoom will be reset to identity_transform anyway
            al_transform_coordinates(&cameraZoom,&mouseTransformedX,&mouseTransformedY);
            SetCameraCenterDestination(overworldCameraXPosition + mouseTransformedX,
                                       overworldCameraYPosition + mouseTransformedY);
        }

        mouseInput[MOUSE_LEFT] = false;
    }

    if(keyInput[KEY_ESC])
    {
        // Priority: 1) Close enyclopedia. 2) Close being status bubble. 2) Close caravan/place bubbles. 3) Unlock camera.

        if(encyclopediaBubbleOpen)
            CloseEncyclopediaBubble();
        else // ! EncyclopediaBubbleOpen
        {
            if(beingStatusBubbleOpen)
                CloseBeingStatusBubble();
            else // ! beingStatusBubbleOpen
            {
                if(bubbleViewCaravan != nullptr || bubbleViewPlace != nullptr) // either caravan/place bubbles are open
                {
                    bubbleViewCaravan = nullptr;
                    bubbleViewPlace = nullptr;
                }
                else // no bubbles are open
                    OverworldUnlockCamera();
            }
        }
        keyInput[KEY_ESC] = false;
    }


    /// Camera panning
    if(!overworldCameraLocked)
    {
        if(!overworldCameraMousePanningDisabled)
        {
            if(mouseDisplayX < 2*TILE_W)
                overworldCameraXPosition -= overworldCameraXSensitivity;
            if(mouseDisplayX > SCREEN_W - 2*TILE_W)
                overworldCameraXPosition += overworldCameraXSensitivity;
            if(mouseDisplayY < 2*TILE_H)
                overworldCameraYPosition -= overworldCameraYSensitivity;
            if(mouseDisplayY > SCREEN_H - 2*TILE_H)
                overworldCameraYPosition += overworldCameraYSensitivity;
        }
    }

    if(keyInput[KEY_SPACE])
    {
        // Reestablishes bubbles of locked place/caravan, in case they have been closed (nullptr'd).
        if(overworldCameraLockedOnPlace)
            bubbleViewPlace = overworldCameraPlace;
        else if(overworldCameraLockedOnCaravan)
        {
            bubbleViewCaravan = overworldCameraCaravan;
            if(bubbleViewCaravan->atPlace)
                bubbleViewPlace = bubbleViewCaravan->whichPlace;
        }
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
        if(overworldCameraLockedOnCaravan)
        {
            overworldCameraXPosition = overworldCameraCaravan->overworldXPosition-SCREEN_W/2;
            overworldCameraYPosition = overworldCameraCaravan->overworldYPosition-SCREEN_H/2;
        }
        else // if ! overworldCameraLockedOnCaravan
        {
            if(overworldCameraApproachingDestination)
            {
                OverworldApproachCameraDestination();
                if(std::abs(overworldCameraXDestination - overworldCameraXPosition) <= 4 && std::abs(overworldCameraYDestination - overworldCameraYPosition) <= 4)
                {
                    AttemptCameraLockOn();
                    overworldCameraApproachingDestination = false;
                }

            }

        }

        OverworldAudioUpdate();
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

        // draw stuff, then revert to identity_transform before drawing UI

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

        al_use_transform(&cameraNoTransform);

        if(bubbleViewCaravan != nullptr)
        {
            bubbleViewCaravan->DrawCaravanCrewBubble();
            //bubbleViewCaravan->DrawCaravanTravelViewBubble();
            bubbleViewCaravan->DrawCaravanInventoryBubble();
            bubbleViewCaravan->DrawCaravanTradeRecordsBubble();
            bubbleViewCaravan->DrawCaravanPathfindingBubble();
        }
        if(bubbleViewPlace != nullptr)
        {
            bubbleViewPlace->DrawPlacePopulationBubble();
            bubbleViewPlace->DrawPlaceCaravanseraiBubble();

            bubbleViewPlace->DrawPlaceSurplusBubble();
            bubbleViewPlace->DrawPlaceDeficitBubble();

            bubbleViewPlace->DrawPlaceMarketBubble();
            bubbleViewPlace->DrawPlaceIndustriesBubble();
        }

        if(beingStatusBubbleOpen)
            DrawBeingStatusBubble();

        if(encyclopediaBubbleOpen)
            DrawEncyclopediaBubble();

        DrawCalendar();
        //OverworldDrawGridMouseCrosshair(mouseDisplayX, mouseDisplayY);
        OverworldDrawGridText(mouseDisplayX, mouseDisplayY);

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

bool MouseLeftOnCaravanCrewBubble()
{
    if(mouseDisplayX > caravanCrewBubbleDrawX
            && mouseDisplayX < caravanCrewBubbleDrawX + bubbleViewCaravan->caravanCrewBubbleWidth
            && mouseDisplayY > caravanCrewBubbleDrawY
            && mouseDisplayY < caravanCrewBubbleDrawY + caravanCrewBubbleHeight)
    {
        int x = mouseDisplayX - caravanCrewBubbleDrawX;
        unsigned index = x/TILE_W;

        if(index < bubbleViewCaravan->members.size())
        {
            OverworldLockCameraCaravan(bubbleViewCaravan);
            OpenBeingStatusBubble(bubbleViewCaravan->members[index]);
        }

        return true;
    }
    else
        return false;
}

bool MouseLeftOnCaravanInventoryBubble()
{
    if(mouseDisplayX > caravanInventoryBubbleDrawX
            && mouseDisplayX < caravanInventoryBubbleDrawX + bubbleViewCaravan->caravanInventoryBubbleWidth
            && mouseDisplayY > caravanInventoryBubbleDrawY
            && mouseDisplayY < caravanInventoryBubbleDrawY + bubbleViewCaravan->caravanInventoryBubbleHeight)
    {
        int x = mouseDisplayX - caravanInventoryBubbleDrawX;
        int y = mouseDisplayY - caravanInventoryBubbleDrawY;

        int xCell = x/TILE_W;
        int yCell = y/(TILE_H+caravanInventoryBubbleRowSpacing);

        unsigned position = yCell*(bubbleViewCaravan->caravanInventoryBubbleNumCols) + xCell;

        if(position < bubbleViewCaravan->inventory.cargo.size())
        {
            std::map<int,float>::iterator it = bubbleViewCaravan->inventory.cargo.begin();
            std::advance(it, position);

            OpenEncyclopediaBubble(mouseDisplayX, mouseDisplayY, EN_CAT_CARGO, (*it).first);
        }

        return true;
    }
    else
        return false;
}

bool MouseLeftOnCaravanTradeRecordsBubble()
{
    if(mouseDisplayX > caravanTradeRecordsBubbleDrawX
            && mouseDisplayX < caravanTradeRecordsBubbleDrawX + caravanTradeRecordsBubbleWidth
            && mouseDisplayY > caravanTradeRecordsBubbleDrawY
            && mouseDisplayY < caravanTradeRecordsBubbleDrawY + bubbleViewCaravan->caravanTradeRecordsBubbleHeight)
    {
        int x = mouseDisplayX - caravanTradeRecordsBubbleDrawX;
        int y = mouseDisplayY - caravanTradeRecordsBubbleDrawY;

        int xCell = x/TILE_W;
        int yCell = y/(TILE_H+caravanTradeRecordsBubbleRowSpacing);

        int ritRecordRowMin = 0;
        int ritRecordRowMax = 0;
        for(std::vector<TradeRecord*>::reverse_iterator rit = bubbleViewCaravan->tradeRecords.rbegin(); rit != bubbleViewCaravan->tradeRecords.rend(); ++rit)
        {
            ritRecordRowMax = ritRecordRowMin + (*rit)->numRows-1;
            if(yCell >= ritRecordRowMin && yCell <= ritRecordRowMax)
            {
                if(x < caravanTradeRecordsBubblePlaceNameWidth)
                {
                    Place::places[(*rit)->location]->UpdateAllBubbles();
                    OverworldLockCameraPlace(Place::places[(*rit)->location]);

                    OpenEncyclopediaBubble(SCREEN_W/2 - encyclopediaBubbleWidth/2,
                                           SCREEN_H/2 + 2*TILE_H,
                                           EN_CAT_PLACES, (*rit)->location);
                }
                else // x >= caravanTradeRecordsBubblePlaceNameWidth
                {
                    xCell -= caravanTradeRecordsBubblePlaceNameWidth/TILE_W;
                    yCell -= ritRecordRowMin;

                    unsigned position = yCell*((*rit)->maxCols) + xCell;
                    if(position < (*rit)->tradeQuantities.size())
                    {
                        std::map<int,int>::iterator it = (*rit)->tradeQuantities.begin();
                        std::advance(it, position);

                        OpenEncyclopediaBubble(mouseDisplayX, mouseDisplayY, EN_CAT_CARGO, (*it).first);
                    }
                }
                break;
            }
            else // yCell not within ritRecordRowMin/Max, i.e. not within the boundary coords of the tradeRecord being inspected
                ritRecordRowMin = ritRecordRowMax+1;
        }

        return true;
    }
    else
        return false;
}

bool MouseLeftOnCaravanPathfindingBubble()
{
    if(mouseDisplayX > caravanPathfindingBubbleDrawX
            && mouseDisplayX < caravanPathfindingBubbleDrawX + bubbleViewCaravan->caravanPathfindingBubbleWidth
            && mouseDisplayY > caravanPathfindingBubbleDrawY
            && mouseDisplayY < caravanPathfindingBubbleDrawY + caravanPathfindingBubbleHeight - TEXT_HEIGHT_8)
    {
        int x = mouseDisplayX - caravanPathfindingBubbleDrawX;

        int xCell = x/TILE_W; // The representation of cities is two tiles wide; every third tile is the red arrow and should not be clickable.
        if(xCell %3 != 2)
        {
            unsigned position = xCell/3;
            int placeId = bubbleViewCaravan->worldGraph.path[position];

            Place::places[placeId]->UpdateAllBubbles();

            SetCameraCenterDestination(Place::places[placeId]->overworldXPosition,
                                       Place::places[placeId]->overworldYPosition);

            OpenEncyclopediaBubble(SCREEN_W/2 - encyclopediaBubbleWidth/2,
                                   SCREEN_H/2 + 2*TILE_H,
                                   EN_CAT_PLACES, placeId);
        }

        return true;
    }
    else
        return false;
}

bool MouseLeftOnPlacePopulationBubble()
{
    return false;
}

bool MouseLeftOnPlaceCaravanseraiBubble()
{
    if(mouseDisplayX > placeCaravanseraiDrawX
            && mouseDisplayX < placeCaravanseraiDrawX + bubbleViewPlace->placeCaravanseraiWidth
            && mouseDisplayY > placeCaravanseraiDrawY
            && mouseDisplayY < placeCaravanseraiDrawY + bubbleViewPlace->placeCaravanseraiHeight)
    {
        int x = mouseDisplayX - placeCaravanseraiDrawX;
        int y = mouseDisplayY - placeCaravanseraiDrawY;

        int xCell = x/TILE_W;
        int yCell = y/TILE_H;

        unsigned position = yCell*(bubbleViewPlace->placeCaravanseraiNumCols) + xCell;

        if(position < bubbleViewPlace->caravanserai.size())
        {
            bubbleViewPlace->caravanserai[position]->UpdateAllBubbles();
            bubbleViewCaravan = bubbleViewPlace->caravanserai[position];
            //OverworldLockCameraCaravan(bubbleViewPlace->caravanserai[position]); // Already unlocks camera from place
        }

        return true;
    }
    else
        return false;
}

bool MouseLeftOnPlaceSurplusBubble()
{
    return false;
}

bool MouseLeftOnPlaceDeficitBubble()
{
    return false;
}

bool MouseLeftOnPlaceMarketBubble()
{
    if(mouseDisplayX > placeMarketBubbleDrawX
            && mouseDisplayX < placeMarketBubbleDrawX + bubbleViewPlace->placeMarketBubbleWidth
            && mouseDisplayY > placeMarketBubbleDrawY
            && mouseDisplayY < placeMarketBubbleDrawY + bubbleViewPlace->placeMarketBubbleHeight)
    {
        int x = mouseDisplayX - placeMarketBubbleDrawX;
        int y = mouseDisplayY - placeMarketBubbleDrawY;

        int xCell = x/TILE_W;
        int yCell = y/(TILE_H+placeMarketBubbleRowSpacing);

        unsigned position = yCell*(bubbleViewPlace->placeMarketBubbleNumCols) + xCell;

        if(position < bubbleViewPlace->market.cargo.size())
        {
            std::map<int,float>::iterator it = bubbleViewPlace->market.cargo.begin();
            std::advance(it, position);

            OpenEncyclopediaBubble(mouseDisplayX, mouseDisplayY, EN_CAT_CARGO, (*it).first);
        }

        return true;
    }
    else
        return false;
}

bool MouseLeftOnPlaceIndustriesBubble()
{
    if(mouseDisplayX > placeIndustriesBubbleDrawX
            && mouseDisplayX < placeIndustriesBubbleDrawX + placeIndustriesBubbleWidth
            && mouseDisplayY > placeIndustriesBubbleDrawY
            && mouseDisplayY < placeIndustriesBubbleDrawY + bubbleViewPlace->placeIndustriesBubbleHeight)
    {
        std::cout << "Unimplemented" << std::endl;

        return true;
    }
    else
        return false;
}

void SetCameraCenterDestination(float x, float y)
{
    //bubbleViewCaravan = nullptr; // Don't nullify this. Needed to peruse pathfinding bubble locations without it closing
    bubbleViewPlace = nullptr;

    OverworldUnlockCamera();

    overworldCameraXDestination = x - SCREEN_W/2;
    overworldCameraYDestination = y - SCREEN_H/2;

    overworldCameraApproachingDestination = true;
}

void AttemptCameraLockOn()
{
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
            bubbleViewPlace = ((*it).second);
            (*it).second->UpdateAllBubbles();

            overworldCameraXPosition = x - SCREEN_W/2;
            overworldCameraYPosition = y - SCREEN_H/2;
            break;
        }
    }

    if(!overworldCameraLockedOnPlace) // If a Place wasn't locked on to, search for a caravan.
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
                bubbleViewCaravan = (*it);
                break;
            }
        }
    }
}
