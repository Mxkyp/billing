#include "../interface.h"
#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//-fsanitize=address -fsanitize=undefined
void initalize_curses_options(){
  initscr();
  echo();
  keypad(stdscr, true);
  curs_set(2);

  refresh();
}

Interface* create_interface(void){
  Interface* new = malloc(sizeof(*new));

  set_main_win(new);
  set_dialog_win(new);
  set_content(new);
  set_input_start(new);

  refresh();
  return new;
}

void set_main_win(Interface *new){
  new->main.upper_left_corner = give_window_start_point(MAIN_Y, MAIN_X);
  new->main.dimensions = give_dimensions(INTERFACE_HEIGHT, INTERFACE_WIDTH);
  new->main.ptr = create_window(new->main.upper_left_corner, new->main.dimensions);

  set_input_options(&new->dialog, true, true, true, true);
  set_input_options(&new->main, false, true,false,false);
}

void set_dialog_win(Interface *new){
  new->dialog.upper_left_corner = give_window_start_point(DIALOG_Y, DIALOG_X);
  new->dialog.dimensions = give_dimensions(DIALOG_HEIGHT, DIALOG_WIDTH);
  new->dialog.ptr = create_window(new->dialog.upper_left_corner, new->dialog.dimensions);
}

void set_content(Interface *new){
  start_color();
  init_pair(TITLE_COLOR, COLOR_GREEN, COLOR_BLACK);
  print_in_middle(new->main.ptr, 1,
                  0, new->main.dimensions.width,
                  "Shop", COLOR_PAIR(TITLE_COLOR));
  wrefresh(new->main.ptr);

}

void set_input_start(Interface *interface){
  interface->user_input_start.y = INPUT_Y;
  interface->user_input_start.x = INPUT_X;
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
