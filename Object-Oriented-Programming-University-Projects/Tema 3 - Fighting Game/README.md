# OOP - Project 3 - Console Fighting Game

Short information:
 - The game is played between 2 players on the same PC or 1 player vs Computer. It is console based, takes inputs during the game. No input/output files.
 - Implemented in C++ (version 17);
 - Uses C++ classes, inheritance and polymorphism, design patterns (Singleton (Game class) and Factory (PlayerFactory class), I wanted to use some sort of Strategy des. pattern for abilities, but didn't do it for now, because of lack of time);
 - Built with: 
 ```bash
 g++.exe -Wall -fexceptions -g -pedantic -Wfatal-errors -Wextra -Werror -Wall -std=c++17 -g
```
 - Checked with Cppcheck: no errors, minor warnings found, ran with:
 ```bash
 cppcheck --enable=all *.cpp
 ```
 - Checked with Valgrind: no memory leaks found, ran with:
 ```bash
 valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main
 ```
 - Has a Makefile to create the `main` executable for bash or WSL, gives no errors, built with:
 ```bash
 make
 ```
