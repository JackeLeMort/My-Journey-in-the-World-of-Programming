#include "ncurses.h"
#include "unistd.h"

int check_q();

int main(){

  initscr();
  cbreak();
  noecho();

  clear();

  int y = LINES;
  int x = COLS;

  for (int i = 1; i >= 0; i++){

    if (LINES-i <= 0 || COLS-i <= 0){
      clear();
      mvaddstr(LINES/2, COLS/2, "It went out of the screen, to exit please press q");
      getch();

      check_q();
      clear();
      refresh();
      printf("Goodbye !");
      return 1;
    }
    else {
      move( y-i , x-i);
      addch('.');
      getch();
//      sleep(1);
      }
  }
  getch();
  endwin();

  return 0;
}


int check_q(){
  int c;
  do {
    c = getchar();
  } while (c != 'q');
  return 0;
}
