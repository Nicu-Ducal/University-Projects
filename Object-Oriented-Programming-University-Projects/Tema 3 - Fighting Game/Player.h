#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player{
    public:
        Player(std::string _PlayerName, int _maxHealth = 1000);
        virtual ~Player();

        void print(std::ostream& out) const;
        friend std::ostream& operator<<(std::ostream& out, const Player& player);

        int getHP();
        void dealDamage(int damage);
        std::string getPlayerName();
        void levelUp();

        virtual void attack(Player* enemy) = 0;
        virtual void attackComputer(Player* enemy) = 0;
        virtual void defence() = 0;
        virtual void defenceComputer() = 0;
        void printTwoRowTable(std::string firstOption, std::string secondOption, std::string thirdOption, std::string fourthOption) const;

    protected:
        std::string PlayerName, Character;
        int HP, MP, Shield, level, XP, specialAbility;
        const int maxHealth;

    private:
        virtual int attackOne() = 0;
        virtual int attackTwo() = 0;
        virtual int attackThree() = 0;
        virtual int attackFour() = 0;
        virtual int attackSpecial() = 0;
        virtual void defenceOne() = 0;
        virtual void defenceTwo() = 0;
        virtual void defenceThree() = 0;
        virtual void defenceFour() = 0;
 };

#endif // PLAYER_H
