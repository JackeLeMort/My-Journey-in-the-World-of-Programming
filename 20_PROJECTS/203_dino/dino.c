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

void *ennemies(void *vargp);
void *collision(void *vargp);
void *distance_travelled(void *vargp);

//variables
int character_position = 0;
int ennemy_number_max = 3;
int ennemy_position = -1;

int ground;
bool game_state;
int distance = 0;
int speed;
int speed_default = 2;
int jump_time = 80000;

bool replay = true;
int score_last = 0;
int game_number_session = 1;
//int game_number_all = $idk how to do that yet
int score_best_session = 0;
int score_best_all = 0;

char *title = "Welcome to DINO";
char *subtitle = "A little game aiming to replicate chrome dino in a terminal, made in C";
char *ready = "Please press space when ready";
char *score = "You ran an insane amount of: ";
char *play_again = "Press 'space' to play again or any other key to quit.";

//init screen and windows
WINDOW *charac_enn;
WINDOW *distance_box;

pthread_mutex_t screen_mutex = PTHREAD_MUTEX_INITIALIZER;


// main function, check arguments and start functions
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
    speed = (100000*2)/ atoi(argv[1]);
  }
  else if (argc == 1) {
    speed = (100000*2)/ speed_default;
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

  charac_enn = newwin (4, 100, ground+1, COLS/2-50);
  distance_box = newwin (3, 16, 2, COLS-20);

  move (ground -5, (COLS - strlen(title)) /2 );
  printw ("%s", title);
  move (ground -3, (COLS - strlen(subtitle))/2 );
  printw ("%s", subtitle );
  move (ground  + 5, (COLS - strlen(ready))/2);
  printw ("%s", ready);
  move (ground + 7, COLS /2  -5);
  printw ("Speed: %d", speed*2/100000);

  for (int i = 0; i < 100; i++){
    mvaddch(ground, COLS/2-50 +i, '_');
  }
  refresh();

  mvwaddch(charac_enn, 0, 4, '0' );
  mvwaddch(charac_enn, 1, 4, '0' );
  wnoutrefresh(charac_enn);
  wrefresh(charac_enn);

  doupdate();

  char c;
  while (c != ' ') {
    c = getch();
  } 
	return 0;
 }


//game
int game(){

  clear();
  refresh();

  for (int i = 0; i < 100; i++){
    mvaddch(ground, COLS/2-50 +i, '_');
    refresh();
    usleep(5000);
  }

  game_state = true;

  //character
  mvwaddch(charac_enn, 0, 5, 'O' );
  mvwaddch(charac_enn, 1, 5, '0' );
  wrefresh(charac_enn);

  pthread_t collision_id;
  pthread_t distance_travelled_id;
  pthread_t ennemies_id;
  pthread_create (&collision_id, NULL, collision, NULL);
  pthread_create (&distance_travelled_id, NULL, distance_travelled, NULL);
  pthread_create (&ennemies_id, NULL, ennemies, NULL);


  char c;

  while (game_state) {

    noecho();
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
      game_state = false;
    }
    else {
      character(0);
    }
  }
  return 0;
}

// END SCREEN
int end_screen (){
  clear();
  refresh();
  score_last = distance;
  if (distance > score_best_session) { score_best_session = distance;}
  if (distance > score_best_all) { score_best_all = distance;}
  move(ground -5, COLS/2 - strlen(score)/2 -2);
  printw ("%s%i", score, score_last);
  distance = 0;
  mvprintw(ground-3, COLS/2 - strlen(play_again)/2, "%s", play_again);
  refresh();
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
      pthread_mutex_lock(&screen_mutex);
      mvwaddch( charac_enn, 0, 5, ' ' );
      mvwaddch( charac_enn, 1, 5, '0' );
      mvwaddch( charac_enn, 2, 5, '0' );
      mvwaddch( charac_enn, 3, 5, ' ' );
      wrefresh(charac_enn);
      character_position = 1;
      pthread_mutex_unlock(&screen_mutex);
      usleep(jump_time);
      break;

    case 2:
      pthread_mutex_lock(&screen_mutex);
      mvwaddch( charac_enn, 1, 5, ' ' );
      mvwaddch( charac_enn, 2, 5, '0' );
      mvwaddch( charac_enn, 3, 5, '0' );
      wrefresh(charac_enn);
      character_position = 2;
      pthread_mutex_unlock(&screen_mutex);
      usleep(jump_time*8);
      break;

    case 0:
      pthread_mutex_lock(&screen_mutex);
      mvwaddch( charac_enn, 0, 5, '0' );
      mvwaddch( charac_enn, 1, 5, '0' );
      mvwaddch( charac_enn, 2, 5, ' ' );
      wrefresh(charac_enn);
      character_position = 0;
      pthread_mutex_unlock(&screen_mutex);
      usleep(jump_time);
      break;
  }
}

void *ennemies(void *vargp) {
  noecho();
  while (game_state) {
    for (int i = 100; i > 0; i--) {
      if (game_state == false) {i = -1; }
        pthread_mutex_lock(&screen_mutex);
        mvwprintw (charac_enn, 0, i, "< ");
        wrefresh(charac_enn);
        pthread_mutex_unlock(&screen_mutex);
        if ( i == 5 ) { ennemy_position = 0; }
        else if ( i == 4 ) { ennemy_position = -1; }
        usleep(speed);
    }
    mvwprintw (charac_enn, 0, 1, " ");
    wrefresh(charac_enn);
  }
}


//check if lose when game is running
void *collision(void *vargp){
  while (game_state == true) {
    if ( character_position == ennemy_position ) {
      game_state = false;
    }
  }
  pthread_exit(NULL);
}


//display current score while playing
void *distance_travelled(void *vargp){
  noecho();
  distance = 0;
  refresh();
  while (game_state) {
    distance += 1;
    pthread_mutex_lock(&screen_mutex);
    mvwprintw (distance_box, 2, 1, "distance: %d  ", distance);
    redrawwin(distance_box);
    wrefresh(distance_box);
    pthread_mutex_unlock(&screen_mutex);
    usleep(speed);
  }
  pthread_exit(NULL);
}
