#include "../main.h"
#include "../interface.h"
#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
  initscr();
  refresh();
  Interface* menu = create_interface();


  sleep(5);
  free(menu);
  endwin();
}
