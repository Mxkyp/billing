#include "../customer.h"
#include <stdlib.h>
#include <assert.h>
#include "../cleanup.h"
#define BASE_SIZE 10

Customer init_customer(void){
  Customer customer = {.cart.total_price = 0,
                       .cart.product = NULL};
  return customer;
}

void add_product(ShoppingCart *cart){
  Product *last = NULL, *new = cart->product;

  while(new != NULL){
    last = new;
    new = new->next;
  }

  new = malloc(sizeof(Product));

  assert(new);
  new->before = last;
  new->next = NULL;

  atexit_add(new);
}
