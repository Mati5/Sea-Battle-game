#pragma once
#include "Board.h"
#include "BoardPlayer.h"
#include "BoardAi.h"
#include "GameMode.h"


class GameSettings
{
	BoardPlayer m_playerBoard_1;
	BoardPlayer m_playerBoard_2;
	BoardAi m_boardAi;
	GameMode m_selectedGameMode{GameMode::OneVsAi};

public:
	void setPlayerBoard_1(const BoardPlayer& playerBoard_1);

	BoardPlayer getPlayerBoard_1() const;

	void setPlayerBoard_2(const BoardPlayer& playerBoard_2);

	BoardPlayer getPlayerBoard_2() const;

	void setBoardAi(const BoardAi& boardAi);

	BoardAi getBoardAi() const;

	GameMode getSelectedGameMode() const;
};

