#pragma once
#include "Board.h"
class GameSettings
{
	Board playerBoard_1;
	Board playerBoard_2;

public:
	void setPlayerBoard_1(const Board& playerBoard_1);

	Board getPlayerBoard_1();

	void setPlayerBoard_2(const Board& playerBoard_2);

	Board getPlayerBoard_2();
};

