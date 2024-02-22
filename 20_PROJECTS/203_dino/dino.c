#include "ncurses.h"

int main(){
  initscr();

  WINDOW * win;

  move(10,10);
  box(win, 15, 20);
  getch();

  addstr("Hello World!");
  refresh;

  addstr("teeees!");
  refresh;

  getch();

  endwin();

  return 0;
}
