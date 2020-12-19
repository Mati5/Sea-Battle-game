#pragma once
#include "Board.h"
#include "GameMode.h"


class GameSettings
{
	Board playerBoard_1;
	Board playerBoard_2;
	GameMode selectedGameMode{GameMode::OneVsAi};

public:
	void setPlayerBoard_1(const Board& playerBoard_1);

	Board getPlayerBoard_1();

	void setPlayerBoard_2(const Board& playerBoard_2);

	Board getPlayerBoard_2();

	GameMode getSelectedGameMode();
};

