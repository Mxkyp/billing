#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <curses.h>

// window parameters
#define INTERFACE_HEIGHT 12
#define INTERFACE_WIDTH  26
#define MAIN_Y (LINES - INTERFACE_HEIGHT)/2
#define MAIN_X (COLS - INTERFACE_WIDTH)/2

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
  Point upper_left_corner;
  Dimensions dimensions;
  WINDOW *ptr;
  InputOptions opt;
}Win;

void initalize_curses_options();

Win init_main_win(void);
void set_main_content(Win* main);
void paint_main_header(Win* main);
void paint_main_menu(Win *main);
void set_input_options(Win *new, bool want_echo, bool want_keypad, bool want_line_buffering, bool want_cursor);

void switch_input_options(Win win);
Point give_window_start_point(int y_wanted, int x_wanted);
Dimensions give_dimensions(int h, int w);
WINDOW* create_window(Point win_start, Dimensions dim);

/*paints the default borders around the window, if specified calls a function to paint the windows details*/
void paint_window(Win *win, void(*paint_details)(Win *win));
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

#endif // MAIN_H_
