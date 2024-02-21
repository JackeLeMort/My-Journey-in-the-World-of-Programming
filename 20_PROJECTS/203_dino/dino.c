#include "ncurses.h"

int main(){
  initscr();
  addstr("Hello World!");
  refresh;
  addstr("teeees!");
  refresh;
  getch();
  endwin();
  return 0;
}
