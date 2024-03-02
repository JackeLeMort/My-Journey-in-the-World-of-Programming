# Dino.c

This project is a recreation of chrome's dino in C (everybody told me after that I shouldn't do it in C, so I will redo it in C++ in the future).
This is my first real "project", it is more than 300 lines of code now, not nested, readable (or so I hope).

It uses ncurses library and multithreading. 


How to launch:
    There is a make file, juste either clone the whole repo then cd here or download the 2 files then type `make`, you'll need the ncurses library,   but she's likely to already be available on your system.

Or just type `cc dino.c -o dino.out -lncurses`.  


Commands:
 - add a number between 1 and infinite as an argument to programm to modify the speed level.
 - press q in the game to go to end_screen.
 - press space to jump.  


  
  What's left to do:
   - [x] create ennemies (first attempt didn't go so well).
   - [x] recreate the collision thread, to detect when the player lose (same).
   - [x] create the best score, last score and game number window
   - [ ] improve ennemies, randomize apparitions
  
  
Maybe later:
- background and color
- store best score
