#ifndef ALLEGROCUSTOM_H_INCLUDED
#define ALLEGROCUSTOM_H_INCLUDED

#include <string>

//#include <allegro5/allegro.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_native_dialog.h>

struct AllegroCustom
{
    static ALLEGRO_COLOR COL_EARTHEN_0;
    static ALLEGRO_COLOR COL_EARTHEN_1;
    static ALLEGRO_COLOR COL_EARTHEN_2;
    static ALLEGRO_COLOR COL_EARTHEN_3;
    static ALLEGRO_COLOR COL_EARTHEN_4;

    static ALLEGRO_COLOR COL_STEEL_0;
    static ALLEGRO_COLOR COL_STEEL_1;
    static ALLEGRO_COLOR COL_STEEL_2;
    static ALLEGRO_COLOR COL_STEEL_3;
    static ALLEGRO_COLOR COL_STEEL_4;

    static ALLEGRO_COLOR COL_RUST_0;
    static ALLEGRO_COLOR COL_RUST_1;
    static ALLEGRO_COLOR COL_RUST_2;
    static ALLEGRO_COLOR COL_RUST_3;

    static ALLEGRO_COLOR COL_FLAME_0;
    static ALLEGRO_COLOR COL_FLAME_1;
    static ALLEGRO_COLOR COL_FLAME_2;
    static ALLEGRO_COLOR COL_FLAME_3;
    static ALLEGRO_COLOR COL_FLAME_4;

    static ALLEGRO_COLOR COL_CARAMEL_0;
    static ALLEGRO_COLOR COL_CARAMEL_1;
    static ALLEGRO_COLOR COL_CARAMEL_2;
    static ALLEGRO_COLOR COL_CARAMEL_3;
    static ALLEGRO_COLOR COL_CARAMEL_4;

    static ALLEGRO_COLOR COL_ELECTRIC_0;
    static ALLEGRO_COLOR COL_ELECTRIC_1;
    static ALLEGRO_COLOR COL_ELECTRIC_2;
    static ALLEGRO_COLOR COL_ELECTRIC_3;
    static ALLEGRO_COLOR COL_ELECTRIC_4;

    static ALLEGRO_COLOR COL_JADE_0;
    static ALLEGRO_COLOR COL_JADE_1;
    static ALLEGRO_COLOR COL_JADE_2;
    static ALLEGRO_COLOR COL_JADE_3;
    static ALLEGRO_COLOR COL_JADE_4;

    static ALLEGRO_COLOR COL_WIND_0;
    static ALLEGRO_COLOR COL_WIND_1;
    static ALLEGRO_COLOR COL_WIND_2;
    static ALLEGRO_COLOR COL_WIND_3;
    static ALLEGRO_COLOR COL_WIND_4;

    static ALLEGRO_COLOR COL_AZURE_0;
    static ALLEGRO_COLOR COL_AZURE_1;
    static ALLEGRO_COLOR COL_AZURE_2;
    static ALLEGRO_COLOR COL_AZURE_3;
    static ALLEGRO_COLOR COL_AZURE_4;

    static ALLEGRO_COLOR COL_OCEAN_0;
    static ALLEGRO_COLOR COL_OCEAN_1;
    static ALLEGRO_COLOR COL_OCEAN_2;
    static ALLEGRO_COLOR COL_OCEAN_3;
    static ALLEGRO_COLOR COL_OCEAN_4;

    static ALLEGRO_COLOR COL_VIOLET_0;
    static ALLEGRO_COLOR COL_VIOLET_1;
    static ALLEGRO_COLOR COL_VIOLET_2;
    static ALLEGRO_COLOR COL_VIOLET_3;
    static ALLEGRO_COLOR COL_VIOLET_4;

    static ALLEGRO_COLOR COL_GUM_0;
    static ALLEGRO_COLOR COL_GUM_1;
    static ALLEGRO_COLOR COL_GUM_2;
    static ALLEGRO_COLOR COL_GUM_3;

    static ALLEGRO_COLOR COL_FLESH_0;
    static ALLEGRO_COLOR COL_FLESH_1;
    static ALLEGRO_COLOR COL_FLESH_2;
    static ALLEGRO_COLOR COL_FLESH_3;
    static ALLEGRO_COLOR COL_FLESH_4;
    static ALLEGRO_COLOR COL_FLESH_5;

    static ALLEGRO_COLOR currentClearColor;

    static void Initialize()
    {
        SetCustomColours();

    }

    static void SetCustomColours();

//void c_al_draw_centered_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags);
//void c_al_draw_rotated_centered_bitmap(ALLEGRO_BITMAP *bitmap, float cx, float cy, float dx, float dy, float angle, int flags);

    static int string_al_get_text_width(const ALLEGRO_FONT *f, std::string str);
    static void string_al_draw_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, int flags, std::string text);

    static void string_al_draw_multiline_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, float max_width, float line_height, int flags, std::string text);

/// Mark Oates' do_multiline_text functions
    static bool multiline_text_draw_callback(int line_num, const char* line, int size, void* user_data);
    static int count_num_lines_will_render(ALLEGRO_FONT* font, float max_width, std::string text);

    /*
    int s_al_show_native_message_box(ALLEGRO_DISPLAY *display,
                                     std::string title, std::string heading, std::string text,
                                     char const *buttons, int flags);
    */

};

#endif // ALLEGROCUSTOM_H_INCLUDED
