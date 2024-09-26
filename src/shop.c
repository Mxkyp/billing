#include "../shop.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


void set_shop_data(Shop* shop){
  const unsigned int buff_size = ELEM_SIZE;

  FILE *file = fopen(shop->data_file_loc, "r");
  assert(file);

  shop->data = malloc(MAX_ELEM_NUMBER * sizeof(*(shop->data)));
  assert(shop->data);

  for(int i = 0; i < MAX_ELEM_NUMBER; i++){
    shop->data[i] = malloc(buff_size * sizeof(*(shop->data[i])));
    assert(shop->data[i]);
  }

  shop->scanned_items = scan_file_for_data(shop->data, buff_size, file);

  free_unused_cells(shop->data, shop->scanned_items, MAX_ELEM_NUMBER);
  fclose(file);
}

int scan_file_for_data(char **data, const unsigned int buff_size, FILE *f){
  int last_data_index;

  for(last_data_index = 0; last_data_index < MAX_ELEM_NUMBER; last_data_index++){
    if(my_getline(buff_size, data[last_data_index], f) == 0){
      break;
    }
  }

  int scanned_elements = last_data_index + 1;
  return scanned_elements;
}

unsigned int my_getline(const unsigned int max_size_with_null, char arr[max_size_with_null], FILE* file_ptr){
  int ch;
  unsigned int i;
  for(i = 0; i < max_size_with_null - 1; i++){
    if((ch = fgetc(file_ptr)) != '\n' && ch != EOF){
      arr[i] = ch;
    }
    else{
      break;
    }
  }

  arr[i] = '\0';
  return i;
}

void free_unused_cells(char** data, int scanned_elements, const int max_data_elements){
  if(scanned_elements == max_data_elements){
    return;
  }

  for(int i = scanned_elements; i < max_data_elements; i++){
    free(data[i]);
  }
}

void free_shop_data(char** data, const int elem_number){
  for(int i = 0; i < elem_number; i++){
    free(data[i]);
  }
  free(data);
}

/*
void set_products_from_data(Shop *shop){
  shop->products = malloc(sizeof(Product) * shop->scanned_items);
  assert(shop->products);


}
*/
