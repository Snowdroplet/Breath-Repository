#ifndef ALLEGROCUSTOM_H_INCLUDED
#define ALLEGROCUSTOM_H_INCLUDED

#include <string>

//#include <allegro5/allegro.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_native_dialog.h>


extern ALLEGRO_COLOR COL_EARTHEN_0;
extern ALLEGRO_COLOR COL_EARTHEN_1;
extern ALLEGRO_COLOR COL_EARTHEN_2;
extern ALLEGRO_COLOR COL_EARTHEN_3;
extern ALLEGRO_COLOR COL_EARTHEN_4;

extern ALLEGRO_COLOR COL_STEEL_0;
extern ALLEGRO_COLOR COL_STEEL_1;
extern ALLEGRO_COLOR COL_STEEL_2;
extern ALLEGRO_COLOR COL_STEEL_3;
extern ALLEGRO_COLOR COL_STEEL_4;

extern ALLEGRO_COLOR COL_RUST_0;
extern ALLEGRO_COLOR COL_RUST_1;
extern ALLEGRO_COLOR COL_RUST_2;
extern ALLEGRO_COLOR COL_RUST_3;

extern ALLEGRO_COLOR COL_FLAME_0;
extern ALLEGRO_COLOR COL_FLAME_1;
extern ALLEGRO_COLOR COL_FLAME_2;
extern ALLEGRO_COLOR COL_FLAME_3;
extern ALLEGRO_COLOR COL_FLAME_4;

extern ALLEGRO_COLOR COL_CARAMEL_0;
extern ALLEGRO_COLOR COL_CARAMEL_1;
extern ALLEGRO_COLOR COL_CARAMEL_2;
extern ALLEGRO_COLOR COL_CARAMEL_3;
extern ALLEGRO_COLOR COL_CARAMEL_4;

extern ALLEGRO_COLOR COL_ELECTRIC_0;
extern ALLEGRO_COLOR COL_ELECTRIC_1;
extern ALLEGRO_COLOR COL_ELECTRIC_2;
extern ALLEGRO_COLOR COL_ELECTRIC_3;
extern ALLEGRO_COLOR COL_ELECTRIC_4;

extern ALLEGRO_COLOR COL_JADE_0;
extern ALLEGRO_COLOR COL_JADE_1;
extern ALLEGRO_COLOR COL_JADE_2;
extern ALLEGRO_COLOR COL_JADE_3;
extern ALLEGRO_COLOR COL_JADE_4;

extern ALLEGRO_COLOR COL_WIND_0;
extern ALLEGRO_COLOR COL_WIND_1;
extern ALLEGRO_COLOR COL_WIND_2;
extern ALLEGRO_COLOR COL_WIND_3;
extern ALLEGRO_COLOR COL_WIND_4;

extern ALLEGRO_COLOR COL_AZURE_0;
extern ALLEGRO_COLOR COL_AZURE_1;
extern ALLEGRO_COLOR COL_AZURE_2;
extern ALLEGRO_COLOR COL_AZURE_3;
extern ALLEGRO_COLOR COL_AZURE_4;

extern ALLEGRO_COLOR COL_OCEAN_0;
extern ALLEGRO_COLOR COL_OCEAN_1;
extern ALLEGRO_COLOR COL_OCEAN_2;
extern ALLEGRO_COLOR COL_OCEAN_3;
extern ALLEGRO_COLOR COL_OCEAN_4;

extern ALLEGRO_COLOR COL_VIOLET_0;
extern ALLEGRO_COLOR COL_VIOLET_1;
extern ALLEGRO_COLOR COL_VIOLET_2;
extern ALLEGRO_COLOR COL_VIOLET_3;
extern ALLEGRO_COLOR COL_VIOLET_4;

extern ALLEGRO_COLOR COL_GUM_0;
extern ALLEGRO_COLOR COL_GUM_1;
extern ALLEGRO_COLOR COL_GUM_2;
extern ALLEGRO_COLOR COL_GUM_3;

extern ALLEGRO_COLOR COL_FLESH_0;
extern ALLEGRO_COLOR COL_FLESH_1;
extern ALLEGRO_COLOR COL_FLESH_2;
extern ALLEGRO_COLOR COL_FLESH_3;
extern ALLEGRO_COLOR COL_FLESH_4;
extern ALLEGRO_COLOR COL_FLESH_5;

extern ALLEGRO_COLOR currentClearColor;

void AllegroCustomColours();

//void c_al_draw_centered_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags);
//void c_al_draw_rotated_centered_bitmap(ALLEGRO_BITMAP *bitmap, float cx, float cy, float dx, float dy, float angle, int flags);

int string_al_get_text_width(const ALLEGRO_FONT *f, std::string str);
void string_al_draw_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, int flags, std::string text);

void string_al_draw_multiline_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, float max_width, float line_height, int flags, std::string text);

/// Mark Oates' do_multiline_text functions
bool multiline_text_draw_callback(int line_num, const char* line, int size, void* user_data);
int count_num_lines_will_render(ALLEGRO_FONT* font, float max_width, std::string text);

/*
int s_al_show_native_message_box(ALLEGRO_DISPLAY *display,
                                 std::string title, std::string heading, std::string text,
                                 char const *buttons, int flags);
*/

#endif // ALLEGROCUSTOM_H_INCLUDED
