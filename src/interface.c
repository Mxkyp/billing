#include "../interface.h"
#include "../cleanup.h"
#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

//-fsanitize=address -fsanitize=undefined
void initalize_curses_options(){
  initscr();
  echo();
  keypad(stdscr, true);
  curs_set(2);

  refresh();
}

Win* create_main_win(void){
  Win *main = malloc(sizeof(*main));
  assert(main);

  main->upper_left_corner = give_window_start_point(MAIN_Y, MAIN_X);
  main->dimensions = give_dimensions(INTERFACE_HEIGHT, INTERFACE_WIDTH);
  main->ptr = create_window(main->upper_left_corner, main->dimensions);

  set_input_options(main, false, true,false,false);

  atexit_add(main);
  return main;
}

Win *create_input_win(void){
  Win *input = malloc(sizeof(*input));
  assert(input);

  input->upper_left_corner = give_window_start_point(INPUT_Y, INPUT_X);
  input->dimensions = give_dimensions(INPUT_HEIGHT, INPUT_WIDTH);
  input->ptr = create_window(input->upper_left_corner, input->dimensions);

  set_input_options(input, true, true, true, true);

  atexit_add(input);
  return input;
}

void set_main_content(Win* main){
  start_color();
  init_pair(TITLE_COLOR, COLOR_GREEN, COLOR_BLACK);
  print_in_middle(main->ptr, 1,
                  0,main->dimensions.width,
                  "Shop", COLOR_PAIR(TITLE_COLOR));
  wrefresh(main->ptr);
}

void set_input_start(InputField* in_field){
  in_field->user_input_start.y = INPUT_START_Y;
  in_field->user_input_start.x = INPUT_START_X;
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

void set_input_options(Win *new, bool want_echo, bool want_keypad, bool want_line_buffering, bool want_cursor){
  noecho();
  cbreak();
  curs_set(0);

  if(want_echo){
   new->opt.echo = true;
   echo();
  }
  if(want_keypad){
    new->opt.keypad = true;
    keypad(new->ptr, TRUE);
  }
  if(want_line_buffering){
    new->opt.line_buffering = true;
   nocbreak();
  }
  if(want_cursor){
    new->opt.cursor = true;
    curs_set(1);
  }
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color){
  int length, x, y;
  float temp;

  getyx(win, y, x);
  if(startx != 0)
    x = startx;
  if(starty != 0)
    y = starty;
  if(width == 0)
    width = 80;

  length = strlen(string);
  temp = (width - length)/ 2;
  x = startx + (int)temp;
  wattron(win, color);
  mvwprintw(win, y, x, "%s", string);
  wattroff(win, color);
  refresh();
}


void switch_input_options(Win win){
  if(win.opt.echo){
   echo();
  }
  else if(win.opt.echo == false){
    noecho();
  }

  if(win.opt.keypad){
    keypad(win.ptr, TRUE);
  }
  else if(win.opt.keypad == false){
    keypad(win.ptr, FALSE);
  }

  if(win.opt.line_buffering){
   cbreak();
  }
  else if(win.opt.line_buffering == false){
   cbreak();
  }

  if(win.opt.cursor){
    curs_set(1);
  }
  else if(win.opt.cursor == false){
    curs_set(0);
  }
}
