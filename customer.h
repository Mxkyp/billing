#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include "shop.h"


typedef struct productBought ProductBought;
struct productBought{
  Product type;
  unsigned int amount_of;
  ProductBought *next;
  ProductBought *before;
};

typedef struct shoppingCart ShoppingCart;
struct shoppingCart{
  unsigned int total_price;
  ProductBought *product;
};

typedef struct customer Customer;
struct customer{
  ShoppingCart cart;
};

Customer init_customer(void);
void add_product(ShoppingCart *cart);

#endif // CUSTOMER_H_
