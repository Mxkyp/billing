#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include "product.h"

typedef struct customer{
  ShoppingCart cart;
}Customer;

Customer init_customer(void);
void add_product(ShoppingCart *cart);

#endif // CUSTOMER_H_
