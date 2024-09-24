#include "../shop.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define ELEM_SIZE 64
#define MAX_ELEM_NUMBER 100

// work on this
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

char **scan_file(char *filename, int *scanned_elements){
  const unsigned int buff_size = ELEM_SIZE;

  FILE *f = fopen(filename, "r");
  assert(f);

  char **data = malloc(MAX_ELEM_NUMBER * sizeof(*data));
  assert(data);

  for(int i = 0; i < MAX_ELEM_NUMBER; i++){
    data[i] = malloc(buff_size * sizeof(*data[i]));
    assert(data[i]);
  }

  int data_counter;
  for(data_counter = 0; data_counter < MAX_ELEM_NUMBER; data_counter++){
    if(my_getline(buff_size, data[data_counter], f)){
      printf("%s\n",data[data_counter]);
    }
    else{
      break;
    }
  }
  *scanned_elements = data_counter + 1;

  free_unused_cells(data, *scanned_elements, MAX_ELEM_NUMBER);
  fclose(f);
  return data;
}

void free_unused_cells(char** data, int scanned_elements, const int max_data_elements){
  if(scanned_elements == max_data_elements){
    return;
  }

  for(int i = scanned_elements; i < max_data_elements; i++){
    free(data[i]);
  }
}


void free_data(char** data, const int elem_number){
  for(int i = 0; i < elem_number; i++){
    free(data[i]);
  }
  free(data);
}
