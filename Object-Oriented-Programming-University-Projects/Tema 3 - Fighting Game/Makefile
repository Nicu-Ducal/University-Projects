CXX = g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -pedantic -g
OBJECTS = main.o Game.o Player.o Naruto.o Sasuke.o PlayerFactory.o

main: $(OBJECTS)
	$(CXX) -o main $(OBJECTS)

main.o: main.cpp
	$(CXX) -c main.cpp

Game.o: Game.cpp Game.h
	$(CXX) -c Game.cpp

Player.o: Player.cpp Player.h
	$(CXX) -c Player.cpp

Naruto.o: Naruto.cpp Naruto.h
	$(CXX) -c Naruto.cpp

Sasuke.o: Sasuke.cpp Sasuke.h
	$(CXX) -c Sasuke.cpp

PlayerFactory.o: PlayerFactory.cpp PlayerFactory.h
	$(CXX) -c PlayerFactory.cpp


clean:
	rm *.o main
