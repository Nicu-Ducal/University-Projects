#ifndef NARUTO_H
#define NARUTO_H

#include "Player.h"


class Naruto : public Player {
    public:
        Naruto(std::string _PlayerName);
        virtual ~Naruto();

        void attack(Player* enemy) override;
        void attackComputer(Player* enemy) override;
        void defence() override;
        void defenceComputer() override;

    private:
        std::vector<int> attackMana = {0, 20, 60, 80, 0};
        std::vector<int> defenceMana = {0, 15, 40, 60};
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

#endif // NARUTO_H
