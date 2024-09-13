#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <curses.h>
typedef struct{
  int x,y;
}Point;

typedef struct{
  Point upper_left_corner;
}MainWin;

typedef struct{
  WINDOW *main;
  MainWin attr;
  Point input_line_start;
  char  input;
}Interface;

Interface* create_interface();

Point find_window_start_point();
Point find_input_start();
WINDOW* create_main_window(Point win_start);

#endif // MAIN_H_
