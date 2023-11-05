#include "allegrocustom.h"
ALLEGRO_COLOR COL_EARTHEN_0;
ALLEGRO_COLOR COL_EARTHEN_1;
ALLEGRO_COLOR COL_EARTHEN_2;
ALLEGRO_COLOR COL_EARTHEN_3;
ALLEGRO_COLOR COL_EARTHEN_4;

ALLEGRO_COLOR COL_STEEL_0;
ALLEGRO_COLOR COL_STEEL_1;
ALLEGRO_COLOR COL_STEEL_2;
ALLEGRO_COLOR COL_STEEL_3;
ALLEGRO_COLOR COL_STEEL_4;

ALLEGRO_COLOR COL_RUST_0;
ALLEGRO_COLOR COL_RUST_1;
ALLEGRO_COLOR COL_RUST_2;
ALLEGRO_COLOR COL_RUST_3;

ALLEGRO_COLOR COL_FLAME_0;
ALLEGRO_COLOR COL_FLAME_1;
ALLEGRO_COLOR COL_FLAME_2;
ALLEGRO_COLOR COL_FLAME_3;
ALLEGRO_COLOR COL_FLAME_4;

ALLEGRO_COLOR COL_CARAMEL_0;
ALLEGRO_COLOR COL_CARAMEL_1;
ALLEGRO_COLOR COL_CARAMEL_2;
ALLEGRO_COLOR COL_CARAMEL_3;
ALLEGRO_COLOR COL_CARAMEL_4;

ALLEGRO_COLOR COL_ELECTRIC_0;
ALLEGRO_COLOR COL_ELECTRIC_1;
ALLEGRO_COLOR COL_ELECTRIC_2;
ALLEGRO_COLOR COL_ELECTRIC_3;
ALLEGRO_COLOR COL_ELECTRIC_4;

ALLEGRO_COLOR COL_JADE_0;
ALLEGRO_COLOR COL_JADE_1;
ALLEGRO_COLOR COL_JADE_2;
ALLEGRO_COLOR COL_JADE_3;
ALLEGRO_COLOR COL_JADE_4;

ALLEGRO_COLOR COL_WIND_0;
ALLEGRO_COLOR COL_WIND_1;
ALLEGRO_COLOR COL_WIND_2;
ALLEGRO_COLOR COL_WIND_3;
ALLEGRO_COLOR COL_WIND_4;

ALLEGRO_COLOR COL_AZURE_0;
ALLEGRO_COLOR COL_AZURE_1;
ALLEGRO_COLOR COL_AZURE_2;
ALLEGRO_COLOR COL_AZURE_3;
ALLEGRO_COLOR COL_AZURE_4;

ALLEGRO_COLOR COL_OCEAN_0;
ALLEGRO_COLOR COL_OCEAN_1;
ALLEGRO_COLOR COL_OCEAN_2;
ALLEGRO_COLOR COL_OCEAN_3;
ALLEGRO_COLOR COL_OCEAN_4;

ALLEGRO_COLOR COL_VIOLET_0;
ALLEGRO_COLOR COL_VIOLET_1;
ALLEGRO_COLOR COL_VIOLET_2;
ALLEGRO_COLOR COL_VIOLET_3;
ALLEGRO_COLOR COL_VIOLET_4;

ALLEGRO_COLOR COL_GUM_0;
ALLEGRO_COLOR COL_GUM_1;
ALLEGRO_COLOR COL_GUM_2;
ALLEGRO_COLOR COL_GUM_3;

ALLEGRO_COLOR COL_FLESH_0;
ALLEGRO_COLOR COL_FLESH_1;
ALLEGRO_COLOR COL_FLESH_2;
ALLEGRO_COLOR COL_FLESH_3;
ALLEGRO_COLOR COL_FLESH_4;
ALLEGRO_COLOR COL_FLESH_5;

ALLEGRO_COLOR currentClearColor;

void AllegroCustomColours()
{

    COL_EARTHEN_0 =  al_map_rgb( 46,  34,  47);
    COL_EARTHEN_1 =  al_map_rgb( 62,  53,  70);
    COL_EARTHEN_2 =  al_map_rgb( 98,  85, 101);
    COL_EARTHEN_3 =  al_map_rgb(150, 108, 108);
    COL_EARTHEN_4 =  al_map_rgb(171, 148, 122);

    COL_STEEL_0 =    al_map_rgb(105,  79,  98);
    COL_STEEL_1 =    al_map_rgb(127, 112, 138);
    COL_STEEL_2 =    al_map_rgb(155, 171, 178);
    COL_STEEL_3 =    al_map_rgb(199, 220, 208);
    COL_STEEL_4 =    al_map_rgb(255, 255, 255);

    COL_RUST_0 =     al_map_rgb(110,  39, 39);
    COL_RUST_1 =     al_map_rgb(179,  56, 49);
    COL_RUST_2 =     al_map_rgb(234,  79, 54);
    COL_RUST_3 =     al_map_rgb(245, 125, 74);

    COL_FLAME_0 =    al_map_rgb(174,  35, 52);
    COL_FLAME_1 =    al_map_rgb(232,  59, 59);
    COL_FLAME_2 =    al_map_rgb(251, 107, 29);
    COL_FLAME_3 =    al_map_rgb(247, 150, 23);
    COL_FLAME_4 =    al_map_rgb(249, 194, 43);

    COL_CARAMEL_0 =  al_map_rgb(122,  48, 69);
    COL_CARAMEL_1 =  al_map_rgb(158,  69, 57);
    COL_CARAMEL_2 =  al_map_rgb(205, 104, 61);
    COL_CARAMEL_3 =  al_map_rgb(230, 144, 78);
    COL_CARAMEL_4 =  al_map_rgb(251, 185, 84);

    COL_ELECTRIC_0 = al_map_rgb(76,   62,  36);
    COL_ELECTRIC_1 = al_map_rgb(103, 102,  51);
    COL_ELECTRIC_2 = al_map_rgb(162, 169,  71);
    COL_ELECTRIC_3 = al_map_rgb(213, 224,  75);
    COL_ELECTRIC_4 = al_map_rgb(251, 255, 134);

    COL_JADE_0 =     al_map_rgb( 22,  90,  76);
    COL_JADE_1 =     al_map_rgb( 35, 144,  99);
    COL_JADE_2 =     al_map_rgb( 30, 188, 115);
    COL_JADE_3 =     al_map_rgb(145, 219, 105);
    COL_JADE_4 =     al_map_rgb(205, 223, 108);

    COL_WIND_0 = al_map_rgb( 49,  54,  56);
    COL_WIND_1 = al_map_rgb( 55,  78,  74);
    COL_WIND_2 = al_map_rgb( 84, 126, 100);
    COL_WIND_3 = al_map_rgb(146, 169, 132);
    COL_WIND_4 = al_map_rgb(178, 186, 144);

    COL_AZURE_0 = al_map_rgb( 11,  94, 101);
    COL_AZURE_1 = al_map_rgb( 11, 138, 143);
    COL_AZURE_2 = al_map_rgb( 14, 175, 155);
    COL_AZURE_3 = al_map_rgb( 48, 225, 185);
    COL_AZURE_4 = al_map_rgb(143, 248, 226);

    COL_OCEAN_0 = al_map_rgb( 50,  51, 83);
    COL_OCEAN_1 = al_map_rgb( 72,  74, 119);
    COL_OCEAN_2 = al_map_rgb( 77, 101, 180);
    COL_OCEAN_3 = al_map_rgb( 77, 155, 230);
    COL_OCEAN_4 = al_map_rgb(143, 211, 255);

    COL_VIOLET_0 = al_map_rgb( 69,  41,  63);
    COL_VIOLET_1 = al_map_rgb(107,  62, 117);
    COL_VIOLET_2 = al_map_rgb(144,  94, 169);
    COL_VIOLET_3 = al_map_rgb(168, 132, 243);
    COL_VIOLET_4 = al_map_rgb(234, 173, 237);

    COL_GUM_0 = al_map_rgb(117,  60,  84);
    COL_GUM_1 = al_map_rgb(162,  75, 111);
    COL_GUM_2 = al_map_rgb(207, 101, 127);
    COL_GUM_3 = al_map_rgb(237, 128, 153);

    COL_FLESH_0 = al_map_rgb(131,  28,  93);
    COL_FLESH_1 = al_map_rgb(195,  36,  84);
    COL_FLESH_2 = al_map_rgb(240,  79, 120);
    COL_FLESH_3 = al_map_rgb(246, 129, 129);
    COL_FLESH_4 = al_map_rgb(252, 167, 144);
    COL_FLESH_5 = al_map_rgb(253, 203, 176);
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

void string_al_draw_multiline_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, float max_width, float line_height, int flags, std::string text)
{
    const char *c = text.c_str();
    al_draw_multiline_text(font, color, x, y, max_width, line_height, flags, c);
}

/// Mark Oates' do_multiline_text functions
bool multiline_text_draw_callback(int line_num, const char* line, int size, void* user_data)
{
   *((int*)user_data) = line_num;
   return true;
}

int count_num_lines_will_render(ALLEGRO_FONT* font, float max_width, std::string text)
{
   if (text.empty()) return 0;

   int multiline_text_line_number = 0;
   al_do_multiline_text(font, max_width, text.c_str(), multiline_text_draw_callback, &multiline_text_line_number);

   // multiline_text_line_number is now modified, and should now be set to the number of lines drawn
   return multiline_text_line_number + 1;
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
