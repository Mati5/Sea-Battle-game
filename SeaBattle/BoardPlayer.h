#pragma once
#include "Board.h"

class BoardPlayer: public Board
{

public:
	void tickField(Field& field);
};