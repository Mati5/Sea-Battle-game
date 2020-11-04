#include "Board.h"

Board::Board()
{
	this->dimensionX = 10;
	this->dimensionY = 10;

	for (int y = 0; y < this->getDimensionY(); y++) {
		for (int x = 0; x < this->getDimensionX(); x++) {
			Field field;
			field.setCoordinate(x, y);
			field.setColor(sf::Color::Cyan);

			this->fieldTab[y][x] = field;
		}
	}
}

void Board::setDimensionX(int dimensionX)
{
	this->dimensionX = dimensionX;
}

int Board::getDimensionX()
{
	return this->dimensionX;
}

void Board::setDimensionY(int dimensionY)
{
	this->dimensionY = dimensionY;
}

int Board::getDimensionY()
{
	return this->dimensionY;
}

std::array<std::array<Field, 10>, 10> Board::getFieldTab()
{
	return this->fieldTab;
}

void Board::setClickedField(Field clickedField)
{
	this->clickedField = clickedField;
}

Field Board::getClickedField()
{
	return this->clickedField;
}

void Board::updateTabEl(Field field)
{
	int tabY = field.getCoordinate()[1] / field.getSpaceBetweenField();
	int tabX = field.getCoordinate()[0] / field.getSpaceBetweenField();

	this->fieldTab[tabY][tabX] = field;
}

void Board::renderBoard(sf::RenderWindow& mWindow, bool leftMouseBtnPressed, bool turn)
{
	for (int y = 0; y < this->getDimensionY(); y++)
	{
		for (int x = 0; x < getDimensionX(); x++)
		{
			Field field = this->getFieldTab()[y][x];

			if (turn && leftMouseBtnPressed) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
				sf::Vector2f worldPos = mWindow.mapPixelToCoords(mousePosition);

				float mouseX = worldPos.x;
				float mouseY = worldPos.y;

				if (field.onClick(mouseX, mouseY)) {
					this->setClickedField(field);
					this->updateTabEl(field);
				}
			}

			mWindow.draw(field.renderField());
		}
	}

	this->randomCraft();
}

void Board::randomCraft()
{
	CraftType craft = CraftType::fourMasted;

	this->fieldTab[0][0].setType(craft);
	this->fieldTab[0][1].setType(craft);
	this->fieldTab[0][2].setType(craft);
	this->fieldTab[0][3].setType(craft);
}
