#pragma once
#include <iostream>
#include <array>
#include "Field.h"
#include "Craft.h"
#include "Direction.h"
#include "RandNum.h"
#include "Settings.h"
#include "SetCraftTab.h"

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
	bool m_leftMouseBtnPressed;

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

	void updateCraftTab(int index, const Craft& craft);

	void setClickedField(const Field& clickedField);

	Field getClickedField() const;

	void updateTabEl(const Field& field);

	void renderBoard(sf::RenderWindow& mWindow, bool showCraft=false, bool showForbidArea=false) const;

	void randomCraft(int type, int quantity=1);

	bool checkCraftIsDestroyed(const Field& field);

	void tickForbidArea(const Craft& craft);

	void checkNSDirection(int rowIndex, int colIndex, int type, bool& allowCraft, int direction);

	void checkVertical(int rowIndex, int colIndex, int type, bool& allowCraft, Direction& allowedDirection);

	void checkWEDirection(int rowIndex, int colIndex, int type, bool& allowCraft, int direction);

	void checkHorizontal(int rowIndex, int colIndex, int type, bool& allowCraft, Direction& allowedDirection);

	void setCraftOnMap(const Direction& allowedDirection, Craft& craftModel, int craftIndex);
	
	int getCraft(std::vector<Craft> craftTab, const Field& field) const;

	void handleInput(const sf::RenderWindow& window);

	int getBoardStats() const;

	void delCraft(int craftIndex);

	void delCraftFromArray(int craftIndex);

	void setCraftTab(const sf::Texture& fiveMTexture, const sf::Texture& fourMTexture, const sf::Texture& threeMTexture, const sf::Texture& twoMTexture, const sf::Texture& oneMTexture);

	void clearCraftTab();

	void sortCraftTab();
};