#include "ncurses.h"
#include "unistd.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "pthread.h"
#include "stdbool.h"


int main(void){
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(false);

  for (;;){
    timeout(10000000);
    char c = getch();
    move(LINES/2, COLS/2);
    printw("%c", c);
    //sleep(1);
    }
}
