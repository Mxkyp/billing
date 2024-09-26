#include "../interface.h"
#include "../cleanup.h"
#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define MENU_COLOR 9
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void initalize_curses_options(){
  initscr();
  echo();
  keypad(stdscr, true);
  curs_set(2);

  refresh();
}

Win init_main_win(void){
  Win main;

  main.upper_left_corner = give_window_start_point(MAIN_Y, MAIN_X);
  main.dimensions = give_dimensions(INTERFACE_HEIGHT, INTERFACE_WIDTH);
  main.ptr = create_window(main.upper_left_corner, main.dimensions);

  set_input_options(&main, false, true,false,false);

  return main;
}

void set_main_content(Win* main){
  start_color();

  paint_main_header(main);
  paint_main_menu(main);
  wrefresh(main->ptr);
}

void paint_main_header(Win* main){
  init_pair(TITLE_COLOR, COLOR_GREEN, COLOR_BLACK);
  print_in_middle(main->ptr, 1,
                  0,main->dimensions.width,
                  "Shop", COLOR_PAIR(TITLE_COLOR));
}

void paint_main_menu(Win *main){
  init_pair(MENU_COLOR, COLOR_WHITE, COLOR_BLACK);
  char *choices[] = {"[0] shop     ", "[1] check out", "[2] exit     "};

  for(size_t i = 0, y_line = 4; i < ARRAY_SIZE(choices); i++, y_line+=2){
  print_in_middle(main->ptr, y_line, 0, main->dimensions.width,
                  choices[i], COLOR_PAIR(MENU_COLOR));
  }
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

void paint_window(Win *win, void(*paint_details)(Win *win)){
  if(paint_details != NULL){
    paint_details(win);
  }
  box(win->ptr, 0, 0);
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
