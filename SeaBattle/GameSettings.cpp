#include "GameSettings.h"

void GameSettings::setPlayerBoard_1(const Board& playerBoard_1)
{
    m_playerBoard_1 = playerBoard_1;
}

Board GameSettings::getPlayerBoard_1() const
{
    return m_playerBoard_1;
}

void GameSettings::setPlayerBoard_2(const Board& playerBoard_2)
{
    m_playerBoard_2 = playerBoard_2;
}

Board GameSettings::getPlayerBoard_2() const
{
    return m_playerBoard_2;
}

GameMode GameSettings::getSelectedGameMode() const
{
    return m_selectedGameMode;
}
