#include "allegrocustom.h"

ALLEGRO_COLOR COL_WHITE;
ALLEGRO_COLOR COL_DARK_WHITE;

ALLEGRO_COLOR COL_GRAY;
ALLEGRO_COLOR COL_DARK_GRAY;

ALLEGRO_COLOR COL_BLACK;

ALLEGRO_COLOR COL_RED;

ALLEGRO_COLOR COL_ORANGE;

ALLEGRO_COLOR COL_YELLOW;
ALLEGRO_COLOR COL_LIGHT_YELLOW;
ALLEGRO_COLOR COL_DARK_YELLOW;

ALLEGRO_COLOR COL_GREEN;
ALLEGRO_COLOR COL_LIGHT_GREEN;

ALLEGRO_COLOR COL_BLUE;

ALLEGRO_COLOR COL_INDIGO;
ALLEGRO_COLOR COL_VIOLET;

ALLEGRO_COLOR COL_BROWN;
ALLEGRO_COLOR COL_DARK_BROWN;

ALLEGRO_COLOR COL_PEN_INK;

ALLEGRO_COLOR currentClearColor;

void AllegroCustomColours()
{
    COL_WHITE = al_map_rgb(255,255,255);
    COL_DARK_WHITE = al_map_rgb(200,200,200);
    COL_GRAY = al_map_rgb(180,180,180);
    COL_DARK_GRAY = al_map_rgb(128,128,128);
    COL_BLACK = al_map_rgb(0,0,0);

    COL_RED = al_map_rgb(127,0,0);

    COL_ORANGE = al_map_rgb(255,106,0);

    COL_YELLOW = al_map_rgb(255,216,0);
    COL_LIGHT_YELLOW = al_map_rgb(255,255,102);
    COL_DARK_YELLOW = al_map_rgb(102, 102, 0);

    COL_GREEN = al_map_rgb(0,127,14);
    COL_LIGHT_GREEN = al_map_rgb(195,214,87);

    COL_BLUE = al_map_rgb(0,148,255);

    COL_INDIGO = al_map_rgb(220,220,255);
    COL_VIOLET = al_map_rgb(178,0,255);

    COL_BROWN = al_map_rgb(226,173,110);
    COL_DARK_BROWN = al_map_rgb(147,103,77);

    COL_PEN_INK = al_map_rgb(0,15,84);

    currentClearColor = COL_WHITE;

}

/*
void c_al_draw_centered_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags)
{
    al_draw_bitmap(bitmap,
                   dx-al_get_bitmap_width(bitmap)/2, dy-al_get_bitmap_height(bitmap)/2,
                   flags);
}

void c_al_draw_rotated_centered_bitmap(ALLEGRO_BITMAP *bitmap, float cx, float cy, float dx, float dy, float angle, int flags)
{
    al_draw_rotated_bitmap(bitmap,
                           cx, cy,
                           dx-al_get_bitmap_width(bitmap)/2, dy-al_get_bitmap_height(bitmap)/2,
                           angle, flags);
}
*/

int string_al_get_text_width(const ALLEGRO_FONT *f, std::string str)
{
    const char *c = str.c_str();
    return al_get_text_width(f, c);
}

void string_al_draw_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, int flags, std::string text)
{
    const char *c = text.c_str();
    al_draw_text(font, color, x, y, flags, c);
}

/*
int s_al_show_native_message_box(ALLEGRO_DISPLAY *display,
                                 std::string title, std::string heading, std::string text,
                                 char const *buttons, int flags)
{
    const char *ctitle = title.c_str();
    const char *cheading = heading.c_str();
    const char *ctext = text.c_str();

    return al_show_native_message_box(display, ctitle, cheading, ctext, buttons, flags);
}
*/
