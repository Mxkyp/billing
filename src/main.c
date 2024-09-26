#include "../interface.h"
#include "../cleanup.h"
#include "../shop.h"
#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#define EXPECTED_ARGC 2
#define FILE_LOC 1

void paint_window(Win *win, void(*paint_details)(Win *win)){
  if(paint_details != NULL){
    paint_details(win);
  }
  box(win->ptr, 0, 0);
}

int main(void){
  initalize_curses_options();
  atexit(clean);

  Win main = init_main_win();
  set_main_content(&main);

  wrefresh(main.ptr);
  int ch;
  while((ch = wgetch(main.ptr)) != 'o'){
    switch(ch){
      case 'c':
              clear();
              refresh();
              break;
      case 'p':
              paint_window(&main, set_main_content);
              break;
    };
  }


  return 0;
}



