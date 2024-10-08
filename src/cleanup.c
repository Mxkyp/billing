#include "../cleanup.h"
#include <curses.h>
#include <stdlib.h>
#include <menu.h>

void **vclean;
size_t nclean;

void atexit_add(void *data){
    vclean = realloc(vclean, sizeof(void *) * (nclean + 1));
    if(vclean == NULL){
      exit(EXIT_FAILURE);
    }
    vclean[nclean++] = data;
}

void clean(void){
    size_t i;

    for (i = 0; i < nclean; i++) {
        free(vclean[i]);
    }

    free(vclean);
    endwin();
}
