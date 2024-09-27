#ifndef SHOP_H_
#define SHOP_H_
#include <stdio.h>
#define ELEM_SIZE 64
#define MAX_ELEM_NUMBER 100
#define MAX_NAME 128

typedef struct product Product;
struct product{
  char name[MAX_NAME];
  long int code;
  double price;
};

typedef struct shop Shop;
struct shop{
  char *data_file_loc;
  char **data;
  int scanned_items;
  Product *products;
};

/*
  allocates memory for MAX_ELEMENTS_NUMBER strings to be saved in shop.data
  reads the strings from the file with address == data_file_addr
  saves them onto the shop.data array of pointers
  saves the number of strings into shop.scanned_items;
  then frees the unused space
 */
void set_shop_data(Shop* shop, const char* data_file_addr);
void set_products_from_data(Shop *shop);

int scan_file_for_data(char **data, const unsigned int buff_size, FILE *f);

/*
  Reads at most max_size_with_null - 1 chars into an array, and terminates with a '\0'
  returns the amount of characters read;
 */
unsigned int my_getline(const unsigned int max_size_with_null, char arr[max_size_with_null], FILE* file_ptr);

/*
 * returns NULL on failure;
*/
char** create_array_of_strings(const int number_of_strings, const int max_string_length);

/*
  frees unused elements
  i.e if 50 elements were scanned, 100 were max,
  then frees all the elements with indexes <50, 99>
 */
void free_unused_cells(char** data, int scanned_elements, const int max_data_elements);

void free_shop_data(char** data, const int elem_number);


#endif // SHOP_H_
