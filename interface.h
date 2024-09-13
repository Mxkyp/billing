#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <curses.h>

#define INTERFACE_HEIGHT 24
#define INTERFACE_WIDTH  26

#define MAIN_Y (LINES - INTERFACE_HEIGHT)/2
#define MAIN_X (COLS - INTERFACE_WIDTH)/2

#define INPUT_X 1
#define INPUT_Y LINES - 1
#define DIALOG_Y LINES - 2
#define DIALOG_X 0
#define DIALOG_HEIGHT 3
#define DIALOG_WIDTH COLS

typedef struct{
  int x,y;
}Point;

typedef struct{
  int height, width;
}Dimensions;

typedef struct{
  Point upper_left_corner;
  Dimensions dimensions;
  WINDOW *ptr;
}Win;

typedef struct{
  Win main;
  Win dialog;
  Point user_input_start;
  char  token;
}Interface;

void set_curses_options();
Interface* create_interface();

void set_main_win(Interface *new);
void set_dialog_win(Interface *new);
void set_input_start(Interface *interface);

Point give_window_start_point(int y_wanted, int x_wanted);
Dimensions give_dimensions(int h, int w);
Point give_input_start();
WINDOW* create_window(Point win_start, Dimensions dim);
void seperate_input_line(Point input_line_start);

#endif // MAIN_H_
