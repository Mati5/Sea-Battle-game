#pragma once
#include <array>
#include "Field.h"
#include <iostream>
#include "CraftType.h"

class Board
{
	int dimensionX;
	int dimensionY;
	std::array<std::array<Field, 10>, 10> fieldTab;
	Field clickedField;

public:
	Board();
	
	void setDimensionX(int dimensionX);

	int getDimensionX();

	void setDimensionY(int dimensionY);

	int getDimensionY();

	std::array<std::array<Field, 10>, 10> getFieldTab();

	void setClickedField(Field clickedField);

	Field getClickedField();

	void updateTabEl(Field field);

	void renderBoard(sf::RenderWindow& mWindow, bool leftMouseBtnPressed, bool turn);

	void randomCraft();
};
