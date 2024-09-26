#include "../my_menus.h"
#include "../interface.h"
#include "../customer.h"
#include "../cleanup.h"
#include <menu.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>

Menu *create_menu(void){
 Menu *menu = malloc(sizeof(*menu));

 if(menu == NULL){
   return NULL;
 }

  atexit_add(menu);
  return menu;
}

void set_menu(Menu *menu, char* choices[], const int num_choices){
  menu->items = (ITEM **)calloc(num_choices+1, sizeof(ITEM*));

  set_items(menu->items, choices, num_choices);

  MENU* menu_ptr = new_menu(menu->items);
  menu->ptr = menu_ptr;
  menu->num_choices = num_choices;
}

void set_main_menu(Menu *menu, char* choices[], const int num_choices){
  menu->items = (ITEM **)calloc(num_choices+1, sizeof(ITEM*));

  set_main_menu_items(menu->items, choices, num_choices);

  MENU* menu_ptr = new_menu(menu->items);
  menu->ptr = menu_ptr;
  menu->num_choices = num_choices;
}

Menu *create_main_menu(Win *main){ // check for null
  char *choices[] = { "Shop", "Check Cart", "Checkout", "Exit" };
  const int num_choices = ARRAY_SIZE(choices);
  WINDOW *subwindow = derwin(main->ptr, main->dimensions.height-5, 12, 4, 7);

  Menu *menu = create_menu();

  set_main_menu(menu, choices, num_choices);
  set_menu_windows(menu->ptr, main->ptr, subwindow);
  set_menu_mark(menu->ptr,"+");

  post_menu(menu->ptr);
  wrefresh(main->ptr);

  return menu;
}

/* testing  */
void shop(ShoppingCart *cart){
  clear();
  refresh();

  Shop shop;
  shop.data_file_loc = "./src/shop_data.txt";
  set_shop_data(&shop);

  WINDOW *shop_win = newwin(LINES-4,COLS,0,0);
  keypad(shop_win,TRUE);
  cbreak();
  noecho();

  Menu *menu = create_menu();
  set_menu(menu, shop.data, shop.scanned_items);
  set_menu_windows(menu->ptr, shop_win, derwin(shop_win, 0, 0, 1, 1));
  post_menu(menu->ptr);

  wrefresh(shop_win);
  refresh();

  int ch;
  while((ch = wgetch(shop_win)) != KEY_F(2)){
    switch(ch)
      { case KEY_DOWN:
		        menu_driver(menu->ptr, REQ_DOWN_ITEM);
      break;
			case KEY_UP:
				menu_driver(menu->ptr, REQ_UP_ITEM);
				break;
		};
	}
  sleep(5);

  unpost_menu(menu->ptr);
  free_menu(menu->ptr);
  free(menu);
  free_shop_data(shop.data, shop.scanned_items);
}

void check_cart(ShoppingCart *cart){
  clear();
  mvprintw(LINES/2, COLS/2, "CART");
  refresh();
  sleep(5);
}

void checkout(ShoppingCart *cart){
  clear();
  mvprintw(LINES/2, COLS/2, "CHECKOUT");
  refresh();
  sleep(5);
}

void exitt(ShoppingCart *cart){
  clear();
  mvprintw(LINES/2, COLS/2, "EXIT");
  refresh();
  sleep(5);
}

void (*menu_function[4])(ShoppingCart *) = {shop, check_cart, checkout, exitt};


void set_main_menu_items(ITEM **items, char *choices[], const int num_choices){
  for(int i = 0; i < num_choices; i++){
    items[i] = new_item(choices[i], choices[i]);
    set_item_userptr(items[i], menu_function[i]);
    atexit_add(items[i]);
  }

  items[num_choices] = (ITEM *)NULL;
  atexit_add(items[num_choices]);
  atexit_add(items);
}


void set_menu_windows(MENU *menu, WINDOW* main, WINDOW* sub){
  set_menu_win(menu, main);
  set_menu_sub(menu, sub);
}

void set_items(ITEM **items, char *choices[], const int num_choices){
  for(int i = 0; i < num_choices; i++){
    items[i] = new_item(choices[i], NULL);
    atexit_add(items[i]);
  }

  items[num_choices] = (ITEM *)NULL;
  atexit_add(items[num_choices]);
  atexit_add(items);
}
