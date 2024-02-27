#include "ncurses.h"
#include "unistd.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "pthread.h"
#include "stdbool.h"


//function
int start_screen(); // 69
int game(); // 104
int end_screen(); //136

int character(int position);

void *collision(void *vargp);
void *distance_travelled(void *vargp);

//variables
int character_position = 0;
int ennemy_number_max = 3;
int ennemy_position[3];
int ennemy_number_screen;

int ground;
int right;
int left;

bool game_state;
int distance;
int speed;
int speed_default = 2;

bool replay = true;
int score_last = 0;
int game_number_session = 1;
//int game_number_all = $idk how to do that yet
int score_best_session = 0;
//int score_best_all = 0;

char *title = "Welcome to DINO";
char *subtitle = "A little game aiming to replicate chrome dino in a terminal, made in C";
char *ready = "Please press space when ready";
char *score = "You ran an insane amount of: ";
char *play_again = "Press 'space' to play again or any other key to quit.";


// main function, check arguments and start start_screen
int main(int argc, char **argv)
{
  if (argc > 2)
    {
      printf ("The programm needs 0 or 1 argument.");
      return 1;
    }
  if (argc == 2){
    for (int i = 0; i < strlen(argv[1]); i++)
      {
      if ( !isdigit (argv[1][i]) )
        {
        printf ("The argument must be an integer.");
        return 1;
        }
      }
    speed = atoi(argv[1]);
  }
  else if (argc == 1) {
    speed = speed_default;
  }
  start_screen();
  while (replay == true) {
    game();
    end_screen();
  }
  endwin();
  return 0;
}


//init screem, welcomes player and wait for his input to start game
int start_screen() {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(false);
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
	return 0;
 }


//
int game(){

  clear();
  for (int i = 0; i < COLS; i++){
    mvaddch(ground , i, '_');
  }
  refresh();

  //ennemy_position = malloc(ennemy_number_max * sizeof(int));
  game_state = true;

  pthread_t collision_id;
  pthread_t distance_travelled_id;
  pthread_create (&collision_id, NULL, collision, NULL);
  pthread_create (&distance_travelled_id, NULL, distance_travelled, NULL);

  //character
  mvaddch( ground +1, 5, 'O' );
  mvaddch( ground +2, 5, '0' );
  refresh();

  distance = 0;
  char c;

  while (game_state) {

    timeout(100);
    c = getch();

    if (c == ' '){
      character(1);
      character(2);
      character(1);
      flushinp();
      character(0);
    }
    else if (c == 'q') {
      return 0;
    }
    else {
      character(0);
    }
  }
  return 0;
}

// END SCREEN
int end_screen (){
  game_state = false;
  //free(ennemy_position);
  refresh();
  move(ground -5, COLS/2 - strlen(score)/2 -2);
  printw ("%s%i", score, distance);
  mvprintw(ground-3, COLS/2 - strlen(play_again)/2, "%s", play_again);
  timeout(-10);
  int c = getch();
  if (c == ' ') {
    replay = true;
    return 0;
  }
  else {
    replay = false;
    return 0;
  }
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




//check if lose when game is running
void *collision(void *vargp){
  while (game_state == true) {
    for (int i = 0; i < ennemy_number_screen; i++) {
      if (character_position == ennemy_position[i] ) {
        game_state = false;
      }
      usleep(100000*2/speed);
    }
  }
}


//display current score while playing
void *distance_travelled(void *vargp){
  WINDOW *distance_box = newwin (3, 15, 2, COLS-20);
  noecho();
  do {
    distance += 1;
    mvwprintw (distance_box, 1, 1, "distance: %d   ", distance);
    redrawwin(distance_box);
    wrefresh(distance_box);
    usleep(100000*2/speed);
  } while (game_state == true);
  delwin (distance_box);
  pthread_exit;
}
