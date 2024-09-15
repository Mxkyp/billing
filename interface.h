#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <curses.h>
#include <menu.h>

#define INTERFACE_HEIGHT 12
#define INTERFACE_WIDTH  26

#define MAIN_Y (LINES - INTERFACE_HEIGHT)/2
#define MAIN_X (COLS - INTERFACE_WIDTH)/2

#define INPUT_X 1
#define INPUT_Y LINES - 1
#define DIALOG_Y LINES - 2
#define DIALOG_X 0
#define DIALOG_HEIGHT 3
#define DIALOG_WIDTH COLS

#define TITLE_COLOR 1

typedef struct{
  int x,y;
}Point;

typedef struct{
  int height, width;
}Dimensions;

typedef struct{
  bool echo, keypad, line_buffering, cursor;
}InputOptions;

typedef struct{
  Point upper_left_corner;
  Dimensions dimensions;
  WINDOW *ptr;
  InputOptions opt;
  MENU *menu;
}Win;

typedef struct{
  Win main;
  Win dialog;
  Point user_input_start;
  char  input;
}Interface;

void initalize_curses_options();
Interface* create_interface();
MENU *create_menu(Win main); // check for null

void set_main_win(Interface *new);
void set_dialog_win(Interface *new);
void set_input_start(Interface *new);
void set_content(Interface *new);

void set_input_options(Win *new, bool want_echo, bool want_keypad, bool want_line_buffering, bool want_cursor);
void switch_input_options(Win win);
Point give_window_start_point(int y_wanted, int x_wanted);
Dimensions give_dimensions(int h, int w);
Point give_input_start();
WINDOW* create_window(Point win_start, Dimensions dim);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);



#endif // MAIN_H_
