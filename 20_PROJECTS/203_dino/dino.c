#include "ncurses.h"
#include "unistd.h"
#include "ctype.h"
#include "stdlib.h"

//function
int start_screen(int speed);
int game(int speed);
int end_screen(int score);

//variables, several speed possible
int speed_default = 2;
int score_best = 0;
int score_last = 0;

int main(int argc, char **argv){

  if (argc > 2){
    printf("The programm needs 0 or 1 argument.");
    return 1;
  }
  for (int i = 0; i < strlen(argv[1]); i++){
    if ( isdigit(argv[1][i]) ){
      printf("The argument must be an integer.");
      return 1;
  }
  if (argc == 1){
    int speed = speed_default;
  }
  else if (argc == 2){
    speed = atoi (argv[1]);
  }

  start_screen(speed);

  game(speed);

}

int start_screen(int speed);

int game(int speed){
  initscr();
  cbreak();
  noecho();

  clear();

  int y = LINES;
  int x = COLS;


  endwin();
  return 0;
}

