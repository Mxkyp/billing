#include "../shop.h"
#include "../cleanup.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define NUM_PRODUCT_PARAMS 3
#define TEMP_SIZE 30
#define NAME 0
#define LONG_CODE 1
#define PRICE 2
void set_products_from_data(Shop *shop){
  shop->products = malloc(shop->scanned_items * sizeof(Product));
  assert(shop->products);
  char temp_name[TEMP_SIZE];
  char temp_long_code[TEMP_SIZE];
  char temp_price[TEMP_SIZE];

  for(int i = 0; i < shop->scanned_items; i++){
       char *received = strtok(shop->data[i],":");
       while(received){
         printf("%s ", received);
         received = strtok(NULL,":");
       }
       printf("\n");
      }
      //memccpy(cur_setting, received,'\0', TEMP_SIZE);
      /*
      if(param == NAME){
        memccpy(shop->products[i].name, cur_setting,'\0', TEMP_SIZE);
      }
      else if(param == LONG_CODE){
        shop->products[i]
      }
      else if(param == PRICE){
        cur_setting = temp_price;
      }
      */
  free(shop->products);
}


void set_shop_data(Shop* shop, const char* data_file_addr){
  const unsigned int buff_size = ELEM_SIZE;

  FILE *file = fopen(data_file_addr, "r");
  assert(file);

  shop->data = create_array_of_strings(MAX_ELEM_NUMBER, buff_size);
  assert(shop->data);

  shop->scanned_items = scan_file_for_data(shop->data, buff_size, file);

  free_unused_cells(shop->data, shop->scanned_items, MAX_ELEM_NUMBER);
  fclose(file);
}

char** create_array_of_strings(const int number_of_strings, const int max_string_length){
  char **array_of_strings = malloc(number_of_strings * sizeof(char *));
  if(array_of_strings == NULL){ return NULL; }

  for(int i = 0; i < number_of_strings; i++){
    array_of_strings[i] = malloc(max_string_length * sizeof(char));
    if(array_of_strings[i] == NULL){ return NULL; }
  }

  return array_of_strings;
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
