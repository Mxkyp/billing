#include "../interface.h"
#include <curses.h>
#include <stdlib.h>
#define INTERFACE_HEIGHT 10
#define INTERFACE_WIDTH  20

//-fsanitize=address -fsanitize=undefined

Interface* create_interface(){
  Interface* new = malloc(sizeof(*new));

  new->attr.upper_left_corner = find_window_start_point();
  new->input_line_start = find_input_start();
  new->main = create_main_window(new->attr.upper_left_corner);

  return new;
}

Point find_window_start_point(){
  Point window_start = {.x = (COLS - INTERFACE_WIDTH)/2,
                        .y = (LINES - INTERFACE_HEIGHT)/2};
  return window_start;
}

Point find_input_start(){
  Point screen_lower_left_corner = {.x = 1,
                                    .y = LINES-1};
  return screen_lower_left_corner;
}

WINDOW* create_main_window(Point win_start){
  WINDOW *new_win = newwin(INTERFACE_HEIGHT, INTERFACE_WIDTH,
                           win_start.y, win_start.x);
  box(new_win, 0, 0);
  wrefresh(new_win);

  return new_win;
}
