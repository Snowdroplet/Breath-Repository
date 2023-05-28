#include "inventory.h"

Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

void Inventory::SetStock(int a, int b)
{
    cargo[a] = b;

    if(cargo[a] <= 0)
        cargo.erase(a);
}

void Inventory::AddStock(int a, int b)
{
    if(cargo.count(a) == 0) // Probably unnecessary, but whatever
        cargo[a] = 0;

    cargo[a] += b;
}

void Inventory::RemoveStock(int a, int b)
{
// It doesn't check if b is more than cargo[a], so do your checking before calling RemoveStock

        cargo[a] -= b;
        if(cargo[a] <= 0)
            cargo.erase(a);
}

/*

void Inventory::DrawVertical(int rows, float x, float y)
{
    int column = 0;
    int row = 0;

    //int drawRangeMin = inventoryRange[activeTab][IT_RANGE_FIRST];
    //int drawRangeMax = inventoryRange[activeTab][IT_RANGE_LAST];

    for(std::map<int,int>::iterator it = cargoInTab.begin(); it != cargoInTab.end(); it++)
    {

            std::string quantity = std::to_string(it->second);

            al_draw_bitmap_region(cargoPng,
                                  (it->first)*CARGO_W,
                                  0,
                                  CARGO_W,
                                  CARGO_H,
                                  x + column*CARGO_W,
                                  y + row*CARGO_H,
                                  0);

            al_draw_text(builtin,
                         al_map_rgb(255,255,255),
                         x + column*CARGO_W + CARGO_W,
                         y + row*CARGO_H + CARGO_H - FONT_BUILTIN_H,
                         ALLEGRO_ALIGN_RIGHT,
                         quantity.c_str());

            row++;
            if(row > rows-1)
            {
                row = 0;
                column++;
            }
    }
}

*/

/*
void Inventory::DrawHorizontal(int cols, float x, float y)
{

}
*/

/*

void Inventory::RefreshCargoInTab()
{
    cargoInTab = std::map<int,int> (cargo.lower_bound(inventoryRange[activeTab][IT_RANGE_FIRST]), cargo.upper_bound(inventoryRange[activeTab][IT_RANGE_LAST]));
}

*/

/*
int Inventory::GetItemTypeAtInput(unsigned input)
{
    if(input < cargoInTab.size())
    {
        std::map<int,int>::iterator it = cargoInTab.begin();
        std::advance(it,input);
        return it->first;
    }

    else
        return IT_NONE;
}
*/
