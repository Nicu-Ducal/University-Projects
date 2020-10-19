#include "PlayerFactory.h"

PlayerFactory::PlayerFactory(){}

PlayerFactory::~PlayerFactory() = default;

Player* PlayerFactory::createPlayer(std::string character, std::string PlayerName){
    if (character == "Naruto")
        return createNaruto(PlayerName);
    else if (character == "Sasuke")
        return createSasuke(PlayerName);
    else
        return nullptr;
}

Player* PlayerFactory::createNaruto(std::string PlayerName){
    return new Naruto(PlayerName);
}

Player* PlayerFactory::createSasuke(std::string PlayerName){
    return new Sasuke(PlayerName);
}
