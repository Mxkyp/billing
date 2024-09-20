#ifndef PRODUCT_H_
#define PRODUCT_H_

typedef struct product Product;
struct product{
  unsigned int price;
  unsigned int amount_of;
  long int code;
  char* name;
  Product *next;
  Product *before;
};

typedef struct{
  unsigned int total_price;
  Product *product;
}ShoppingCart;

#endif // PRODUCT_H_
