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
#define NOT_FOUND -1
#define FILE_LOC 1
#define ESC 27
#define ENTER 10
#define TIME 150000

#define SHOP '0'
#define CHECKOUT '1'
#define EXIT '2'

void restructure_shop_data(Shop *shop);
void set_up_shop(Shop *shop);
int main_menu_driver(Win* main, Shop* shop, Customer *customer);
void do_shopping(Shop *shop, Customer *customer);
void set_items_array( ITEM **items, Shop* shop);

/*
  checksout the customer, prints the shoping summary, and allows him to pay
 */
void checkout(Customer *customer);
/*
  prints all the items bought by the customer, and the total cost
 */
void print_summary(Customer *customer);

//checks if a product with a given code is already in cart, if yes, increase its quanity by one
//else add it, and increments the counter of unique products
void assign_item_to_customer(ITEM* picked, Customer *customer);
int search_for_code(long int searched_code, int n, Product bought[n]);


int main(void){
  initalize_curses_options();
  atexit(clean);

  Win main = init_main_win();
  set_main_content(&main);

  Shop shop;
  set_up_shop(&shop);

  Customer customer = {.product_quanity = {0}, .distinct_product_counter = 0};

  main_menu_driver(&main, &shop, &customer);

  free(shop.products);
  free_shop_data(shop.data, shop.scanned_items);
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

int main_menu_driver(Win* main, Shop* shop, Customer *customer){
  int ch;

  while((ch = wgetch(main->ptr)) != EXIT){
    clear();
    refresh();

    switch(ch){
      case SHOP: do_shopping(shop, customer);
        break;
      case CHECKOUT: checkout(customer);
        break;
    };

    clear();
    paint_window(main, set_main_content);
    refresh();
  }
  return 0;
}

void do_shopping(Shop *shop, Customer *customer){
   ITEM **my_items;
   MENU *my_menu;

	my_items = (ITEM **)calloc(shop->scanned_items + 1, sizeof(ITEM *));

  set_items_array(my_items, shop);

	my_menu = new_menu((ITEM **)my_items);
	post_menu(my_menu);
	refresh();

  int c;
	while((c = wgetch(stdscr)) != ESC){
    usleep(TIME);
    switch(c){
      case KEY_DOWN:
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
         ITEM *cur;
         cur = current_item(my_menu);
         assign_item_to_customer(cur, customer);
         pos_menu_cursor(my_menu);
        break;
      default:
        menu_driver(my_menu, c);
        break;
		};
    flushinp();
	}

  refresh();
	unpost_menu(my_menu);
	free_menu(my_menu);
  for(int i =0; i < shop->scanned_items; i ++){
    free_item(my_items[i]);
  }
  free(my_items);
}

void set_items_array(ITEM **items, Shop* shop){
	for(int i = 0; i < shop->scanned_items; i++){
	        items[i] = new_item(shop->data[i], NULL);
          set_item_userptr(items[i], &shop->products[i]);
  }
	items[shop->scanned_items] = (ITEM *)NULL;
}

void checkout(Customer *customer){
  clear();
  refresh();
  print_summary(customer);
  refresh();
  sleep(5);
}


void assign_item_to_customer(ITEM* picked, Customer *customer){
  Product *picked_product = (Product*)item_userptr(picked);
  int index = search_for_code(picked_product->code, customer->distinct_product_counter, customer->products);

  if(index == NOT_FOUND){
    customer->product_quanity[customer->distinct_product_counter]++;
    customer->products[customer->distinct_product_counter++] = *(Product*)item_userptr(picked);

  }
  else{
    customer->product_quanity[index]++;
  }
}

int search_for_code(long int searched_code, int n, Product bought[n]){
  for(int i = 0; i < n; i++){
    if(bought[i].code == searched_code){
      return i;
    }
  }
  return NOT_FOUND;
}

void print_summary(Customer *customer){
  double total_cost = 0;
  wprintw(stdscr,"%-40s %-11s %-7s %-10s %-10s\n","PRODUCT NAME", "CODE","QUANITY", "UNIT PRICE", "TOTAL COST");

  for(unsigned int i = 0; i < customer->distinct_product_counter; i++){
    wprintw(stdscr,"%-40s %-11ld %-7u %-10.3lf %-10.3lf\n",customer->products[i].name, customer->products[i].code, customer->product_quanity[i],
                                                           customer->products[i].price, customer->products[i].price * customer->product_quanity[i]);
    total_cost += customer->products[i].price * customer->product_quanity[i];
  }

  wprintw(stdscr,"%-40s %-11s %-7s %-10s %-10.3lf","", "","","SUM: ", total_cost);

}
