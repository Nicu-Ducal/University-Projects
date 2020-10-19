#include <iostream>
#include <iomanip>
#include <string>
#include "Player.h"

Player::Player(std::string _PlayerName, int _maxHealth) : PlayerName(_PlayerName), MP(20), Shield(50), level(1), XP(0), specialAbility(0), maxHealth(_maxHealth) {
    //std::cout << "Creating player\n";
}

Player::~Player(){
    PlayerName.clear();
    Character.clear();
}

int Player::getHP(){
    return this->HP;
}

void Player::dealDamage(int damage){
    if (this->Shield > 0){
        int lowest = std::min(this->Shield, damage);
        damage -= lowest;
        this->Shield -= lowest;
    }
    this->HP -= damage;
}

std::string Player::getPlayerName(){
    return this->PlayerName;
}

void Player::levelUp(){
    this->level += this->XP / 100;
    this->XP %= 100;
    std::cout << "\n" << this->getPlayerName() << " has leveled up! He's now at level " << this->level;
}

void Player::printTwoRowTable(std::string firstOption, std::string secondOption, std::string thirdOption, std::string fourthOption) const{
    std::cout << "\n==================================================================\n";
    std::cout << "||                              ||                              ||\n";
    std::cout << "||" << std::setw(25) << firstOption << "\t||" << std::setw(25) << secondOption << "\t||\n";
    std::cout << "||                              ||                              ||\n";
    std::cout << "==================================================================\n";
    std::cout << "||                              ||                              ||\n";
    std::cout << "||" << std::setw(25) << thirdOption << "\t||" << std::setw(25) << fourthOption << "\t||\n";
    std::cout << "||                              ||                              ||\n";
    std::cout << "==================================================================\n";
}


void Player::print(std::ostream& out) const{
    out << "\nPlayer's Name: " << this->PlayerName << "\nCharacter: " << this->Character;
    out << "\nHealth Points: " << this->HP << "/" << this->maxHealth << " , Shield Points: " << this->Shield << "/" << 100;
    out << ", Mana Points: " << this->MP << "/" << 100;
    out << "\nLevel: " << this->level << ", XP: " << this->XP << "/" << 100;
    out << "\nSpecial Ability: ";
    if (specialAbility == 100){
        out << "READY!" << "\n";
    }
    else{
        for (int i = 1, temp = this->specialAbility / 10; i <= 10; i++, temp--){
            if (temp > 0)
                out << "#";
            else
                out << "*";
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Player& player){
    player.print(out);
    return out;
}
