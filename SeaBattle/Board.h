#pragma once
#include <array>
#include "Field.h"
#include <iostream>
#include "CraftType.h"
#include "Button.h"
#include "Craft.h"
#include<Windows.h>

class Board
{
	int m_dimensionX{10};
	int m_dimensionY{10};
	std::array<std::array<Field, 10>, 10> m_fieldTab;
	std::vector<Craft> m_craftTab;
	std::vector<std::vector<int>> m_availableField{};
	std::vector<Field> m_hitCraftTab;
	Field m_clickedField;
	bool m_leftMouseBtnPressed{false};

public:
	Board();

	~Board();

	void resetBoard()
	{
		m_dimensionX = 10;
		m_dimensionY = 10;
		m_craftTab.clear();

		for (int y = 0; y < this->getDimensionY(); y++) {
			for (int x = 0; x < this->getDimensionX(); x++) {
				Field field;
				field.setCoordinate(x, y);
				field.setColor(sf::Color::Cyan);

				m_fieldTab[y][x] = field;
			}
		}
	}
	
	void setDimensionX(int dimensionX);

	int getDimensionX() const;

	void setDimensionY(int dimensionY);

	int getDimensionY() const;

	std::array<std::array<Field, 10>, 10> getFieldTab() const;

	void addCraft(const Craft& craft);

	std::vector<Craft> getCraftTab() const;

	void setClickedField(const Field& clickedField);

	Field getClickedField() const;

	void updateTabEl(const Field& field);

	void updateCraftTab(const Craft& craft, int index);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void handleInput(const sf::Event& event);

	void renderBoard(sf::RenderWindow& mWindow, bool turn, bool Ai=false);

	void randomCraft(int type, int quantity);

	void checkCraftIsDestroyed(const Field& field);

	void tickForbidArea(const Craft& craft);

	void checkNSDirection(int rowIndex, int colIndex, int type, bool& allowCraft, int direction);

	void checkVertical(int rowIndex, int colIndex, int type, bool& allowCraft, char& allowedDirection);

	void checkWEDirection(int rowIndex, int colIndex, int type, bool& allowCraft, int direction);

	void checkHorizontal(int rowIndex, int colIndex, int type, bool& allowCraft, char& allowedDirection);

	Field getAvailableField();

	void delAvailableField(int index);

	void delForbidAvailableField(std::vector<Field> forbidArea);

	int getIndexAvailableField(int coordinateX, int coordinateY);

	int getCraft(const Field& field);
};
