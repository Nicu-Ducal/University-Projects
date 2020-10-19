#include <iostream>
#include <chrono>
#include <thread>
#include "Sasuke.h"

using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

Sasuke::Sasuke(std::string _PlayerName) : Player(_PlayerName, 850) {
    this->HP = maxHealth;
    this->Character = "Sasuke";
}

Sasuke::~Sasuke() = default;

int Sasuke::attackOne(){
    int initDamage = 25;
    int damage = initDamage + (this->level - 1) * 5;

    this->specialAbility = std::min(100, this->specialAbility + initDamage);
    this->MP = std::min(this->MP + initDamage - attackMana[0], 100);

    std::cout << "\n" << this->getPlayerName() << " has chosen Sword Attack and is going to deal " << damage << " damage.\n";

    this->XP += initDamage;
    if (this->XP >= 100)
        levelUp();

    return damage;
}

int Sasuke::attackTwo(){
    int initDamage = 50;
    int damage = initDamage + (this->level - 1) * 10;

    this->specialAbility = std::min(100, this->specialAbility + initDamage / 3);
    this->MP = std::min(this->MP + initDamage - attackMana[1], 100);

    std::cout << "\n" << this->getPlayerName() << " has chosen Chidori and is going to deal " << damage << " damage.\n";

    this->XP += initDamage / 2;
    if (this->XP >= 100)
        levelUp();

    return damage;
}

int Sasuke::attackThree(){
    int initDamage = 80;
    int damage = initDamage + (this->level - 1) * 10;

    this->specialAbility = std::min(100, this->specialAbility + initDamage / 3);
    this->MP = std::min(this->MP + initDamage / 2 - attackMana[2], 100);

    std::cout << "\n" << this->getPlayerName() << " has chosen Sharingan and is going to deal " << damage << " damage.\n";

    this->XP += initDamage / 2;
    if (this->XP >= 100)
        levelUp();

    return damage;
}

int Sasuke::attackFour(){
    int initDamage = 120;
    int damage = initDamage + (this->level - 1) * 20;

    this->specialAbility = std::min(100, this->specialAbility + initDamage / 3);
    this->MP = std::min(this->MP + initDamage / 3 - attackMana[3], 100);

    std::cout << "\n" << this->getPlayerName() << " has chosen Amaterasu and is going to deal " << damage << " damage.\n";

    this->XP += initDamage / 3;
    if (this->XP >= 100)
        levelUp();

    return damage;
}

int Sasuke::attackSpecial(){
    int initDamage = 150;
    int damage = initDamage + (this->level - 1) * 50;

    std::cout << "\n" << this->getPlayerName() << " has chosen Perfect Susanoo Special Attack and is going to deal " << damage << " damage.\n";

    this->specialAbility = 0;
    this->XP += initDamage / 4;
    if (this->XP >= 100)
        levelUp();

    return damage;
}

void Sasuke::defenceOne(){
    int restHP = 50, restMP = 30;
    std::cout << "\n" << this->getPlayerName() << " has chosen to rest. Recovering " << restHP << " HP and " << restMP << " MP.\n";
    this->HP = std::min(this->HP + restHP, maxHealth);
    this->MP = std::min(this->MP - defenceMana[0] + restMP, 100);
}

void Sasuke::defenceTwo(){
    int healHP = 75 + (this->level - 1) * 10;
    std::cout << "\n" << this->getPlayerName() << " has chosen to heal up. Recovering " << healHP << " HP.\n";
    this->HP = std::min(this->HP + healHP, maxHealth);
    this->MP -= defenceMana[1];
}

void Sasuke::defenceThree(){
    int SusanoShield = 50 + (this->level - 1) * 5;
    std::cout << "\n" << this->getPlayerName() << " has chosen to use Susanoo Shield. Adding up " << SusanoShield << " HP.\n";
    this->Shield = std::min(this->Shield + SusanoShield, 100);
    this->MP -= defenceMana[2];
}

void Sasuke::defenceFour(){
    int SusanoPower = 200 + (this->level - 1) * 30;
    std::cout << "\n" << this->getPlayerName() << " has chosen to use Susanoo Power. Regenerating " << SusanoPower << " HP.\n";
    this->HP = std::min(this->HP + SusanoPower, maxHealth);
    this->MP -= defenceMana[3];
}

void Sasuke::attack(Player* enemy){
    char choice;
    std::cout << "\n\tChoose your next attack: ";
    printTwoRowTable("Sword Attack (1)", "Chidori (2)", "Sharingan (3)", "Amaterasu (4)");
    if (this->specialAbility == 100)
        std::cout << "\n\nYour special attack is ready: Perfect Susanoo(5)\n";
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

void Sasuke::attackComputer(Player* enemy){
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

void Sasuke::defence(){
    char choice;
    std::cout << "\n\tChoose your defense action: ";
    printTwoRowTable("Resting (1)", "Heal Up (2)", "Susanoo Shield (3)", "Susanoo Power (4)");
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

void Sasuke::defenceComputer(){
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
