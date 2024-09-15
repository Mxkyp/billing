#include "../main.h"
#include "../interface.h"
#include <curses.h>
#include <menu.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
  initalize_curses_options();
  Interface* interface = create_interface();
  int c;

keypad(interface->main.ptr, TRUE);
while((c = wgetch(interface->main.ptr)) != KEY_F(1))
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(interface->main.menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(interface->main.menu, REQ_UP_ITEM);
				break;
		};
	}

  free(interface);
  endwin();
}

