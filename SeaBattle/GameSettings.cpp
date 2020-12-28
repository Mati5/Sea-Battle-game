#include "GameSettings.h"

void GameSettings::setPlayerBoard_1(const BoardPlayer& playerBoard_1)
{
    m_playerBoard_1 = playerBoard_1;
}

BoardPlayer GameSettings::getPlayerBoard_1() const
{
    return m_playerBoard_1;
}

void GameSettings::setPlayerBoard_2(const BoardPlayer& playerBoard_2)
{
    m_playerBoard_2 = playerBoard_2;
}

BoardPlayer GameSettings::getPlayerBoard_2() const
{
    return m_playerBoard_2;
}

void GameSettings::setBoardAi(const BoardAi& boardAi)
{
    m_boardAi = boardAi;
}

BoardAi GameSettings::getBoardAi() const
{
    return m_boardAi;
}

void GameSettings::setSelectedGameMode(GameMode gameMode)
{
    m_selectedGameMode = gameMode;
}

GameMode GameSettings::getSelectedGameMode() const
{
    return m_selectedGameMode;
}
