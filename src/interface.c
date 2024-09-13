#include "../interface.h"
#include <curses.h>
#include <stdlib.h>
#define INTERFACE_HEIGHT 24
#define INTERFACE_WIDTH  26

//-fsanitize=address -fsanitize=undefined
void set_curses_options(){
  initscr();
  echo();
  keypad(stdscr, true);
  curs_set(2);

  refresh();
}

Interface* create_interface(){
  Interface* new = malloc(sizeof(*new));

  new->attr.upper_left_corner = find_window_start_point();
  new->main = create_main_window(new->attr.upper_left_corner);
  new->input_line_start = find_input_start();
  seperate_input_line(new->input_line_start);

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

void seperate_input_line(Point input_line_start){
  move(input_line_start.y-1, input_line_start.x);

  attron(A_DIM);
  hline(ACS_HLINE, COLS+2000);
  attroff(A_DIM);

  move(input_line_start.y, input_line_start.x);
  refresh();
}
