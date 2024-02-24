#include "ncurses.h"
#include "unistd.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

//function
int start_screen(int speed);
int game(int speed, int game);
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

  int ground = LINES*2/5;

  char *title = "Welcome to DINO";
  char *subtitle = "A little game aiming to replicate chrome dino in a terminal, made in C";
  char *ready = "Please press space when ready";

  move (ground -5, (COLS - strlen(title)) /2 );
  printw ("%s", title);
  move (ground -3, (COLS - strlen(subtitle))/2 );
  printw ("%s", subtitle );
  move (ground + 5, COLS /2  -5);
  printw ("Speed : %d", speed);
  move (ground  + 3, (COLS - strlen(ready))/2);
  printw ("%s", ready);

  for (int i = 0; i < COLS; i++){
    mvaddch(ground , i, '_');
  }
  mvaddch( ground +1, 5, '0' );
  mvaddch( ground +2, 5, '0' );

  refresh();

  int c;
  do {
    c = getchar();
  } while (c != ' ');

  game(speed, ground);
 }


int game(int speed, int ground){
  clear();
  for (int i = 0; i < COLS; i++){
    mvaddch(ground , i, '_');
  }
  mvaddch( ground +1, 5, 'O' );
  mvaddch( ground +2, 5, '0' );

  refresh();

  int i = 0;
  do {
    if (getchar() == ' '){
      mvaddch( ground +1, 5, ' ' );
      mvaddch( ground +2, 5, '0' );
      mvaddch( ground +3, 5, '0' );
      refresh();
      usleep(50000);

      mvaddch( ground +2, 5, ' ' );
      mvaddch( ground +3, 5, '0' );
      mvaddch( ground +4, 5, '0' );
      refresh();
      usleep(750000);

      mvaddch( ground +2, 5, '0' );
      mvaddch( ground +3, 5, '0' );
      mvaddch( ground +4, 5, ' ' );
      refresh();
      usleep(100000);

      mvaddch( ground +1, 5, 'O' );
      mvaddch( ground +2, 5, '0' );
      mvaddch( ground +3, 5, ' ' );
      refresh();
      usleep(100000);

      i += 10;
    }
    else {
      i++;
    }

  } while (1);

  end_screen(speed);
}


int end_screen(int speed){

  endwin();
}
