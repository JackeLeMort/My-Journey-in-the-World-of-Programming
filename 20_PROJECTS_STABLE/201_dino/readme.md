# Dino.c

(This is the V1 of my dino project, I'm currently working on a improved version in ../30_PROJECTS_WIP)

This project is a recreation of chrome's dino in C (everybody told me after that I shouldn't do it in C, so I will redo it in C++ in the future).
This is my first real "project", it is more than 300 lines of code now, not nested, readable (or so I hope).

It uses ncurses and multithreading. 


How to launch:  
    There is a make file, juste either   
    - Clone the whole repo then cd (or zoxide, amazing tool, I recommand) here   
    - Or download the 2 files then type `make`,   
    - Or just type `cc dino.c -o dino.out -lncurses`.    
you'll need the `ncurses library`, but it's likely already available on your system.


Commands:
 - add a number between 1 and infinite as an argument to programm to modify the speed level.
 - press q in the game to go to end_screen.
 - press space to jump.  
