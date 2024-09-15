#include "../my_menus.h"
#include "../interface.h"
#include <menu.h>
#include <unistd.h>

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

MENU *create_main_menu(Win main){ // check for null
  const int num_choices = 4;
  const char *choices[] = { "Shop", "Check Cart", "Checkout", "Exit" };
  ITEM *items[num_choices + 1];


  items[num_choices] = (ITEM *)NULL;

  MENU* my_menu = new_menu(items);
  set_menu_win(my_menu, main.ptr);
  set_menu_sub(my_menu,derwin(main.ptr, main.dimensions.height-5, 12,
                            4, 7));
  set_menu_mark(my_menu,"+");

  post_menu(my_menu);
  wrefresh(main.ptr);

  return my_menu;
}

void set_menu_items(ITEM *items[], const char *choices[], const int num_choices){
  for(int i = 0; i < num_choices; i++){
    items[i] = new_item(choices[i],NULL);
    set_item_userptr(items[i], menu_function[i]);
  }

}
