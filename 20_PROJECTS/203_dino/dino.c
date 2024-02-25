#include "ncurses.h"
#include "unistd.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "pthread.h"

//function
int start_screen(int speed); // 69
int game(int speed); // 104
int end_screen(int distance); //136

int character(int position);


//variables
int character_position = 0;
int *ennemy_position;
int ennemy_number_max =3;
int ennemy_number_screen;

bool game_state;
int ground;

int distance;

int speed;
int speed_default = 2;

int score_last = 0;
int game_number_session = 1;
//int game_number_all = $idk how to do that yet
int score_best_session = 0;
//int score_best_all = 0;

char *title = "Welcome to DINO";
char *subtitle = "A little game aiming to replicate chrome dino in a terminal, made in C";
char *ready = "Please press space when ready";

char *score = "you ran an insane amount of: ";



// main function, check arguments and start start_screen
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


//init screem, welcomes player and wait for his input to start game
int start_screen(int speed) {
  initscr();
  cbreak();
  noecho();
  clear();

  ground = LINES*2/5;

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

  game(speed);
 }


//
int game(int speed){

  clear();
  for (int i = 0; i < COLS; i++){
    mvaddch(ground , i, '_');
  }
  game_state = true;

  //character
  mvaddch( ground +1, 5, 'O' );
  mvaddch( ground +2, 5, '0' );
  refresh();

  int distance = 0;

  do {
    if (getchar() == 'q') {
      game_state = false;
      end_screen(distance);
    }
    else if (getchar() == ' '){

      timeout(900000);
      character(1);
      character(2);
      character(1);

      distance += 10;
      }
    character(0);
    distance += 1;
    } while (game_state = true);
}


int end_screen (int distance){

  move(ground +5, COLS/2 - strlen(score) -2);
  printw ("%s%i", score, distance);
  getch();
  endwin();
  exit(0);
}


// character position
int character(int position){

  switch (position) {

    case 1:
      mvaddch( ground +1, 5, ' ' );
      mvaddch( ground +2, 5, '0' );
      mvaddch( ground +3, 5, '0' );
      mvaddch( ground +4, 5, ' ' );
      refresh();
      character_position = 1;
      usleep(100000);
      break;

    case 2:
      mvaddch( ground +2, 5, ' ' );
      mvaddch( ground +3, 5, '0' );
      mvaddch( ground +4, 5, '0' );
      refresh();
      character_position = 2;
      usleep(800000);
      break;

    case 0:
      mvaddch( ground +1, 5, '0' );
      mvaddch( ground +2, 5, '0' );
      mvaddch( ground +3, 5, ' ' );
      refresh();
      character_position = 0;
      usleep(100000);
  }
}



void *collision(){
  do {
    for (int i = 0; i < ennemy_number_max; i++) {
      if (character_position == ennemy_position[i] ) {
        game_state = false;
        end_screen(distance);
      }
    }
  } while (game_state = true);
}
