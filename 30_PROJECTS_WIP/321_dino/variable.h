#include <ncurses.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>


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


