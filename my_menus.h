#ifndef MY_MENUS_H_
#define MY_MENUS_H_
#include "interface.h"
#include "customer.h"
#include "menu.h"
#include <curses.h>
#include <menu.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

Menu *create_main_menu(Win main); // check for null

void set_items(ITEM *items[], const char *choices[], const int num_choices);

void set_menu_windows(MENU *menu, WINDOW* main, WINDOW* sub);
void free_Menu_obj(Menu *menu);
#endif // MY_MENUS_H_

