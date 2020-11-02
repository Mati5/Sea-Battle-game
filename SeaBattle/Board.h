#pragma once
#include <array>
#include "Field.h"
#include <iostream>

class Board
{
	int dimensionX;
	int dimensionY;
	std::array<std::array<Field, 10>, 10> fieldTab;

public:
	Board();
	
	void setDimensionX(int dimensionX);

	int getDimensionX();

	void setDimensionY(int dimensionY);

	int getDimensionY();

	std::array<std::array<Field, 10>, 10> getFieldTab();

	void updateTabEl(Field field);

	void renderBoard(sf::RenderWindow& mWindow, bool leftMouseBtnPressed);
};
