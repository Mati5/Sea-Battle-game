#pragma once
#include "Board.h"
#include<Windows.h>

class BoardPlayer: public Board
{
	bool m_leftMouseBtnPressed{ false };
public:
	void tickField(Field field);
};