#include "ncurses.h"
#include "unistd.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"

int visual();

int main() {
  char *title = "Welcome to DINO";
  char *subtitle = "A little game aiming to replicate chrome dino in a terminal, made in C";
  printf("%s\n\n%s", title, subtitle);
  sleep(1);

  initscr();
  cbreak();
  noecho();
  clear();

  move (LINES/3, (COLS - strlen(title))/2 );
  printw ("%s\n\n", title);
  move (LINES /3 +3, (COLS - strlen(subtitle))/2 );
  printw ("%s", subtitle );
  refresh();
  getch();
}
