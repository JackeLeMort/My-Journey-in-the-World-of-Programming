#include "ncurses.h"

int main(){
  initscr();
  addstr("Hello World!");
  getch();
  refresh;
  endwin();
  return 0;
}
