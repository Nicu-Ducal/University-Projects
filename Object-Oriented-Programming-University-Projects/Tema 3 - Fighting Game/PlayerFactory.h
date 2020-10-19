#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include <string>
#include "Player.h"
#include "Naruto.h"
#include "Sasuke.h"

class PlayerFactory{
    public:
        PlayerFactory();
        virtual ~PlayerFactory();

        Player* createPlayer(std::string character, std::string PlayerName);

    private:
        Player* createNaruto(std::string PlayerName);
        Player* createSasuke(std::string PlayerName);
};


#endif // PLAYERFACTORY_H
