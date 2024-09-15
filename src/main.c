#include "../main.h"
#include "../interface.h"
#include <curses.h>
#include <menu.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
  set_curses_options();
  Interface* interface = create_interface();

  char c;
  while((c =getchar()) != 'p'){
    addch(c);
    refresh();
  }
  free(interface);
  endwin();
}

