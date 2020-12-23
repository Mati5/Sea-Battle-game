#pragma once
#include "Board.h"
#include "GameMode.h"


class GameSettings
{
	Board m_playerBoard_1;
	Board m_playerBoard_2;
	GameMode m_selectedGameMode{GameMode::OneVsAi};

public:
	void setPlayerBoard_1(const Board& playerBoard_1);

	Board getPlayerBoard_1() const;

	void setPlayerBoard_2(const Board& playerBoard_2);

	Board getPlayerBoard_2() const;

	GameMode getSelectedGameMode() const;
};

