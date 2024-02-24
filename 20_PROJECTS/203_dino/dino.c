#include "ncurses.h"
#include "unistd.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"

//function
int start_screen(int speed);
int game(int speed);
int end_screen(int score);

//variables
int speed;
int speed_default = 2;
int score_best = 0;
int score_last = 0;
int game_number_session = 1;
//int game_number_all = $idk how to do that yet

int main(int argc, char **argv)
{
  if (argc > 2)
    {
      printf ("The programm needs 0 or 1 argument.");
      return 1;
    }
  if (argc == 2){
    for (int i = 0; i < strlen( argv[1] ); i++)
      {
      if ( isdigit (argv[1][i]) )
        {
        printf ("The argument must be an integer.");
        return 1;
        }
      }
    start_screen( atoi(argv[1]) );
  }
  if (argc == 1) {
    speed = speed_default;
  }
  else if (argc == 2) {
    speed = atoi (argv[1]);
  }
  start_screen(speed);
}


int start_screen(int speed) {
  initscr();
  cbreak();
  noecho();
  clear();

  char *title = "Welcome to DINO";
  char *subtitle = "A little game aiming to replicate chrome dino in a terminal, made in C";
  char *ready = "Please press space when ready";

  move (LINES/3, (COLS - strlen(title)) /2 );
  printw ("%s", title);
  move (LINES /3 +3, (COLS - strlen(subtitle))/2 );
  printw ("%s", subtitle );
  move (LINES /3 +6, COLS /2  -5);
  printw ("Speed : %d", speed);
  move (LINES /3 +8, (COLS - strlen(ready))/2);
  printw ("%s", ready);

  refresh();

  int c;
  do {
    c = getchar();
  } while (c != ' ');

  game(speed);
 }


int game(int speed){
  clear();

  endwin();
  return 0;
}

