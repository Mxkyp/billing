#include "../interface.h"
#include "../cleanup.h"
#include "../shop.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#define EXPECTED_ARGC 2
#define FILE_LOC 1
#define SHOP '0'
#define CHECKOUT '1'
#define EXIT '2'
int main_menu_driver(Win* main);

int main(void){
  initalize_curses_options();
  atexit(clean);

  Win main = init_main_win();
  set_main_content(&main);

  main_menu_driver(&main);

  return 0;
}


int main_menu_driver(Win* main){
  int ch;
  while((ch = wgetch(main->ptr)) != EXIT){
    switch(ch){
      case SHOP:
              clear();
              refresh();
              paint_window(main, set_main_content);
        break;
      case CHECKOUT:
              clear();
              refresh();
              paint_window(main, set_main_content);
        break;
    }
  }
  return 0;
}
