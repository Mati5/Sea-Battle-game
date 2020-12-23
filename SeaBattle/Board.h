#pragma once
#include <array>
#include "Field.h"
#include <iostream>
#include "CraftType.h"
#include "Button.h"
#include "Craft.h"
#include<windows.h>

class Board
{
	int dimensionX;
	int dimensionY;
	std::array<std::array<Field, 10>, 10> fieldTab;
	std::vector<Craft> craftTab;
	std::vector<std::vector<int>> availableField{};
	std::vector<Field> hitCraftTab;
	Field clickedField;
	bool leftMouseBtnPressed{false};

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

	std::array<std::array<Field, 10>, 10> getFieldTab();

	void addCraft(Craft craft);

	std::vector<Craft> getCraftTab();

	void setClickedField(Field clickedField);

	Field getClickedField();

	void updateTabEl(Field field);

	void updateCraftTab(Craft craft, int index);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void handleInput(sf::Event event);

	void renderBoard(sf::RenderWindow& mWindow, bool turn, bool Ai=false);

	void randomCraft(int type, int quantity);

	void checkCraftIsDestroyed(Field field);

	void tickForbidArea(Craft craft);

	void checkNSDirection(int rowIndex, int colIndex, int type, bool& allowCraft, int direction);

	void checkVertical(int rowIndex, int colIndex, int type, bool& allowCraft, char& allowedDirection);

	void checkWEDirection(int rowIndex, int colIndex, int type, bool& allowCraft, int direction);

	void checkHorizontal(int rowIndex, int colIndex, int type, bool& allowCraft, char& allowedDirection);

	Field getAvailableField();

	void delAvailableField(int index);

	void delForbidAvailableField(std::vector<Field> forbidArea);

	int getIndexAvailableField(int coordinateX, int coordinateY);

	int getCraft(Field field);

	void addHitCraft(Field field);

	int getHitCraft(Field field);
};
