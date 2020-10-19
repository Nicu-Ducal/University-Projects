#include <iostream>
#include <chrono>
#include <thread>
#include "Naruto.h"

using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

Naruto::Naruto(std::string _PlayerName) : Player(_PlayerName, 1000) {
    this->HP = maxHealth;
    this->Character = "Naruto";
}

Naruto::~Naruto() = default;

int Naruto::attackOne(){
    int initDamage = 20;
    int damage = initDamage + (this->level - 1) * 5;;

    this->specialAbility = std::min(100, this->specialAbility + initDamage);
    this->MP = std::min(this->MP + initDamage - attackMana[0], 100);

    std::cout << "\n" << this->getPlayerName() << " has chosen Fist Attack and is going to deal " << damage << " damage.\n";

    this->XP += initDamage;
    if (this->XP >= 100)
        levelUp();

    return damage;
}

int Naruto::attackTwo(){
    int initDamage = 50;
    int damage = initDamage + (this->level - 1) * 10;

    this->specialAbility = std::min(100, this->specialAbility + initDamage / 2);
    this->MP = std::min(this->MP + initDamage - attackMana[1], 100);

    std::cout << "\n" << this->getPlayerName() << " has chosen Shadow Clones and is going to deal " << damage << " damage.\n";

    this->XP += initDamage / 2;
    if (this->XP >= 100)
        levelUp();

    return damage;
}

int Naruto::attackThree(){
    int initDamage = 75;
    int damage = initDamage + (this->level - 1) * 10;

    this->specialAbility = std::min(100, this->specialAbility + initDamage / 3);
    this->MP = std::min(this->MP + initDamage / 2 - attackMana[2], 100);

    std::cout << "\n" << this->getPlayerName() << " has chosen Rasengan and is going to deal " << damage << " damage.\n";

    this->XP += initDamage / 2;
    if (this->XP >= 100)
        levelUp();

    return damage;
}

int Naruto::attackFour(){
    int initDamage = 100;
    int damage = initDamage + (this->level - 1) * 20;

    this->specialAbility = std::min(100, this->specialAbility + initDamage / 3);
    this->MP = std::min(this->MP + initDamage / 3 - attackMana[3], 100);

    std::cout << "\n" << this->getPlayerName() << " has chosen Rasenshuriken and is going to deal " << damage << " damage.\n";

    this->XP += initDamage / 3;
    if (this->XP >= 100)
        levelUp();

    return damage;
}

int Naruto::attackSpecial(){
    int initDamage = 150;
    int damage = initDamage + (this->level - 1) * 50;

    std::cout << "\n" << this->getPlayerName() << " has chosen Sage Mode Special Attack and is going to deal " << damage << " damage.\n";

    this->specialAbility = 0;
    this->XP += initDamage / 4;
    if (this->XP >= 100)
        levelUp();

    return damage;
}

void Naruto::defenceOne(){
    int restHP = 20, restMP = 30;
    std::cout << "\n" << this->getPlayerName() << " has chosen to rest. Recovering " << restHP << " HP and " << restMP << " MP.\n";
    this->HP = std::min(this->HP + restHP, maxHealth);
    this->MP = std::min(this->MP - defenceMana[0] + restMP, 100);
}

void Naruto::defenceTwo(){
    int healHP = 75 + (this->level - 1) * 10;
    std::cout << "\n" << this->getPlayerName() << " has chosen to heal up. Recovering " << healHP << " HP.\n";
    this->HP = std::min(this->HP + healHP, maxHealth);
    this->MP -= defenceMana[1];
}

void Naruto::defenceThree(){
    int shieldUp = 50 + (this->level - 1) * 5;
    std::cout << "\n" << this->getPlayerName() << " has chosen to shield up. Setting shield to " << shieldUp << " HP.\n";
    this->Shield = std::min(this->Shield + shieldUp, 100);
    this->MP -= defenceMana[2];
}

void Naruto::defenceFour(){
    int regenHP = 150 + (this->level - 1) * 25;
    std::cout << "\n" << this->getPlayerName() << " has chosen to regenerate. Regeneration " << regenHP << " HP.\n";
    this->HP = std::min(this->HP + regenHP, maxHealth);
    this->MP -= defenceMana[3];
}

void Naruto::attack(Player* enemy){
    char choice;
    std::cout << "\n\tChoose your next attack: ";
    printTwoRowTable("Fist Attack (1)", "Shadow Clones (2)", "Rasengan (3)", "Rasenshuriken (4)");
    if (this->specialAbility == 100)
        std::cout << "\n\nYour special attack is ready: Sage Mode(5)\n";
    std::cout << "Your choice (1 / 2 / 3 / 4 / 5) : ";

    while(true){
        std::cin >> choice;

        int numChoice = (int) choice - (int) '0';
        if (numChoice < 1 or numChoice > 5){
            std::cout << "\nPlease enter a valid choice : ";
        } else if (numChoice == 5 and this->specialAbility != 100){
            std::cout << "\nYour special attack is not ready. Choose a normal attack: ";
            continue;
        } else if (this->attackMana[numChoice - 1] > this->MP){
            std::cout << "\nYou don't have enough mana points. Choose another attack: ";
            continue;
        } else {
            break;
        }
    }

    sleep_for(10ns);
    sleep_until(system_clock::now() + 1s);

    int damage;
    if (choice == '1')
        damage = attackOne();
    else if (choice == '2')
        damage = attackTwo();
    else if (choice == '3')
        damage = attackThree();
    else if (choice == '4')
        damage = attackFour();
    else
        damage = attackSpecial();

    enemy->dealDamage(damage);
}

void Naruto::attackComputer(Player* enemy){
    sleep_for(10ns);
    sleep_until(system_clock::now() + 1s);

    int damage, choice, limit = 1;

    if (this->specialAbility == 100){
        damage = this->attackSpecial();
    } else {
        for (int i = 1; i < (int)this->attackMana.size(); i++){
            if (this->attackMana[i] <= this->MP)
                ++limit;
        }
        choice = (rand() % limit) + 1;
        switch(choice){
            case 1:
                damage = this->attackOne();
                break;
            case 2:
                damage = this->attackTwo();
                break;
            case 3:
                damage = this->attackThree();
                break;
            case 4:
                damage = this->attackFour();
        }
    }

    enemy->dealDamage(damage);
}


void Naruto::defence(){
    char choice;
    std::cout << "\n\tChoose your defense action: ";
    printTwoRowTable("Resting (1)", "Heal Up (2)", "Shield Up (3)", "Regeneration (4)");
    std::cout << "Your choice (1 / 2 / 3 / 4) : ";

    while(true){
        std::cin >> choice;

        int numChoice = (int) choice - (int) '0';
        if (numChoice < 1 or numChoice > 4){
            std::cout << "\nPlease enter a valid choice : ";
        } else if (this->defenceMana[numChoice - 1] > this->MP){
            std::cout << "\nYou don't have enough mana points. Choose another defence method: ";
            continue;
        } else {
            break;
        }
    }

    sleep_for(10ns);
    sleep_until(system_clock::now() + 1s);

    if (choice == '1')
        defenceOne();
    else if (choice == '2')
        defenceTwo();
    else if (choice == '3')
        defenceThree();
    else
        defenceFour();
}

void Naruto::defenceComputer(){
    sleep_for(10ns);
    sleep_until(system_clock::now() + 1s);

    int choice, limit = 1;

    for (int i = 1; i < (int)this->defenceMana.size(); i++){
        if (this->defenceMana[i] <= this->MP)
            ++limit;
    }
    choice = (rand() % limit) + 1;
    switch(choice){
        case 1:
            this->defenceOne();
            break;
        case 2:
            this->defenceTwo();
            break;
        case 3:
            this->defenceThree();
            break;
        case 4:
            this->defenceFour();
    }
}

