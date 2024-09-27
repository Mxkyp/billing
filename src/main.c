#include "../interface.h"
#include "../cleanup.h"
#include "../shop.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#define EXPECTED_ARGC 2
#define FILE_LOC 1
#define SHOP '0'
#define CHECKOUT '1'
#define EXIT '2'
int main_menu_driver(Win* main);

void restructure_shop_data(Shop *shop){
  char *comma;

  for(int i = 0; i < shop->scanned_items; i++){
    snprintf(shop->data[i], ELEM_SIZE, "%-40s %-.2f", shop->products[i].name, shop->products[i].price);
  }

}

void do_shopping(void){
  Shop shop;
  set_shop_data(&shop, "./src/shop_data.txt");
  set_products_from_data(&shop);

  restructure_shop_data(&shop);
  for(int i = 0; i < shop.scanned_items; i++){
    wprintw(stdscr, "%s\n", shop.data[i]);
  }
  refresh();
  sleep(5);

  free(shop.products);
  free_shop_data(shop.data, shop.scanned_items);

}


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
    clear();
    refresh();

    switch(ch){
      case SHOP: do_shopping();
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
