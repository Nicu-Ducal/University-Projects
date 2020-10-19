#ifndef SASUKE_H
#define SASUKE_H

#include "Player.h"


class Sasuke : public Player {
    public:
        Sasuke(std::string _PlayerName);
        virtual ~Sasuke();

        void attack(Player* enemy) override;
        void attackComputer(Player* enemy) override;
        void defence() override;
        void defenceComputer() override;

    private:
        std::vector<int> attackMana = {0, 15, 50, 75, 0};
        std::vector<int> defenceMana = {0, 20, 40, 70};
        int attackOne() override;
        int attackTwo() override;
        int attackThree() override;
        int attackFour() override;
        int attackSpecial() override;
        void defenceOne() override;
        void defenceTwo() override;
        void defenceThree() override;
        void defenceFour() override;
};

#endif // SASUKE_H
