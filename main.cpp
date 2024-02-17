/**
Obscure bugs list:
-If a city has all 23 items in its market inventory, deficits bubble is empty (but the height is still max)

-A city can have -0.00 deficit in an item, which does not equal 0.00

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

#include "event.h"
#include "timer.h"
#include "camera.h"
#include "resource.h"
#include "scene.h"
#include "being.h"
#include "caravan.h"
#include "road.h"
#include "place.h"
#include "overworld.h"
#include "calendar.h"

bool gameExit = false;

bool redraw = false;

void Initialize();
void Deinitialize();

void InterpretInput();
void ProgressWorld();
void UpdateUI();

void DrawUI();

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

    Display::display = al_create_display(Display::WIDTH, Display::HEIGHT);
    if(!Display::display)
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

    Timer::FPSTimer = al_create_timer(1.0/Timer::FPS);

    Event::eventQueue = al_create_event_queue();

    al_register_event_source(Event::eventQueue, al_get_display_event_source(Display::display));
    al_register_event_source(Event::eventQueue, al_get_timer_event_source(Timer::FPSTimer));
    al_register_event_source(Event::eventQueue, al_get_keyboard_event_source());
    al_register_event_source(Event::eventQueue, al_get_mouse_event_source());

    PHYSFS_init(argv[0]);
    if(!PHYSFS_mount("./gamedata.zip", "/", 1))
    {
        al_show_native_message_box(al_get_current_display(),"Initialization Failed", "", "gamedata.zip not found!", NULL, 0);
        return false;
    }

    al_set_physfs_file_interface();

    AllegroCustomColours();
    Resource::LoadFontResources();
    Resource::LoadImageResources();
    Resource::LoadAudioResources();

    Initialize();

    al_start_timer(Timer::FPSTimer);

    al_identity_transform(&Camera::noTransform);

    OverworldBeginParallelBackgroundAudio();

    while(!gameExit)
    {
        al_wait_for_event(Event::eventQueue, &Event::event);

        if(Event::event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            gameExit = true;

        if(Event::event.type == ALLEGRO_EVENT_KEY_DOWN)
            Event::InputKeydown();

        if(Event::event.type == ALLEGRO_EVENT_KEY_UP)
            Event::InputKeyup();

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
            overworldCameraMousePanningDisabled = false;

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
            overworldCameraMousePanningDisabled = true;


        if(Event::event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            Event::InputMouseXY();
            Event::InputMousewheel();

            // if(activeUI == UI_OVERWORLD)
            //OverworldUpdateTransformedMouseCoords(mouseDisplayX, mouseDisplayY);
        }

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            Event::InputMouseDown();

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            Event::InputMouseUp();

        if(Event::event.type == ALLEGRO_EVENT_TIMER)
        {
            //executionTime += (1.0/FPS);

            redraw = true;

            InterpretInput();
            ProgressWorld();
            UpdateUI();
        }

        if(redraw && al_is_event_queue_empty(Event::eventQueue))
        {
            redraw = false;
            al_clear_to_color(currentClearColor);
            DrawUI();
            al_flip_display();
        }
    }

    OverworldEndParallelBackgroundAudio();

    Deinitialize();

    Resource::UnloadFontResources();
    Resource::UnloadImageResources();
    Resource::UnloadAudioResources();

    PHYSFS_deinit();

    al_uninstall_audio();
    al_destroy_display(Display::display);
    al_destroy_timer(Timer::FPSTimer);
    al_destroy_event_queue(Event::eventQueue);

    al_shutdown_native_dialog_addon();
    al_uninstall_system();

    return 0;
}

void Initialize()
{
    Scene::Initialize();
    Camera::Initialize();
    BubbleView::Initialize();

    InitCalendar(22,30,12,2023);

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

    Scene::ChangeScene(Scene::SCENE_OVERWORLD,Scene::SUBSCENE_OVERWORLD_NONE);
    currentClearColor = COL_JADE_3;
}

void Deinitialize()
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

void InterpretInput()
{
    Event::InputKeyHold();
    Event::InputMouseButtonHold();

    if(Event::mousewheelInput[Event::MOUSEWHEEL_UP])
    {
        if(Camera::zoomScale < Camera::SCALE_MAX)
        {
            Camera::zoomScale += 0.1;

            Camera::zoomTranslateX -= Display::WIDTH*0.05; // Ten 0.05s = 0.5
            Camera::zoomTranslateY -= Display::HEIGHT*0.05;

            //std::cout << "zoom scale " << Camera::zoomScale << " (" << Camera::zoomScale*100 << "%)" << std::endl;
        }

        al_set_mouse_z(0);
    }
    else if(Event::mousewheelInput[Event::MOUSEWHEEL_DOWN])
    {
        if(Camera::zoomScale > Camera::SCALE_MIN)
        {
            Camera::zoomScale -= 0.1;

            Camera::zoomTranslateX += Display::WIDTH*0.05; // Ten 0.05s = 0.5
            Camera::zoomTranslateY += Display::HEIGHT*0.05;

            //std::cout << "zoom scale " << Camera::zoomScale << " (" << Camera::zoomScale*100 << "%)" << std::endl;
        }

        al_set_mouse_z(0);
    }
    else if(Event::mouseButtonHoldTicks[Event::MOUSE_MIDDLE] == 1)
    {
        Camera::zoomScale = 1;
        Camera::zoomTranslateX = 0;
        Camera::zoomTranslateY = 0;
    }

    if(Event::mouseButtonHoldTicks[Event::MOUSE_LEFT] == 1)
    {
        BubbleView::CloseEncyclopediaBubble();
        BubbleView::CloseBeingStatusBubble();

        bool mouseLeftOnNoCaravanBubbles = false;
        bool mouseLeftOnNoPlaceBubbles = false;

        if(BubbleView::currentCaravan != nullptr)
        {
            if(!MouseLeftOnCaravanCrewBubble())
                if(!MouseLeftOnCaravanInventoryBubble())
                    if(!MouseLeftOnCaravanTradeRecordsBubble())
                        if(!MouseLeftOnCaravanPathfindingBubble())
                            mouseLeftOnNoCaravanBubbles = true;
        }
        else // BubbleView::currentCaravan == nullptr
            mouseLeftOnNoCaravanBubbles = true;

        if(BubbleView::currentPlace != nullptr)
        {
            if(!MouseLeftOnPlacePopulationBubble())
                if(!MouseLeftOnPlaceCaravanseraiBubble())
                    if(!MouseLeftOnPlaceSurplusBubble())
                        if(!MouseLeftOnPlaceDeficitBubble())
                            if(!MouseLeftOnPlaceMarketBubble())
                                if(!MouseLeftOnPlaceIndustriesBubble())
                                    mouseLeftOnNoPlaceBubbles = true;
        }
        else // BubbleView::currentPlace = nullptr
            mouseLeftOnNoPlaceBubbles = true;

        if(mouseLeftOnNoCaravanBubbles && mouseLeftOnNoPlaceBubbles)
        {
            Camera::mouseTransformedX = Event::mouseDisplayX;
            Camera::mouseTransformedY = Event::mouseDisplayY;
            al_invert_transform(&Camera::zoomTransform); // Don't need to invert a second time, by the way. On redraw, cameraZoom will be reset to identity_transform anyway
            al_transform_coordinates(&Camera::zoomTransform,&Camera::mouseTransformedX,&Camera::mouseTransformedY);
            SetCameraCenterDestination(Camera::xPosition + Camera::mouseTransformedX,
                                       Camera::yPosition + Camera::mouseTransformedY);
        }

        //Event::mouseInput[Event::MOUSE_LEFT] = false;
    }

    if(Event::keyHoldTicks[Event::KEY_ESC] == 1)
    {
        // Priority: 1) Close enyclopedia. 2) Close being status bubble. 2) Close caravan/place bubbles. 3) Unlock camera.

        if(BubbleView::encyclopediaBubbleOpen)
            BubbleView::CloseEncyclopediaBubble();
        else // ! EncyclopediaBubbleOpen
        {
            if(BubbleView::BubbleView::beingStatusBubbleOpen)
                BubbleView::CloseBeingStatusBubble();
            else // ! BubbleView::beingStatusBubbleOpen
            {
                if(BubbleView::currentCaravan != nullptr || BubbleView::currentPlace != nullptr) // either caravan/place bubbles are open
                {
                    BubbleView::currentCaravan = nullptr;
                    BubbleView::currentPlace = nullptr;
                }
                else // no bubbles are open
                    OverworldUnlockCamera();
            }
        }
        //Event::keyInput[Event::KEY_ESC] = false;
    }


    /// Camera panning
    if(!overworldCameraLocked)
    {
        if(!overworldCameraMousePanningDisabled)
        {
            if(Event::mouseDisplayX < 2*Tile::WIDTH)
                Camera::xPosition -= Camera::xSensitivity;
            if(Event::mouseDisplayX > Display::WIDTH - 2*Tile::WIDTH)
                Camera::xPosition += Camera::xSensitivity;
            if(Event::mouseDisplayY < 2*Tile::HEIGHT)
                Camera::yPosition -= Camera::ySensitivity;
            if(Event::mouseDisplayY > Display::HEIGHT - 2*Tile::HEIGHT)
                Camera::yPosition += Camera::ySensitivity;
        }
    }

    if(Event::keyHoldTicks[Event::KEY_SPACE] == 1)
    {
        // Reestablishes bubbles of locked place/caravan, in case they have been closed (nullptr'd).
        if(overworldCameraLockedOnPlace)
            BubbleView::currentPlace = overworldCameraPlace;
        else if(overworldCameraLockedOnCaravan)
        {
            BubbleView::currentCaravan = overworldCameraCaravan;
            if(BubbleView::currentCaravan->atPlace)
                BubbleView::currentPlace = BubbleView::currentCaravan->whichPlace;
        }
    }
}

void ProgressWorld()
{
    if(Scene::activeScene == Scene::SCENE_OVERWORLD)
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
    if(Scene::activeScene == Scene::SCENE_OVERWORLD)
    {
        if(overworldCameraLockedOnCaravan)
        {
            Camera::xPosition = overworldCameraCaravan->overworldXPosition-Display::WIDTH/2;
            Camera::yPosition = overworldCameraCaravan->overworldYPosition-Display::HEIGHT/2;
        }
        else // if ! overworldCameraLockedOnCaravan
        {
            if(Camera::approachingDestination)
            {
                ///OverworldApproachCameraDestination();
                Camera::ApproachDestination();
                if(std::abs(Camera::xDestination - Camera::xPosition) <= 4 && std::abs(Camera::yDestination - Camera::yPosition) <= 4)
                {
                    Camera::WarpToDestination();
                    AttemptCameraLockOn();
                }

            }

        }

        if(BubbleView::currentCaravan != nullptr)
        {
            if(BubbleView::currentCaravan->crewBubbleNeedsUpdate)
                BubbleView::UpdateCaravanCrewBubble(BubbleView::currentCaravan);
            if(BubbleView::currentCaravan->inventoryBubbleNeedsUpdate)
                BubbleView::UpdateCaravanInventoryBubble(BubbleView::currentCaravan);
            if(BubbleView::currentCaravan->tradeRecordsBubbleNeedsUpdate)
                BubbleView::UpdateCaravanTradeRecordsBubble(BubbleView::currentCaravan);
            if(BubbleView::currentCaravan->pathfindingBubbleNeedsUpdate)
                BubbleView::UpdateCaravanPathfindingBubble(BubbleView::currentCaravan);
        }

        if(BubbleView::currentPlace != nullptr)
        {
            if(BubbleView::currentPlace->populationBubbleNeedsUpdate)
                BubbleView::UpdatePlacePopulationBubble(BubbleView::currentPlace);
            if(BubbleView::currentPlace->caravanseraiBubbleNeedsUpdate)
                BubbleView::UpdatePlaceCaravanseraiBubble(BubbleView::currentPlace);
            if(BubbleView::currentPlace->surplusBubbleNeedsUpdate)
                BubbleView::UpdatePlaceSurplusBubble(BubbleView::currentPlace);
            if(BubbleView::currentPlace->deficitBubbleNeedsUpdate)
                BubbleView::UpdatePlaceDeficitBubble(BubbleView::currentPlace);
            if(BubbleView::currentPlace->marketBubbleNeedsUpdate)
                BubbleView::UpdatePlaceMarketBubble(BubbleView::currentPlace);
            if(BubbleView::currentPlace->industriesBubbleNeedsUpdate)
                BubbleView::UpdatePlaceIndustriesBubble(BubbleView::currentPlace);

        }

        OverworldAudioUpdate();
    }
}

void DrawUI()
{
    if(Scene::activeScene == Scene::SCENE_OVERWORLD)
    {
        al_identity_transform(&Camera::zoomTransform);
        al_scale_transform(&Camera::zoomTransform,Camera::zoomScale,Camera::zoomScale);
        al_translate_transform(&Camera::zoomTransform,Camera::zoomTranslateX,Camera::zoomTranslateY);
        al_use_transform(&Camera::zoomTransform);

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

        al_use_transform(&Camera::noTransform);

        if(BubbleView::beingStatusBubbleOpen)
            BubbleView::DrawBeingStatusBubble(BubbleView::currentBeing);

        if(BubbleView::currentCaravan != nullptr)
        {
            BubbleView::DrawCaravanCrewBubble(BubbleView::currentCaravan);
            //BubbleView::DrawCaravanTravelViewBubble(BubbleView::currentCaravan);
            BubbleView::DrawCaravanInventoryBubble(BubbleView::currentCaravan);
            BubbleView::DrawCaravanTradeRecordsBubble(BubbleView::currentCaravan);
            BubbleView::DrawCaravanPathfindingBubble(BubbleView::currentCaravan);
        }
        if(BubbleView::currentPlace != nullptr)
        {
            BubbleView::DrawPlacePopulationBubble(BubbleView::currentPlace);
            BubbleView::DrawPlaceCaravanseraiBubble(BubbleView::currentPlace);
            BubbleView::DrawPlaceSurplusBubble(BubbleView::currentPlace);
            BubbleView::DrawPlaceDeficitBubble(BubbleView::currentPlace);
            BubbleView::DrawPlaceMarketBubble(BubbleView::currentPlace);
            BubbleView::DrawPlaceIndustriesBubble(BubbleView::currentPlace);
        }

        if(BubbleView::encyclopediaBubbleOpen)
            BubbleView::DrawEncyclopediaBubble();

        DrawCalendar();
        //OverworldDrawGridMouseCrosshair(mouseDisplayX, mouseDisplayY);
        OverworldDrawGridText(Event::mouseDisplayX, Event::mouseDisplayY);

    }
}

bool MouseLeftOnCaravanCrewBubble()
{
    if(Event::mouseDisplayX > BubbleView::caravanCrewBubbleDrawX
            && Event::mouseDisplayX < BubbleView::caravanCrewBubbleDrawX + BubbleView::caravanCrewBubbleWidth
            && Event::mouseDisplayY > BubbleView::caravanCrewBubbleDrawY
            && Event::mouseDisplayY < BubbleView::caravanCrewBubbleDrawY + BubbleView::caravanCrewBubbleHeight)
    {
        int x = Event::mouseDisplayX - BubbleView::caravanCrewBubbleDrawX;
        unsigned index = x/Tile::WIDTH;

        if(index < BubbleView::currentCaravan->members.size())
        {
            OverworldLockCameraCaravan(BubbleView::currentCaravan);
            BubbleView::OpenBeingStatusBubble(BubbleView::currentCaravan->members[index]);
        }

        return true;
    }
    else
        return false;
}

bool MouseLeftOnCaravanInventoryBubble()
{
    if(Event::mouseDisplayX > BubbleView::caravanInventoryBubbleDrawX
            && Event::mouseDisplayX < BubbleView::caravanInventoryBubbleDrawX + BubbleView::caravanInventoryBubbleWidth
            && Event::mouseDisplayY > BubbleView::caravanInventoryBubbleDrawY
            && Event::mouseDisplayY < BubbleView::caravanInventoryBubbleDrawY + BubbleView::caravanInventoryBubbleHeight)
    {
        int x = Event::mouseDisplayX - BubbleView::caravanInventoryBubbleDrawX;
        int y = Event::mouseDisplayY - BubbleView::caravanInventoryBubbleDrawY;

        int xCell = x/Tile::WIDTH;
        int yCell = y/(Tile::HEIGHT+BubbleView::caravanInventoryBubbleRowSpacing);

        unsigned position = yCell*BubbleView::caravanInventoryBubbleNumCols + xCell;

        if(position < BubbleView::currentCaravan->inventory.cargo.size())
        {
            std::map<int,float>::iterator it = BubbleView::currentCaravan->inventory.cargo.begin();
            std::advance(it, position);

            BubbleView::OpenEncyclopediaBubble(Event::mouseDisplayX, Event::mouseDisplayY, EN_CAT_CARGO, (*it).first);
        }

        return true;
    }
    else
        return false;
}

bool MouseLeftOnCaravanTradeRecordsBubble()
{
    if(Event::mouseDisplayX > BubbleView::caravanTradeRecordsBubbleDrawX
            && Event::mouseDisplayX < BubbleView::caravanTradeRecordsBubbleDrawX + BubbleView::caravanTradeRecordsBubbleWidth
            && Event::mouseDisplayY > BubbleView::caravanTradeRecordsBubbleDrawY
            && Event::mouseDisplayY < BubbleView::caravanTradeRecordsBubbleDrawY + BubbleView::caravanTradeRecordsBubbleHeight)
    {
        int x = Event::mouseDisplayX - BubbleView::caravanTradeRecordsBubbleDrawX;
        int y = Event::mouseDisplayY - BubbleView::caravanTradeRecordsBubbleDrawY;

        int xCell = x/Tile::WIDTH;
        int yCell = y/(Tile::HEIGHT+BubbleView::caravanTradeRecordsBubbleRowSpacing);

        int ritRecordRowMin = 0;
        int ritRecordRowMax = 0;
        for(std::vector<TradeRecord*>::reverse_iterator rit = BubbleView::currentCaravan->tradeRecords.rbegin(); rit != BubbleView::currentCaravan->tradeRecords.rend(); ++rit)
        {
            ritRecordRowMax = ritRecordRowMin + (*rit)->numRows-1;
            if(yCell >= ritRecordRowMin && yCell <= ritRecordRowMax)
            {
                if(x < BubbleView::caravanTradeRecordsBubblePlaceNameWidth)
                {
                    Place::places[(*rit)->location]->AllBubblesNeedUpdate();
                    OverworldLockCameraPlace(Place::places[(*rit)->location]);

                    BubbleView::OpenEncyclopediaBubble(Display::WIDTH/2 - encyclopediaBubbleWidth/2,
                                                       Display::HEIGHT/2 + 2*Tile::HEIGHT,
                                                       EN_CAT_PLACES, (*rit)->location);
                }
                else // x >= caravanTradeRecordsBubblePlaceNameWidth
                {
                    xCell -= BubbleView::caravanTradeRecordsBubblePlaceNameWidth/Tile::WIDTH;
                    yCell -= ritRecordRowMin;

                    unsigned position = yCell*((*rit)->maxCols) + xCell;
                    if(position < (*rit)->tradeQuantities.size())
                    {
                        std::map<int,int>::iterator it = (*rit)->tradeQuantities.begin();
                        std::advance(it, position);

                        BubbleView::OpenEncyclopediaBubble(Event::mouseDisplayX, Event::mouseDisplayY, EN_CAT_CARGO, (*it).first);
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
    if(Event::mouseDisplayX > BubbleView::caravanPathfindingBubbleDrawX
            && Event::mouseDisplayX < BubbleView::caravanPathfindingBubbleDrawX + BubbleView::caravanPathfindingBubbleWidth
            && Event::mouseDisplayY > BubbleView::caravanPathfindingBubbleDrawY
            && Event::mouseDisplayY < BubbleView::caravanPathfindingBubbleDrawY + BubbleView::caravanPathfindingBubbleHeight - Resource::TEXT_HEIGHT_8)
    {
        int x = Event::mouseDisplayX - BubbleView::caravanPathfindingBubbleDrawX;

        int xCell = x/Tile::WIDTH; // The representation of cities is two tiles wide; every third tile is the red arrow and should not be clickable.
        if(xCell %3 != 2)
        {
            unsigned position = xCell/3;
            int placeId = BubbleView::currentCaravan->worldGraph.path[position];

            Place::places[placeId]->AllBubblesNeedUpdate();

            SetCameraCenterDestination(Place::places[placeId]->overworldXPosition,
                                       Place::places[placeId]->overworldYPosition);

            BubbleView::OpenEncyclopediaBubble(Display::WIDTH/2 - encyclopediaBubbleWidth/2,
                                               Display::HEIGHT/2 + 2*Tile::HEIGHT,
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
    if(Event::mouseDisplayX > BubbleView::placeCaravanseraiDrawX
            && Event::mouseDisplayX < BubbleView::placeCaravanseraiDrawX + BubbleView::placeCaravanseraiWidth
            && Event::mouseDisplayY > BubbleView::placeCaravanseraiDrawY
            && Event::mouseDisplayY < BubbleView::placeCaravanseraiDrawY + BubbleView::placeCaravanseraiHeight)
    {
        int x = Event::mouseDisplayX - BubbleView::placeCaravanseraiDrawX;
        int y = Event::mouseDisplayY - BubbleView::placeCaravanseraiDrawY;

        int xCell = x/Tile::WIDTH;
        int yCell = y/Tile::HEIGHT;

        unsigned position = yCell*(BubbleView::placeCaravanseraiNumCols) + xCell;

        if(position < BubbleView::currentPlace->caravanserai.size())
        {
            BubbleView::currentPlace->caravanserai[position]->AllBubblesNeedUpdate();
            BubbleView::currentCaravan = BubbleView::currentPlace->caravanserai[position];
            //OverworldLockCameraCaravan(BubbleView::currentPlace->caravanserai[position]); // Already unlocks camera from place
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
    if(Event::mouseDisplayX > BubbleView::placeMarketBubbleDrawX
            && Event::mouseDisplayX < BubbleView::placeMarketBubbleDrawX + BubbleView::placeMarketBubbleWidth
            && Event::mouseDisplayY > BubbleView::placeMarketBubbleDrawY
            && Event::mouseDisplayY < BubbleView::placeMarketBubbleDrawY + BubbleView::placeMarketBubbleHeight)
    {
        int x = Event::mouseDisplayX - BubbleView::placeMarketBubbleDrawX;
        int y = Event::mouseDisplayY - BubbleView::placeMarketBubbleDrawY;

        int xCell = x/Tile::WIDTH;
        int yCell = y/(Tile::HEIGHT+BubbleView::placeMarketBubbleRowSpacing);

        unsigned position = yCell*(BubbleView::placeMarketBubbleNumCols) + xCell;

        if(position < BubbleView::currentPlace->market.cargo.size())
        {
            std::map<int,float>::iterator it = BubbleView::currentPlace->market.cargo.begin();
            std::advance(it, position);

            BubbleView::OpenEncyclopediaBubble(Event::mouseDisplayX, Event::mouseDisplayY, EN_CAT_CARGO, (*it).first);
        }

        return true;
    }
    else
        return false;
}

bool MouseLeftOnPlaceIndustriesBubble()
{
    if(Event::mouseDisplayX > BubbleView::placeIndustriesBubbleDrawX
            && Event::mouseDisplayX < BubbleView::placeIndustriesBubbleDrawX + BubbleView::placeIndustriesBubbleWidth
            && Event::mouseDisplayY > BubbleView::placeIndustriesBubbleDrawY
            && Event::mouseDisplayY < BubbleView::placeIndustriesBubbleDrawY + BubbleView::placeIndustriesBubbleHeight)
    {
        std::cout << "Unimplemented" << std::endl;

        return true;
    }
    else
        return false;
}

void SetCameraCenterDestination(float x, float y)
{
    //BubbleView::currentCaravan = nullptr; // Don't nullify this. Needed to peruse pathfinding bubble locations without it closing
    BubbleView::currentPlace = nullptr;

    OverworldUnlockCamera();

    Camera::SetDestination(x - Display::WIDTH/2, y - Display::HEIGHT/2);

    ///overworldCameraXDestination = x - Display::WIDTH/2;
    ///overworldCameraYDestination = y - Display::HEIGHT/2;

    ///overworldCameraApproachingDestination = true;
}

void AttemptCameraLockOn()
{
    for(std::map<int,Place*>::iterator it = Place::places.begin(); it != Place::places.end(); ++it)
    {
        float x = (*it).second->overworldXPosition;
        float y = (*it).second->overworldYPosition;
        float w = Place::OVERWORLD_SPRITE_W;
        float h = Place::OVERWORLD_SPRITE_H;

        if((Camera::xPosition + Display::WIDTH/2) > x - w/2
                && (Camera::xPosition + Display::WIDTH/2) < x + w/2
                && (Camera::yPosition + Display::HEIGHT/2) > y - h/2
                && (Camera::yPosition + Display::HEIGHT/2) < y + h/2)
        {
            OverworldLockCameraPlace((*it).second);
            BubbleView::currentPlace = ((*it).second);
            (*it).second->AllBubblesNeedUpdate();

            Camera::xPosition = x - Display::WIDTH/2;
            Camera::yPosition = y - Display::HEIGHT/2;
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

            if((Camera::xPosition + Display::WIDTH/2) > x - w/2
                    && (Camera::xPosition + Display::WIDTH/2) < x + w/2
                    && (Camera::yPosition + Display::HEIGHT/2) > y - h/2
                    && (Camera::yPosition + Display::HEIGHT/2) < y + h/2)
            {
                OverworldLockCameraCaravan(*it);
                BubbleView::currentCaravan = (*it);
                break;
            }
        }
    }
}
