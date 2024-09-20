#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <curses.h>
#include <menu.h>

// window parameters
#define INTERFACE_HEIGHT 12
#define INTERFACE_WIDTH  26
#define MAIN_Y (LINES - INTERFACE_HEIGHT)/2
#define MAIN_X (COLS - INTERFACE_WIDTH)/2
#define INPUT_START_X 1
#define INPUT_START_Y LINES - 1
#define INPUT_Y LINES - 2
#define INPUT_X 0
#define INPUT_HEIGHT 3
#define INPUT_WIDTH COLS

//Specific numbers
#define TITLE_COLOR 1
#define ENTER 10

typedef struct{
  int x,y;
}Point;

typedef struct{
  int height, width;
}Dimensions;

typedef struct{
  bool echo, keypad, line_buffering, cursor;
}InputOptions;

typedef struct{
 MENU *ptr;
 int num_choices;
 ITEM *items[];
}Menu;

typedef struct{
  Point upper_left_corner;
  Dimensions dimensions;
  WINDOW *ptr;
  InputOptions opt;
  Menu *menu;
}Win;

typedef struct{
 Point user_input_start;
 Win win;
 int input;
}InputField;

void initalize_curses_options();

Win* create_main_win(void);
Win *create_dialog_win(void);
void set_input_start(InputField* in_field);
void set_main_content(Win* main);
void set_input_options(Win *new, bool want_echo, bool want_keypad, bool want_line_buffering, bool want_cursor);

void switch_input_options(Win win);
Point give_window_start_point(int y_wanted, int x_wanted);
Dimensions give_dimensions(int h, int w);
Point give_input_start();
WINDOW* create_window(Point win_start, Dimensions dim);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);



#endif // MAIN_H_
