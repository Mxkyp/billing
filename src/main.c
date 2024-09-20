#include "../main.h"
#include "../interface.h"
#include "../my_menus.h"
#include <curses.h>
#include <menu.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
  initalize_curses_options();
  Interface* interface = create_interface();
  interface->main.menu = create_main_menu(interface->main);
  input(interface);

  free_Menu_obj(interface->main.menu);
  free(interface);
  endwin();
}

void input(Interface *interface){
  while((interface->input = wgetch(interface->main.ptr)) != KEY_F(2)){
    switch(interface->input)
	    {	case KEY_DOWN:
		        menu_driver(interface->main.menu->ptr, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(interface->main.menu->ptr, REQ_UP_ITEM);
				break;
      case ENTER:
        ITEM *cur;
				void (*p)(ShoppingCart *);

				cur = current_item(interface->main.menu->ptr);
				p = item_userptr(cur);
				p(NULL);
				pos_menu_cursor(interface->main.menu->ptr);
				break;
		};
	}
}
