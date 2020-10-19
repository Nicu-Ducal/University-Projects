#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <thread>
#include "Game.h"

using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

Game::Game(){}

Game::~Game(){
    if (P1 != nullptr){
        delete P1;
        P1 = nullptr;
    }
    if (P2 != nullptr){
        delete P2;
        P2 = nullptr;
    }
    gameMode = 0;
}

Game& Game::Get(){
    static Game gameInstance;
    return gameInstance;
}

void Game::printOneRowTable(std::string firstOption, std::string secondOption){
    std::cout << "\n==================================================================\n";
    std::cout << "||                              ||                              ||\n";
    std::cout << "||" << std::setw(25) << firstOption << "\t||" << std::setw(25) << secondOption << "\t||\n";
    std::cout << "||                              ||                              ||\n";
    std::cout << "==================================================================\n";
}

void Game::choosePlayers(){
    auto& game = Game::Get();
    PlayerFactory *Creator = new PlayerFactory();

    std::string nickname;
    int choice;
    std::vector<std::string> allPlayers = {"Naruto", "Sasuke"};

    // Choosing the first player
    if (game.gameMode == 1)
        std::cout << "\nPlayer One, enter your nickname: ";
    else
        std::cout << "\nEnter your nickname: ";
    std::cin >> nickname;

    std::cout << "Now, choose your fighter: \n";
    for (int i = 0; i < (int) allPlayers.size(); i++)
        std::cout << "\t(" << i + 1 << ") " << allPlayers[i];
    std::cout << "\n\nEnter the corresponding fighter: (1 / 2) ";
    std::cin >> choice;
    while (choice < 1 or choice > (int) allPlayers.size()){
        std::cout << "Please, enter a valid number: ";
        std::cin >> choice;
    }

    game.P1 = Creator->createPlayer(allPlayers[choice - 1], nickname);

    // Choosing the second player
    if (game.gameMode == 1){
        std::cout << "\nPlayer Two, enter your nickname: ";
        std::cin >> nickname;

        std::cout << "Now, choose your fighter: \n";
        for (int i = 0; i < (int) allPlayers.size(); i++)
            std::cout << "\t(" << i + 1 << ") " << allPlayers[i];
        std::cout << "\n\nEnter the corresponding fighter: (1 / 2) ";
        std::cin >> choice;
        while (choice < 1 or choice > (int) allPlayers.size()){
            std::cout << "Please, enter a valid number: ";
            std::cin >> choice;
        }
    } else {
        std::cout << "\nYour opponent is Computer. Computer chooses fighter: ";
        nickname = "Computer";

        choice = (rand() + 3 * (rand() + 47)) % ((int) allPlayers.size()) + 1;

        sleep_for(10ns);
        sleep_until(system_clock::now() + 1s);
        std::cout << allPlayers[choice - 1] << "\n";
    }

    game.P2 = Creator->createPlayer(allPlayers[choice - 1], nickname);

    delete Creator;
    Creator = nullptr;
}

void Game::Round(){
    auto& game = Game::Get();
    char choice;

    // First Player
    std::cout << "\n\t" << game.P1->getPlayerName() << " stats: " << *(game.P1) << "\n\n\t" << game.P2->getPlayerName() << " stats: " << *(game.P2) << "\n";
    std::cout << "\nPlayer One, choose your action: \n";
    printOneRowTable("Attack (1)", "Defend / Regen (2)");
    std::cout << "\n\nPlease enter your choice (1 / 2): ";
    std::cin >> choice;
    while (choice != '1' and choice != '2'){
        std::cout << "\n\nPlease enter a valid choice (1 / 2): ";
        std::cin >> choice;
    }
    if (choice == '1')
        game.P1->attack(P2);
    else
        game.P1->defence();

    sleep_for(10ns);
    sleep_until(system_clock::now() + 1s);

    // Second Player / Computer
    if (game.gameMode == 1){
        std::cout << "\nPlayer Two, choose your action: \n";
        printOneRowTable("Attack (1)", "Defend / Regen (2)");
        std::cout << "\n\nPlease enter your choice (1 / 2): ";
        std::cin >> choice;
        while (choice != '1' and choice != '2'){
            std::cout << "\n\nPlease enter a valid choice (1 / 2): ";
            std::cin >> choice;
        }
        if (choice == '1')
            game.P2->attack(P1);
        else
            game.P2->defence();
    } else {
        std::cout << "\nComputer is choosing an action. ";
        choice = (rand() % 2) + 1 + (int) '0';
        if (choice == '1')
            game.P2->attackComputer(P1);
        else
            game.P2->defenceComputer();
    }

    sleep_for(10ns);
    sleep_until(system_clock::now() + 1s);
}

void Game::Play(){
    auto& game = Game::Get();
    int i = 1;

    std::cout << "\nPerfect, all set! The game is about to start in 5 second, get ready\n";
    for (int i = 5; i > 0; i--){
        if (i <= 3)
            std::cout << i << "\n";
        sleep_for(10ns);
        sleep_until(system_clock::now() + 1s);
    }

    while (game.P1->getHP() > 0 and game.P2->getHP() > 0){
        std::cout << "\n<=============== Round " << i << " ===============>\n";
        game.Round();
        ++i;
    }

    if (game.P1->getHP() <= 0 and game.P2->getHP() <= 0){
        std::cout << "\n<=============== It's a Draw! ===============>\n";
    } else if (game.P1->getHP() <= 0){
        std::cout << "\n" << "<=============== The winner is " << game.P2->getPlayerName() << " ===============>\n";
    } else {
        std::cout << "\n" << "<=============== The winner is " << game.P1->getPlayerName() << " ===============>\n";
    }
}


void Game::StartGame(){
    auto& game = Game::Get();

    std::cout << "====================== Welcome to Fighting Game v0.1 ======================\n\n\n\n";
    std::cout << "To start, choose a game mode: \n";

    game.printOneRowTable("(1) Player vs Player", "(2) Player vs Computer");
    std::cout << "\nYour choice? (1 / 2)  ";
    std::cin >> game.gameMode;
    while (game.gameMode != 1 and game.gameMode != 2){
        std::cout << "Please enter a valid option (1 / 2): ";
        std::cin >> game.gameMode;
    }

    game.choosePlayers();

    game.Play();

    std::cout << "\nTough game! Want to play it one more time? (Y / N) ";
    char restartChoice;
    std::cin >> restartChoice;
    while (restartChoice != 'Y' and restartChoice != 'y' and restartChoice != 'N' and restartChoice != 'n'){
        std::cout << "Please enter a valid letter: (Y / N) ";
        std::cin >> restartChoice;
    }
    if (restartChoice == 'Y' or restartChoice == 'y'){
        std::cout << "\n\n";
        Game::RestartGame();
    } else {
        std::cout << "Thanks for playing. See you next time!\n";
    }
}

void Game::RestartGame(){
    auto& game = Game::Get();
    if (game.P1 != nullptr)
        delete game.P1;
    if (game.P2 != nullptr)
        delete game.P2;
    Game::StartGame();
}
