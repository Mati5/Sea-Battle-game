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
protected:
	int m_dimensionX{10};
	int m_dimensionY{10};
	std::array<std::array<Field, 10>, 10> m_fieldTab;
	std::vector<Craft> m_craftTab;
	Field m_clickedField;
	int m_boardStats{0};
	sf::Texture m_fieldTexture;
	sf::Texture m_craftTexture;
	sf::Texture m_checkedTexture;
	sf::Texture m_hitCraftTexture;

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

	void renderBoard(sf::RenderWindow& mWindow, bool showCraft=false) const;

	void randomCraft(int type, int quantity);

	bool checkCraftIsDestroyed(const Field& field);

	void tickForbidArea(const Craft& craft);

	void checkNSDirection(int rowIndex, int colIndex, int type, bool& allowCraft, int direction);

	void checkVertical(int rowIndex, int colIndex, int type, bool& allowCraft, char& allowedDirection);

	void checkWEDirection(int rowIndex, int colIndex, int type, bool& allowCraft, int direction);

	void checkHorizontal(int rowIndex, int colIndex, int type, bool& allowCraft, char& allowedDirection);

	int getCraft(std::vector<Craft> craftTab, const Field& field);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, sf::RenderWindow& window);

	void handleInput(sf::RenderWindow& window, const sf::Event& event);

	int getBoardStats();
};
