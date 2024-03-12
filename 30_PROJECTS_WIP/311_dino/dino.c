#include "ncurses.h"
#include "unistd.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "pthread.h"
#include "stdbool.h"


//FUNCTIONS and THREADS
int start_screen(); //
int game();
int end_screen();

int character(int position);

void *ennemies(void *vargp);
void *collision(void *vargp);
void *distance_travelled(void *vargp);

pthread_mutex_t screen_mutex = PTHREAD_MUTEX_INITIALIZER;

//VARIABLES
//character and ennemies
int character_position = 0;
int ennemy_number_max = 3;
int ennemy_position = -1;

//distance, speed and play
int distance = 0;
int speed;
int speed_default = 2;
int speed_level;
int jump_time;
bool game_state;
bool replay = true;

//scores
int score_last = 0;
int game_number_session = 1;
//int game_number_all = $idk how to do that yet
int score_best_session = 0;
int score_best_all = 0;

//text for the user
char *title = "Welcome to DINO";
char *subtitle = "A little game aiming to replicate chrome dino in a terminal, made in C";
char *ready = "Please press space when ready";
char *score = "You ran an insane amount of: ";
char *play_again = "Press 'space' to play again or any other key to quit.";

//windows and placement
int ground;
WINDOW *charac_enn;
WINDOW *distance_box;
WINDOW *score_box;



// main function, check if (possible) arguments are alright, start functions start_screen, games and end_screen and initilalise speed related variables
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
        printf ("The argument must be an (positive) integer.");
        return 1;
        }
      }
    speed_level = atoi(argv[1]);
    speed = (100000*2)/ speed_level;
  }
  else if (argc == 1) {
    speed = (100000*2)/ speed_default;
  }
  jump_time = 80000 - ((speed_level -2) * 4000);
  start_screen();
  while (replay == true) {
    game();
    end_screen();
  }
  endwin();
  return 0;
}


//init screen and important variables, welcomes player and wait for his input to start the game
int start_screen() {

  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(false);
  clear();

  ground = LINES*2/5;

  charac_enn = newwin (4, 100, ground+1, COLS/2-50);
  distance_box = newwin (3, 16, 1, COLS-20);
  score_box = newwin (4, 15, 1, 3);

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


//game, recreate playscreen, start all threads, invoke character function every 0.1 second, depending on input (or stop game).
int game(){

  clear();
  refresh();

  pthread_mutex_lock(&screen_mutex);
  for (int i = 0; i < 100; i++){
    mvaddch(ground, COLS/2-50 +i, '_');
    refresh();
    usleep(5000);
  }

  ennemy_position = -1;
  game_state = true;

  //character
  mvwaddch(charac_enn, 0, 5, 'O' );
  mvwaddch(charac_enn, 1, 5, '0' );
  wrefresh(charac_enn);
  pthread_mutex_unlock(&screen_mutex);

  pthread_t collision_id;
  pthread_t distance_travelled_id;
  pthread_t ennemies_id;
  pthread_create (&collision_id, NULL, collision, NULL);
  pthread_create (&distance_travelled_id, NULL, distance_travelled, NULL);
  pthread_create (&ennemies_id, NULL, ennemies, NULL);

  pthread_mutex_lock(&screen_mutex);
  redrawwin(score_box);
  wrefresh(score_box);
  pthread_mutex_unlock(&screen_mutex);

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

// END SCREEN, store score, display it and ask for replay
int end_screen (){
  clear();
  refresh();
  score_last = distance;
  if (distance > score_best_session) { score_best_session = distance;}
  if (distance > score_best_all) { score_best_all = distance;}
  pthread_mutex_lock(&screen_mutex);
  move(ground -5, COLS/2 - strlen(score)/2 -2);
  printw ("%s%i", score, score_last);
  mvprintw(ground-3, COLS/2 - strlen(play_again)/2, "%s", play_again);
  mvwprintw (score_box, 1, 1, "best: %d\n last: %d", score_best_session, score_last);
  wrefresh(score_box);
  pthread_mutex_unlock(&screen_mutex);

  distance = 0;

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



// change character position in the character+ennenies_window depending on what the parent function (game()) send (either 0 or 1-2-1-0)
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

//create ennemies, make them move toward the character
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


//check if character and ennemie are at the same location, if yes it stops the game
void *collision(void *vargp){
  while (game_state == true) {
    if ( character_position == ennemy_position ) {
      game_state = false;
    }
  }
  pthread_exit(NULL);
}


//count and display the already travelled distance, the score
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
