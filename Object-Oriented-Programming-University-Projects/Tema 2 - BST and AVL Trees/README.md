# OOP - Project 2 - Binary Search Trees and AVL Trees

Short information:
 - Implemented in C++ (version 17);
 - Uses C++ classes, inheritance and polymorphism;
 - Built with: 
 ```bash
 g++.exe -Wall -fexceptions -g -pedantic -Wfatal-errors -Wextra -Wall -std=c++17 -g
```
 - Checked with Cppcheck: no errors, warnings found (see the screenshots of the reports [here](https://github.com/Nicu-Ducal/Object-Oriented-Programming-University-Projects/tree/master/Tema%202%20-%20BST%20and%20AVL%20Trees/Reports%20of%20Cppcheck%20and%20Valgrind));
 - Checked with Valgrind: no memory leaks found (see the screenshots of the reports [here](https://github.com/Nicu-Ducal/Object-Oriented-Programming-University-Projects/tree/master/Tema%202%20-%20BST%20and%20AVL%20Trees/Reports%20of%20Cppcheck%20and%20Valgrind)), runed with:
 ```bash
 valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main
 ```
 - Has a Makefile to create the `main` executable for bash or WSL, gives no errors, built with:
 ```bash
 g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic -g
 ```
