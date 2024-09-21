#include "../my_menus.h"
#include "../interface.h"
#include "../customer.h"
#include "../cleanup.h"
#include <menu.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>

Menu *create_menu(const char *choices[], const int num_choices){
 Menu *menu = malloc(sizeof(*menu));
 menu->items = malloc(sizeof(ITEM*) * (num_choices+1));

 if(menu == NULL){
   return NULL;
 }

  set_items(menu->items, choices, num_choices);

  MENU* menu_ptr = new_menu(menu->items);
  menu->ptr = menu_ptr;
  menu->num_choices = num_choices;

  atexit_add(menu);
  return menu;
}

Menu *create_main_menu(Win *main){ // check for null
  const char *choices[] = { "Shop", "Check Cart", "Checkout", "Exit" };
  const int num_choices = ARRAY_SIZE(choices);
  WINDOW *subwindow = derwin(main->ptr, main->dimensions.height-5, 12, 4, 7);

  Menu *menu = create_menu(choices, num_choices);

  set_menu_windows(menu->ptr, main->ptr, subwindow);
  set_menu_mark(menu->ptr,"+");

  post_menu(menu->ptr);
  wrefresh(main->ptr);

  return menu;
}


void shop(ShoppingCart *cart){
  clear();
  mvprintw(LINES/2, COLS/2, "SHOP");
  refresh();
  sleep(5);
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


void set_items(ITEM **items, const char *choices[], const int num_choices){
  for(int i = 0; i < num_choices; i++){
    items[i] = new_item(choices[i],NULL);
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
