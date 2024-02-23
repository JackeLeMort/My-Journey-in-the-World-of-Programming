#include "ncurses.h"
#include "unistd.h"

int check_q();

int main(){

  initscr();
  cbreak();
  clear();

  int y = LINES;
  int x = COLS;

  for (int i = 0; i >= 0; i++){

    if (LINES-i < 0 || COLS-i < 0){
      clear();
      mvaddstr(LINES/2, COLS/2, "went out of the screen");

      check_q();
    }
    move( y-i , x-i);
    addch('.');
    getch();
//    sleep(1);
  }
  getch();
  endwin();

  return 0;
}

int check_q(){
  c = getch();
  for (c != "q"){
    c = getch();
  }
}
