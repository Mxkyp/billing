#include "../main.h"
#include "../interface.h"
#include "../my_menus.h"
#include "../cleanup.h"
#include "../customer.h"
#include "../shop.h"
#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main(void){
  initalize_curses_options();
  atexit(clean);

  Win main = init_main_win();
  set_main_win(&main);

  Customer customer = init_customer();

  handle_win_menu(&main, &customer);

  unpost_menu(main.menu->ptr);
  free_menu(main.menu->ptr);
  return 0;
}


void set_main_win(Win *main){
  set_main_content(main);
  main->menu = create_main_menu(main);
}

void handle_win_menu(Win *win, Customer *customer){
  int ch;
  while((ch = wgetch(win->ptr)) != KEY_F(2)){
    switch(ch)
      { case KEY_DOWN:
		        menu_driver(win->menu->ptr, REQ_DOWN_ITEM);
      break;
			case KEY_UP:
				menu_driver(win->menu->ptr, REQ_UP_ITEM);
				break;
      case ENTER:
        ITEM *cur;
				void (*p)(ShoppingCart *);

				cur = current_item(win->menu->ptr);
				p = item_userptr(cur);
				p(&customer->cart);
				pos_menu_cursor(win->menu->ptr);
				break;
		};
	}
}
