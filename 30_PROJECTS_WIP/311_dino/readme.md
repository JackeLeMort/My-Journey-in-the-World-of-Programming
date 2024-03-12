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


# Next Version's TODO  

Priority
   - [ ] Move variable and header to another file and transform variables to structures
   - [ ] Store best and last score accross sessions
   
Else
   - [ ] improve ennemie [0/2]
     - [ ] randomize delay between apparition
     - [ ] create several type of ennemies, and randomly pick one every ennemy appartion
   - [ ] improve user experience
     - [ ] allow quitting on the home_screen
     - [ ] allow quitting while jumping
     - [ ] allow changing speed level on end_screen
     - [ ] allow changing speed level on start_screen
   - [ ] improve desging overall
     - [ ] backgrouds
     - [ ] character
     - [ ] ennemies
     
