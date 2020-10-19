main: main.o node.o NodeAVL.o Tree.o BST.o AVL.o
	g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic -g main.o node.o NodeAVL.o Tree.o BST.o AVL.o -o main

main.o: main.cpp
	g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic -g -c main.cpp

node.o: node.cpp node.h
	g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic -g -c node.cpp

NodeAVL.o: NodeAVL.cpp NodeAVL.h
	g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic -g -c NodeAVL.cpp

Tree.o: Tree.cpp Tree.h
	g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic -g -c Tree.cpp

BST.o: BST.cpp BST.h
	g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic -g -c BST.cpp

AVL.o: AVL.cpp AVL.h
	g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic -g -c AVL.cpp

clean:
	rm *.o main
