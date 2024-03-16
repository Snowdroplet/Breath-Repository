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
#include "lockon.h"
#include "resource.h"
#include "scene.h"
#include "being.h"
#include "caravan.h"
#include "road.h"
#include "place.h"
#include "overworld.h"
#include "calendar.h"
#include "configuration.h"
#include "inventoryindex.h"
#include "encyclopediaindex.h"

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
void OverworldLockCameraPlace(Place *whichPlace);
void OverworldLockCameraCaravan(Caravan *whichCaravan);
void OverworldUnlockCamera();
void OverworldUnlockCameraCaravan();
void OverworldUnlockCameraPlace();

void OverworldDrawGridUnderlay();
void OverworldDrawGridCameraCrosshair();
//void OverworldDrawGridMouseCrosshair(float mouseZoomedX, float mouseZoomedY);
void OverworldDrawGridText(float mouseTransformedX, float mouseTransformedY);

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

    AllegroCustom::Initialize();

    PHYSFS_init(argv[0]);
    if(!PHYSFS_mount("./gamedata.zip", "/", 1))
    {
        al_show_native_message_box(al_get_current_display(),"Initialization Failed", "", "gamedata.zip not found!", NULL, 0);
        return false;
    }

    al_set_physfs_file_interface();
    Resource::LoadFontResources();
    Resource::LoadImageResources();
    Resource::LoadAudioResources();

    al_set_standard_file_interface();
    Configuration::LoadConfigurations();
    InventoryIndex::LoadConfigurations();
    PlaceIndex::LoadConfigurations();
    EncyclopediaIndex::LoadConfigurations();

    Configuration::UnloadConfigurations();

    Initialize();

    al_start_timer(Timer::FPSTimer);

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
            Camera::overworldCameraMousePanningDisabled = false;

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
            Camera::overworldCameraMousePanningDisabled = true;


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
            al_clear_to_color(AllegroCustom::currentClearColor);
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
/*
    al_set_standard_file_interface();

    ALLEGRO_CONFIG* testConfig = al_load_config_file("configs/testConfig.cfg");
    if(!testConfig)
        std::cout << "beep beep" << std::endl;
    else
        std::cout << "success" << std::endl;

    al_add_config_section(testConfig, "Test Data Section"); // Doesn't seem to work
    al_add_config_comment(testConfig, "Test Data Section", "Some comment"); // Doesn't seem to work
    al_set_config_value(  testConfig, "Test Data Section", "Number of mushrooms", "123"); // Doesn't seem to work
    al_save_config_file("configs/testConfig.cfg", testConfig); // Unknown whether it works
    al_destroy_config(testConfig);

    ALLEGRO_CONFIG* testSaveConfig = al_create_config();
    al_save_config_file("configs/testSaveConfig.cfg", testSaveConfig);
    al_destroy_config(testSaveConfig);
*/
    Scene::Initialize();
    Camera::Initialize();
    LockOn::Initialize();
    BubbleView::Initialize();
    Calendar::Initialize(12,17,2,2024);

    for(unsigned i = PlaceIndex::PL_MARKER_FIRST; i <= PlaceIndex::PL_MARKER_LAST; i++)
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
    AllegroCustom::currentClearColor = AllegroCustom::COL_JADE_3;

    OverworldBeginParallelBackgroundAudio();
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
        // Priority: 1) Close enyclopedia. 2) Close being status bubble. 3) Close caravan/place bubbles + unlock camera.

        if(BubbleView::encyclopediaBubbleOpen)
        {
            BubbleView::CloseEncyclopediaBubble();
            std::cout << "Closing encyclopedia bubble" << std::endl;
        }
        else // ! EncyclopediaBubbleOpen
        {
            if(BubbleView::BubbleView::beingStatusBubbleOpen)
            {
                BubbleView::CloseBeingStatusBubble();
                std::cout << "Closing being status bubble" << std::endl;
            }
            else // ! BubbleView::beingStatusBubbleOpen
            {
                if(BubbleView::currentCaravan != nullptr || BubbleView::currentPlace != nullptr) // either caravan/place bubbles are open
                {
                    BubbleView::currentCaravan = nullptr;
                    BubbleView::currentPlace = nullptr;
                    std::cout << "Closing caravan/place bubbles" << std::endl;
                }

                OverworldUnlockCamera();
                std::cout << "unlocking camera" << std::endl;
            }
        }
        //Event::keyInput[Event::KEY_ESC] = false;
    }


    /// Camera panning
    if(!LockOn::isLockedOn)
    {
        if(!Camera::overworldCameraMousePanningDisabled)
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
        if(LockOn::IsLockedOnPlace)
            BubbleView::currentPlace = LockOn::whichPlace;
        else if(LockOn::isLockedOnCaravan)
        {
            BubbleView::currentCaravan = LockOn::whichCaravan;
            if(BubbleView::currentCaravan->atPlace)
                BubbleView::currentPlace = BubbleView::currentCaravan->whichPlace;
        }
    }
}

void ProgressWorld()
{
    if(Scene::activeScene == Scene::SCENE_OVERWORLD)
    {
        Calendar::AdvanceHourFrame();
        Calendar::UpdateCalendarText();

        for(std::map<int,Place*>::iterator it = Place::places.begin(); it != Place::places.end(); ++it)
        {
            ((*it).second)->ProgressFlyingTexts();
            ((*it).second)->ProgressPlaceIndustriesBubbleProgressBars();

            if(Calendar::hourChangeTick)
            {
                ((*it).second)->ProgressProduction();

                ((*it).second)->ProgressMaintainenceConsumption();
                ((*it).second)->UpdateSurplusesDescending();
                ((*it).second)->UpdateDeficitsDescending();
            }

            if(Calendar::dayChangeTick)
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
        if(LockOn::isLockedOnCaravan)
        {
            Camera::xPosition = LockOn::whichCaravan->overworldXPosition-Display::WIDTH/2;
            Camera::yPosition = LockOn::whichCaravan->overworldYPosition-Display::HEIGHT/2;
        }
        else // if ! isLockedOnCaravan
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

        Calendar::DrawCalendar();
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

            BubbleView::OpenEncyclopediaBubble(Event::mouseDisplayX, Event::mouseDisplayY, EncyclopediaIndex::EN_CAT_CARGO, (*it).first);
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

                    BubbleView::OpenEncyclopediaBubble(Display::WIDTH/2 - BubbleView::encyclopediaBubbleWidth/2,
                                                       Display::HEIGHT/2 + 2*Tile::HEIGHT,
                                                       EncyclopediaIndex::EN_CAT_PLACES, (*rit)->location);
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

                        BubbleView::OpenEncyclopediaBubble(Event::mouseDisplayX, Event::mouseDisplayY, EncyclopediaIndex::EN_CAT_CARGO, (*it).first);
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

            BubbleView::OpenEncyclopediaBubble(Display::WIDTH/2 - BubbleView::encyclopediaBubbleWidth/2,
                                               Display::HEIGHT/2 + 2*Tile::HEIGHT,
                                               EncyclopediaIndex::EN_CAT_PLACES, placeId);
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

            BubbleView::OpenEncyclopediaBubble(Event::mouseDisplayX, Event::mouseDisplayY, EncyclopediaIndex::EN_CAT_CARGO, (*it).first);
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

    if(!LockOn::IsLockedOnPlace) // If a Place wasn't locked on to, search for a caravan.
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


void OverworldLockCameraPlace(Place *whichPlace)
{
    OverworldUnlockCameraCaravan();

    LockOn::whichPlace = whichPlace;
    LockOn::IsLockedOnPlace = true;
    LockOn::isLockedOn = true;

    BubbleView::currentPlace = whichPlace;

    OverworldSwapParallelBackgroundAudioToPlace();
}

void OverworldLockCameraCaravan(Caravan *whichCaravan)
{
    OverworldUnlockCameraPlace();

    LockOn::whichCaravan = whichCaravan;
    LockOn::isLockedOnCaravan = true;
    LockOn::isLockedOn = true;

    BubbleView::currentCaravan = whichCaravan;

    OverworldSwapParallelBackgroundAudioToField();
}

void OverworldUnlockCameraCaravan()
{
    LockOn::whichCaravan = nullptr;
    LockOn::isLockedOnCaravan = false;
}

void OverworldUnlockCameraPlace()
{
    LockOn::whichPlace = nullptr;
    LockOn::IsLockedOnPlace = false;
}

void OverworldUnlockCamera()
{
    OverworldUnlockCameraPlace();
    OverworldUnlockCameraCaravan();
    LockOn::isLockedOn = false;
}

void OverworldDrawGridUnderlay()
{

    for(int x = 0; x <= Display::WIDTH/Tile::WIDTH; x++) //Columns
    {
        int cxp = Camera::xPosition;
        int tw = Tile::WIDTH;

        al_draw_line(x*Tile::WIDTH - cxp%tw,
                     0,
                     x*Tile::WIDTH - cxp%tw,
                     Display::HEIGHT,
                     COLKEY_DEBUG_GRID_UNDERLAY,1);
    }

    for(int y = 0; y <= Display::HEIGHT/Tile::WIDTH; y++) //Rows
    {
        int cyp = Camera::yPosition;
        int th = Tile::HEIGHT;

        al_draw_line(0,
                     y*Tile::HEIGHT - cyp%th,
                     Display::WIDTH,
                     y*Tile::HEIGHT - cyp%th,
                     COLKEY_DEBUG_GRID_UNDERLAY,1);
    }
}

void OverworldDrawGridCameraCrosshair()
{
    if(!LockOn::isLockedOn)
    {
        al_draw_line(Display::WIDTH/2,0,Display::WIDTH/2,Display::HEIGHT,COLKEY_CAMERA_CROSSHAIR_FREE,1);
        al_draw_line(0,Display::HEIGHT/2,Display::WIDTH,Display::HEIGHT/2,COLKEY_CAMERA_CROSSHAIR_FREE,1);
    }
    else
    {
        al_draw_line(Display::WIDTH/2,0,Display::WIDTH/2,Display::HEIGHT,COLKEY_CAMERA_CROSSHAIR_LOCKED,1);
        al_draw_line(0,Display::HEIGHT/2,Display::WIDTH,Display::HEIGHT/2,COLKEY_CAMERA_CROSSHAIR_LOCKED,1);
    }
}

/*
void OverworldDrawGridMouseCrosshair(float mouseDisplayX, float mouseDisplayY)
{
    al_draw_line(mouseDisplayX, 0, mouseDisplayX, Display::HEIGHT, COLKEY_MOUSE_CROSSHAIR,1);
    al_draw_line(0, mouseDisplayY, Display::WIDTH, mouseDisplayY, COLKEY_MOUSE_CROSSHAIR,1);
}
*/

void OverworldDrawGridText(float mouseTransformedX, float mouseTransformedY)
{
    int cameraCrosshairXPosition = Camera::xPosition+Display::WIDTH/2;
    int cameraCrosshairYPosition = Camera::yPosition+Display::HEIGHT/2;

    int cameraCrosshairXPositionCell = cameraCrosshairXPosition/Tile::WIDTH;
    int cameraCrosshairYPositionCell = cameraCrosshairYPosition/Tile::HEIGHT;

    int mouseCrosshairXPosition = Camera::xPosition+mouseTransformedX;
    int mouseCrosshairYPosition = Camera::yPosition+mouseTransformedY;

    int mouseCrosshairXPositionCell = mouseCrosshairXPosition/Tile::WIDTH;
    int mouseCrosshairYPositionCell = mouseCrosshairYPosition/Tile::HEIGHT;

    int zoomPercentage = Camera::zoomScale*100;

    std::string cameraCrosshairPositionString = "CAMERA: (" + std::to_string(cameraCrosshairXPosition) + ", " + std::to_string(cameraCrosshairYPosition) + ") : ("
            + std::to_string(cameraCrosshairXPositionCell) + ", " + std::to_string(cameraCrosshairYPositionCell) + ") "
            + std::to_string(zoomPercentage) + "%";

    std::string mouseCrosshairPositionString = "MOUSE:  (" + std::to_string(mouseCrosshairXPosition) + ", " + std::to_string(mouseCrosshairYPosition) + ") : ("
            + std::to_string(mouseCrosshairXPositionCell) + ", " + std::to_string(mouseCrosshairYPositionCell) + ") "
            + std::to_string(zoomPercentage) + "%";

    if(!LockOn::isLockedOn)
        AllegroCustom::string_al_draw_text(Resource::builtin8,COLKEY_CAMERA_CROSSHAIR_FREE,0,0,ALLEGRO_ALIGN_LEFT,cameraCrosshairPositionString);
    else
        AllegroCustom::string_al_draw_text(Resource::builtin8,COLKEY_CAMERA_CROSSHAIR_LOCKED,0,0,ALLEGRO_ALIGN_LEFT,cameraCrosshairPositionString);

    AllegroCustom::string_al_draw_text(Resource::builtin8,COLKEY_MOUSE_CROSSHAIR,0,Resource::TEXT_HEIGHT_8,ALLEGRO_ALIGN_LEFT,mouseCrosshairPositionString);

}
