#include "GameSettings.h"

void GameSettings::setPlayerBoard_1(const Board& playerBoard_1)
{
    this->playerBoard_1 = playerBoard_1;
}

Board GameSettings::getPlayerBoard_1()
{
    return playerBoard_1;
}

void GameSettings::setPlayerBoard_2(const Board& playerBoard_2)
{
    this->playerBoard_2 = playerBoard_2;
}

Board GameSettings::getPlayerBoard_2()
{
    return playerBoard_2;
}

GameMode GameSettings::getSelectedGameMode()
{
    return this->selectedGameMode;
}
