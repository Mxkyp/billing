#include "../interface.h"
#include <curses.h>
#include <stdlib.h>

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

  set_main_win(new);
  set_dialog_win(new);
  set_input_start(new);

  refresh();
  return new;
}

void set_main_win(Interface *new){
  new->main.upper_left_corner = give_window_start_point(MAIN_Y, MAIN_X);
  new->main.dimensions = give_dimensions(INTERFACE_HEIGHT, INTERFACE_WIDTH);
  new->main.ptr = create_window(new->main.upper_left_corner, new->main.dimensions);
}
void set_dialog_win(Interface *new){
  new->dialog.upper_left_corner = give_window_start_point(DIALOG_Y, DIALOG_X);
  new->dialog.dimensions = give_dimensions(DIALOG_HEIGHT, DIALOG_WIDTH);
  new->dialog.ptr = create_window(new->dialog.upper_left_corner, new->dialog.dimensions);
}

void set_input_start(Interface *interface){
  interface->user_input_start.y = INPUT_Y;
  interface->user_input_start.x = INPUT_X;

  move(interface->user_input_start.y, interface->user_input_start.x);
}

Point give_window_start_point(int y_wanted, int x_wanted){
  Point window_start = {.y = y_wanted,
                        .x = x_wanted};
  return window_start;
}

Dimensions give_dimensions(int h, int w){
  Dimensions d = { .height = h, .width = w};
  return d;
}

WINDOW* create_window(Point win_start, Dimensions dim){
  WINDOW *new_win = newwin(dim.height, dim.width,
                           win_start.y, win_start.x);
  box(new_win, 0, 0);
  wrefresh(new_win);

  return new_win;
}

