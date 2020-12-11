#pragma once
#include <array>
#include "Field.h"
#include <iostream>
#include "CraftType.h"
#include "Button.h"
#include "Craft.h"

class Board
{
	int dimensionX;
	int dimensionY;
	std::array<std::array<Field, 10>, 10> fieldTab;
	std::vector<Craft> craftTab;
	Field clickedField;

public:
	Board();

	~Board();

	Board(const Board& board);

	void resetBoard()
	{
		this->dimensionX = 10;
		this->dimensionY = 10;
		this->craftTab.clear();

		for (int y = 0; y < this->getDimensionY(); y++) {
			for (int x = 0; x < this->getDimensionX(); x++) {
				Field field;
				field.setCoordinate(x, y);
				field.setColor(sf::Color::Cyan);

				this->fieldTab[y][x] = field;
			}
		}
	}
	
	void setDimensionX(int dimensionX);

	int getDimensionX();

	void setDimensionY(int dimensionY);

	int getDimensionY();

	void setFieldTab(std::array<std::array<Field, 10>, 10> fieldTab);

	std::array<std::array<Field, 10>, 10> getFieldTab();

	void addCraft(Craft craft);

	std::vector<Craft> getCraftTab();

	void setClickedField(Field clickedField);

	Field getClickedField();

	void updateTabEl(Field field);

	void updateCraftTab(Craft craft, int index);

	void renderBoard(sf::RenderWindow& mWindow, bool leftMouseBtnPressed, bool turn);

	void randomCraft(int type, int quantity);

	void tickForbidArea(Craft craft);
};
