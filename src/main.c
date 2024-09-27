#include "../interface.h"
#include "../cleanup.h"
#include "../shop.h"
#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#define EXPECTED_ARGC 2
#define FILE_LOC 1
#define ESC 27
#define ENTER 10
#define SHOP '0'
#define CHECKOUT '1'
#define EXIT '2'

void restructure_shop_data(Shop *shop);
void set_up_shop(Shop *shop);
int main_menu_driver(Win* main, Shop* shop);
void do_shopping(Shop *shop);


int main(void){
  initalize_curses_options();
  atexit(clean);

  Win main = init_main_win();
  set_main_content(&main);

  Shop shop;
  set_up_shop(&shop);

  main_menu_driver(&main, &shop);

  free(shop.products);
  free_shop_data(shop.data, shop.scanned_items);
  return 0;
}


int main_menu_driver(Win* main, Shop* shop){
  int ch;

  while((ch = wgetch(main->ptr)) != EXIT){
    clear();
    refresh();

    switch(ch){
      case SHOP: do_shopping(shop);
        break;
      case CHECKOUT:
        break;
    };

    clear();
    paint_window(main, set_main_content);
    refresh();
  }
  return 0;
}

void set_up_shop(Shop *shop){
  set_shop_data(shop, "./src/shop_data.txt");
  set_products_from_data(shop);
  restructure_shop_data(shop);
}

void restructure_shop_data(Shop *shop){
  for(int i = 0; i < shop->scanned_items; i++){
    snprintf(shop->data[i], ELEM_SIZE, "%-40s %-.2f", shop->products[i].name, shop->products[i].price);
  }
}

void do_shopping(Shop *shop){
   ITEM **my_items;
   MENU *my_menu;

	my_items = (ITEM **)calloc(shop->scanned_items + 1, sizeof(ITEM *));

	for(int i = 0; i < shop->scanned_items; i++){
	        my_items[i] = new_item(shop->data[i],NULL);
          set_item_userptr(my_items[i], &shop->products[i]);
  }
	my_items[shop->scanned_items] = (ITEM *)NULL;

	my_menu = new_menu((ITEM **)my_items);
	post_menu(my_menu);
	refresh();

  int c;
	while((c = wgetch(stdscr)) != ESC){
    switch(c)
	    {	case KEY_DOWN:
		        menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
      case KEY_BACKSPACE:
        menu_driver(my_menu, REQ_BACK_PATTERN);
        break;
      case KEY_END:
        menu_driver(my_menu, REQ_CLEAR_PATTERN);
        break;
      case ENTER:
        /*add adding to shop */
        break;
      default:
        menu_driver(my_menu, c);
        break;
		};
	}

  refresh();
	unpost_menu(my_menu);
	free_menu(my_menu);
  for(int i =0; i < shop->scanned_items; i ++){
    free_item(my_items[i]);
  }
  free(my_items);
}
