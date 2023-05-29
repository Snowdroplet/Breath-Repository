#ifndef ALLEGROCUSTOM_H_INCLUDED
#define ALLEGROCUSTOM_H_INCLUDED

#include <string>

//#include <allegro5/allegro.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_native_dialog.h>

extern ALLEGRO_COLOR COL_WHITE;
extern ALLEGRO_COLOR COL_DARK_WHITE;
extern ALLEGRO_COLOR COL_GRAY;
extern ALLEGRO_COLOR COL_DARK_GRAY;
extern ALLEGRO_COLOR COL_BLACK;

extern ALLEGRO_COLOR COL_RED;

extern ALLEGRO_COLOR COL_ORANGE;

extern ALLEGRO_COLOR COL_YELLOW;
extern ALLEGRO_COLOR COL_LIGHT_YELLOW;
extern ALLEGRO_COLOR COL_DARK_YELLOW;

extern ALLEGRO_COLOR COL_GREEN;
extern ALLEGRO_COLOR COL_LIGHT_GREEN;

extern ALLEGRO_COLOR COL_BLUE;

extern ALLEGRO_COLOR COL_INDIGO;
extern ALLEGRO_COLOR COL_VIOLET;

extern ALLEGRO_COLOR COL_BROWN;
extern ALLEGRO_COLOR COL_DARK_BROWN;

extern ALLEGRO_COLOR COL_PEN_INK;

extern ALLEGRO_COLOR currentClearColor;

void AllegroCustomColours();

//void c_al_draw_centered_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags);
//void c_al_draw_rotated_centered_bitmap(ALLEGRO_BITMAP *bitmap, float cx, float cy, float dx, float dy, float angle, int flags);

int string_al_get_text_width(const ALLEGRO_FONT *f, std::string str);
void string_al_draw_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, int flags, std::string text);

void string_al_draw_multiline_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, float max_width, float line_height, int flags, std::string text);

/*
int s_al_show_native_message_box(ALLEGRO_DISPLAY *display,
                                 std::string title, std::string heading, std::string text,
                                 char const *buttons, int flags);
*/

#endif // ALLEGROCUSTOM_H_INCLUDED
