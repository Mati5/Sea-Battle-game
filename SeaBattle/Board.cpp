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

	this->randomCraft(4, 1);
	this->randomCraft(3, 2);
	this->randomCraft(2, 3);
	this->randomCraft(1, 4);
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

void Board::setFieldTab(std::array<std::array<Field, 10>, 10> fieldTab)
{
	{
		this->fieldTab = fieldTab;
	}
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
			if (field.getType() != CraftType::zeroMasted && field.getType() != CraftType::forbid)
				field.setColor(sf::Color::Green);

			if (field.getType() == CraftType::forbid)
				field.setColor(sf::Color::Blue);

			if (turn && leftMouseBtnPressed) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
				sf::Vector2f worldPos = mWindow.mapPixelToCoords(mousePosition);

				float mouseX = worldPos.x;
				float mouseY = worldPos.y;

				if (field.onClick(mouseX, mouseY)) {
					this->setClickedField(field);
					this->updateTabEl(field);

					//check if craft is destroyed

				}
			}

			mWindow.draw(field.renderField());
		}
	}
}

void randomField()
{

}

void checkNSDirection(int rowIndex, int colIndex, int type, std::array<std::array<Field, 10>, 10> fieldTab, bool& allowCraft, int direction)
{
	for (int i = 1; i < type; i++)
	{
		if (rowIndex + (i * direction) > 9 || rowIndex + (i * direction) < 0)
		{
			allowCraft = false;
			break;
		}

		if (fieldTab[rowIndex + (i*direction)][colIndex].getType() != CraftType::zeroMasted)
		{
			allowCraft = false;
			break;
		}
	}
}

void checkVertical(int rowIndex, int colIndex, int type, std::array<std::array<Field, 10>, 10> fieldTab, bool& allowCraft, char& allowedDirection)
{
	allowCraft = true;
	allowedDirection = 'S';

	if (rowIndex + type - 1 <= 9)
	{
		allowCraft = true;
		checkNSDirection(rowIndex, colIndex, type, fieldTab, allowCraft, 1);
		
		if (!allowCraft)
		{
			allowCraft = true;
			allowedDirection = 'N';

			checkNSDirection(rowIndex, colIndex, type, fieldTab, allowCraft, -1);
		}
	}
	else if(rowIndex-type-1>=0)
	{
		allowCraft = true;
		allowedDirection = 'N';
		checkNSDirection(rowIndex, colIndex, type, fieldTab, allowCraft, -1);

		if (!allowCraft)
		{
			allowCraft = true;
			allowedDirection = 'S';

			checkNSDirection(rowIndex, colIndex, type, fieldTab, allowCraft, 1);
		}
	}
	else
	{
		std::cout << "WARNING VERTICAL CHECK" << std::endl;
	}
}

void checkWEDirection(int rowIndex, int colIndex, int type, std::array<std::array<Field, 10>, 10> fieldTab, bool& allowCraft, int direction)
{
	for (int i = 1; i < type; i++)
	{
		if (colIndex + (i * direction) < 0 || colIndex + (i * direction)>9)
		{
			allowCraft = false;
			break;
		}

		if (fieldTab[rowIndex][colIndex + (i*direction)].getType() != CraftType::zeroMasted)
		{
			allowCraft = false;
			break;
		}
	}
}

void checkHorizontal(int rowIndex, int colIndex, int type, std::array<std::array<Field, 10>, 10> fieldTab, bool& allowCraft, char& allowedDirection)
{
	allowCraft = true;
	allowedDirection = 'E';
	if (colIndex + type - 1 <= 9)
	{
		checkWEDirection(rowIndex, colIndex, type, fieldTab, allowCraft, 1);

		if (!allowCraft)
		{
			allowCraft = true;
			allowedDirection = 'W';

			checkWEDirection(rowIndex, colIndex, type, fieldTab, allowCraft, -1);
		}
	}
	else if (colIndex - type - 1 >= 0)
	{
		allowCraft = true;
		allowedDirection = 'W';

		checkWEDirection(rowIndex, colIndex, type, fieldTab, allowCraft, -1);
			
		if(!allowCraft)
		{
			allowCraft = true;
			allowedDirection = 'E';

			checkWEDirection(rowIndex, colIndex, type, fieldTab, allowCraft, 1);	
		}
	}
	else
	{
		std::cout << "WARNING HORIZONTAL CHECK" << std::endl;
	}
}

void randomEmptyField(int& rowIndex, int& colIndex, std::array<std::array<Field, 10>, 10> fieldTab)
{
	do
	{
		rowIndex = rand() % 10;
		colIndex = rand() % 10;
	} while (fieldTab[rowIndex][colIndex].getType() != CraftType::zeroMasted);
}

void Board::randomCraft(int type, int quantity)
{
	for (int i = 0; i < quantity; i++)
	{
		CraftType craft;

		switch (type)
		{
			case 1:
				craft = CraftType::oneMasted;
				break;
			case 2:
				craft = CraftType::twoMasted;
				break;
			case 3:
				craft = CraftType::threeMasted;
				break;
			case 4:
				craft = CraftType::fourMasted;
				break;
		}

		bool allowCraft = true;
		char allowedDirection = 'K';

		//rand direction (vertical(1)/horizontal(0))
		int direction = rand() % 2;

		//Rand row
		int rowIndex = rand() % 10;

		//rand cols
		int colIndex = rand() % 10;

		//Rand empty field
		randomEmptyField(rowIndex, colIndex, this->fieldTab);

		std::cout << std::endl << "Rand field" << rowIndex << ' ' << colIndex << std::endl;

		//Check if field is empty vertical
		if (direction == 1)
		{
			do {
				randomEmptyField(rowIndex, colIndex, this->fieldTab);
				checkVertical(rowIndex, colIndex, type, this->fieldTab, allowCraft, allowedDirection);
			} while (allowCraft != true);
		}
		else // check if field is empty horizontal
		{
			do {
				randomEmptyField(rowIndex, colIndex, this->fieldTab);
				checkHorizontal(rowIndex, colIndex, type, this->fieldTab, allowCraft, allowedDirection);
			} while (allowCraft != true);
		}
		
	
		
		//If checked set craft on map
		if (allowCraft && allowedDirection == 'S')
		{
			for (int i = 0; i < type; i++)
			{
				fieldTab[rowIndex + i][colIndex].setType(craft);

				if (colIndex < 9 && fieldTab[rowIndex + i][colIndex + 1].getType() == CraftType::zeroMasted)
					fieldTab[rowIndex + i][colIndex + 1].setType(CraftType::forbid);

				if (colIndex > 0 && fieldTab[rowIndex + i][colIndex - 1].getType() == CraftType::zeroMasted)
					fieldTab[rowIndex + i][colIndex - 1].setType(CraftType::forbid);
			}

			if (rowIndex>0&&fieldTab[rowIndex - 1][colIndex].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex - 1][colIndex].setType(CraftType::forbid);

			if (colIndex > 0 && rowIndex>0 && fieldTab[rowIndex - 1][colIndex - 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex - 1][colIndex - 1].setType(CraftType::forbid);

			if (colIndex<9&&rowIndex>0&&fieldTab[rowIndex - 1][colIndex + 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex - 1][colIndex + 1].setType(CraftType::forbid);

			if (rowIndex+type<=9 && fieldTab[rowIndex + type][colIndex].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex + type][colIndex].setType(CraftType::forbid);

			if (colIndex > 0 && rowIndex+type<=9 && fieldTab[rowIndex + type][colIndex - 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex + type][colIndex - 1].setType(CraftType::forbid);

			if (colIndex<9&& rowIndex+type<=9 && fieldTab[rowIndex + type][colIndex + 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex + type][colIndex + 1].setType(CraftType::forbid);
		}
		else if (allowCraft && allowedDirection == 'N')
		{
			for (int i = 0; i < type; i++)
			{
				fieldTab[rowIndex - i][colIndex].setType(craft);

				if (colIndex<9 && fieldTab[rowIndex - i][colIndex + 1].getType() == CraftType::zeroMasted)
					fieldTab[rowIndex - i][colIndex + 1].setType(CraftType::forbid);

				if (colIndex > 0 && fieldTab[rowIndex - i][colIndex - 1].getType() == CraftType::zeroMasted)
					fieldTab[rowIndex - i][colIndex - 1].setType(CraftType::forbid);
			}

			if (rowIndex < 9 && fieldTab[rowIndex + 1][colIndex].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex + 1][colIndex].setType(CraftType::forbid);

			if (colIndex > 0 && rowIndex < 9 && fieldTab[rowIndex + 1][colIndex - 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex + 1][colIndex - 1].setType(CraftType::forbid);

			if (rowIndex < 9 && colIndex<9 && fieldTab[rowIndex + 1][colIndex + 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex + 1][colIndex + 1].setType(CraftType::forbid);

			if (rowIndex-type>=0&&fieldTab[rowIndex - type][colIndex].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex - type][colIndex].setType(CraftType::forbid);

			if (colIndex > 0 && rowIndex-type>=0&& fieldTab[rowIndex - type][colIndex - 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex - type][colIndex - 1].setType(CraftType::forbid);

			if (rowIndex-type>=0 && colIndex<9 && fieldTab[rowIndex - type][colIndex + 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex - type][colIndex + 1].setType(CraftType::forbid);
		}
		else if (allowCraft && allowedDirection == 'E')
		{
			for (int i = 0; i < type; i++)
			{
				fieldTab[rowIndex][colIndex+i].setType(craft);

				if (rowIndex<9&&fieldTab[rowIndex+1][colIndex + i].getType() == CraftType::zeroMasted)
					fieldTab[rowIndex+1][colIndex + i].setType(CraftType::forbid);

				if (colIndex<9&&rowIndex>0&&fieldTab[rowIndex-1][colIndex + i].getType() == CraftType::zeroMasted)
					fieldTab[rowIndex - 1][colIndex +i].setType(CraftType::forbid);
			}

			if (colIndex>0 && fieldTab[rowIndex][colIndex-1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex][colIndex-1].setType(CraftType::forbid);

			if (colIndex > 0 && rowIndex>0 && fieldTab[rowIndex-1][colIndex - 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex-1][colIndex - 1].setType(CraftType::forbid);

			if (colIndex > 0 && rowIndex<9 && fieldTab[rowIndex+1][colIndex - 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex+1][colIndex - 1].setType(CraftType::forbid);

			if (colIndex+type <= 9 && fieldTab[rowIndex][colIndex + type].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex][colIndex + type].setType(CraftType::forbid);

			if (colIndex+type <= 9 && rowIndex>0 && fieldTab[rowIndex-1][colIndex + type].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex-1][colIndex + type].setType(CraftType::forbid);

			if (colIndex+type <= 9 && rowIndex<9 && fieldTab[rowIndex+1][colIndex + type].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex+1][colIndex + type].setType(CraftType::forbid);

		}
		else if (allowCraft && allowedDirection == 'W')
		{
			for (int i = 0; i < type; i++)
			{
				fieldTab[rowIndex][colIndex - i].setType(craft);

				if (rowIndex<9 && fieldTab[rowIndex + 1][colIndex - i].getType() == CraftType::zeroMasted)
					fieldTab[rowIndex + 1][colIndex - i].setType(CraftType::forbid);

				if (colIndex-i>=0 && rowIndex>0 && fieldTab[rowIndex - 1][colIndex - i].getType() == CraftType::zeroMasted)
					fieldTab[rowIndex - 1][colIndex - i].setType(CraftType::forbid);
			}

			if (colIndex < 9 && fieldTab[rowIndex][colIndex + 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex][colIndex + 1].setType(CraftType::forbid);

			if (colIndex < 9 && rowIndex>0 && fieldTab[rowIndex - 1][colIndex + 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex - 1][colIndex + 1].setType(CraftType::forbid);

			if (colIndex < 9 && rowIndex < 9 && fieldTab[rowIndex + 1][colIndex + 1].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex + 1][colIndex + 1].setType(CraftType::forbid);

			if (colIndex-type > 0 && fieldTab[rowIndex][colIndex - type].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex][colIndex - type].setType(CraftType::forbid);

			if (colIndex-type > 0 && rowIndex>0 && fieldTab[rowIndex - 1][colIndex - type].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex - 1][colIndex - type].setType(CraftType::forbid);

			if (colIndex-type > 0 && rowIndex<9 && fieldTab[rowIndex + 1][colIndex - type].getType() == CraftType::zeroMasted)
				fieldTab[rowIndex + 1][colIndex - type].setType(CraftType::forbid);
		}
	}
}
