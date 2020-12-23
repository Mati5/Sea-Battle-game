#include "Board.h"

Board::Board()
{
	this->dimensionX = 10;
	this->dimensionY = 10;

	for (int y = 0; y < this->getDimensionY(); y++) {
		for (int x = 0; x < this->getDimensionX(); x++) {
			Craft craft;
			Field field;
			
			field.setCoordinate(x, y);
			field.setColor(sf::Color::Cyan);
			craft.addField(field);
			this->fieldTab[y][x] = field;

			availableField.push_back({ y,x });
		}
	}

	this->leftMouseBtnPressed = false;
}

Board::~Board()
{
	craftTab.clear();
}

Board::Board(const Board& board)
{
	this->dimensionX = board.dimensionX;
	this->dimensionY = board.dimensionY;
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			this->fieldTab[y][x] = board.fieldTab[y][x];
			availableField.push_back({ y,x });
		}
	}
	for (int i = 0; i < board.craftTab.size(); i++)
	{
		this->craftTab.push_back(board.craftTab[i]);
	}
	this->clickedField = board.clickedField;
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

void Board::addCraft(Craft craft)
{
	this->craftTab.push_back(craft);
}

std::vector<Craft> Board::getCraftTab()
{
	return this->craftTab;
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

void Board::updateCraftTab(Craft craft, int index)
{
	this->craftTab[index] = craft;
}

void Board::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Mouse::Left)
	{
		leftMouseBtnPressed = isPressed;
	}
}



void Board::handleInput(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		handlePlayerInput(event.key.code, true);
		break;
	case sf::Event::MouseButtonReleased:
		handlePlayerInput(event.key.code, false);
		break;
	}
}

void Board::renderBoard(sf::RenderWindow& mWindow, bool turn, bool Ai)
{
	Field field2;
		
	if (Ai && turn)
	{
		if (hitCraftTab.size()==1)
		{
			field2 = hitCraftTab[0];

			//Tick 4 option (random 4 direction)
			std::vector<char> direction = {};
			int x = field2.getCoordinateX();
			int y = field2.getCoordinateY();

			//1 check which direction is available
			// all 4 direction
			if (x > 0 && x < 9 && y > 0 && y < 9)
			{
				if (!fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!fieldTab[y][x + 1].getChecked()) direction.push_back('E');
				if (!fieldTab[y + 1][x].getChecked()) direction.push_back('S');
				if (!fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}
			else if (x==0 && y==0)
			{
				if (!fieldTab[y][x + 1].getChecked()) direction.push_back('E');
				if (!fieldTab[y + 1][x].getChecked()) direction.push_back('S');
			}
			else if (x == 0 && y == 9)
			{
				if (!fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!fieldTab[y][x + 1].getChecked()) direction.push_back('E');
			}
			else if (x == 9 && y == 0)
			{
				if (!fieldTab[y + 1][x].getChecked()) direction.push_back('S');
				if (!fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}
			else if (x == 9 && y == 9)
			{
				if (!fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}
			else if (x == 0 && y > 0 && y < 9)
			{
				if (!fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!fieldTab[y][x + 1].getChecked()) direction.push_back('E');
				if (!fieldTab[y + 1][x].getChecked()) direction.push_back('S');
			}
			else if (x == 9 && y>0 && y<9)
			{
				if (!fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!fieldTab[y + 1][x].getChecked()) direction.push_back('S');
				if (!fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}
			else if (x > 0 && x < 9 && y == 0)
			{
				if (!fieldTab[y][x + 1].getChecked()) direction.push_back('E');
				if (!fieldTab[y + 1][x].getChecked()) direction.push_back('S');
				if (!fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}
			else if (x > 0 && x < 9 && y == 9)
			{
				if (!fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!fieldTab[y][x + 1].getChecked()) direction.push_back('E');
				if (!fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}

			if (direction.size() > 0)
			{
				int randDirectionNum = rand() % direction.size();
				char randDirection = direction[randDirectionNum];

				switch (randDirection)
				{
				case 'N':
					field2 = fieldTab[y - 1][x];
					break;
				case 'E':
					field2 = fieldTab[y][x + 1];
					break;
				case 'S':
					field2 = fieldTab[y + 1][x];
					break;
				case 'W':
					field2 = fieldTab[y][x - 1];;
					break;
				}
			}
			else {
				field2 = getAvailableField();
			}
		}
		else if (hitCraftTab.size() > 1)
		{
			int hitCraftIndex = getCraft(hitCraftTab[0]);
			std::string hitCraftDirection = craftTab[hitCraftIndex].getOrientation();

			if (hitCraftDirection == "vertical") //N/S
			{
				for (int i = 0; i < hitCraftTab.size(); i++)
				{
					int x = hitCraftTab[i].getCoordinateX();
					int y = hitCraftTab[i].getCoordinateY();

					if (y-1>=0 && !fieldTab[y - 1][x].getChecked()) {
						field2 = fieldTab[y - 1][x];
						break;
					}
					else if (y+1<=9 && !fieldTab[y + 1][x].getChecked())
					{
						field2 = fieldTab[y + 1][x];
						break;
					}
				}
			}
			else//E/W
			{
				for (int i = 0; i < hitCraftTab.size(); i++)
				{
					int x = hitCraftTab[i].getCoordinateX();
					int y = hitCraftTab[i].getCoordinateY();

					if (x-1>=0 && !fieldTab[y][x - 1].getChecked()) {
						field2 = fieldTab[y][x - 1];
						break;
					}
					else if (x+1<=9 && !fieldTab[y][x + 1].getChecked())
					{
						field2 = fieldTab[y][x + 1];
						break;
					}
				}
			}
		}
		else
		{
			field2 = getAvailableField();
		}	
		
		Sleep(1000);

		if (!field2.getChecked())
		{
			field2.setColor(sf::Color::White);
			field2.setChecked(true);
			
			if (field2.hitCraft()) {
				field2.setColor(sf::Color::Blue);

				//add to hitCraftTab to remeber which craft is partly destroyed
				hitCraftTab.push_back(field2);
			}

			this->setClickedField(field2);
			this->updateTabEl(field2);
			int checkedFieldIndex = getIndexAvailableField(field2.getCoordinateX(), field2.getCoordinateY());
			delAvailableField(checkedFieldIndex);

			checkCraftIsDestroyed(field2);
		}
		else
		{
			std::cout << "Not work Ai" << std::endl;
		}
	}

	for (int y = 0; y < this->getDimensionY(); y++)
	{
		for (int x = 0; x < getDimensionX(); x++)
		{
			Field field = this->getFieldTab()[y][x];

			//Display craft
			if (field.getType() != CraftType::zeroMasted && field.getType() != CraftType::forbid)
				field.setColor(sf::Color::Green);

			if(Ai && field.getChecked())
				field.setColor(sf::Color::Red);

			if (Ai && field.getChecked())
				field.setColor(sf::Color::Red);

			if(Ai&& field.getChecked() && field.getType() != CraftType::zeroMasted && field.getType() != CraftType::forbid)
				field.setColor(sf::Color::Blue);

			//Display forbid 
			/*if (field.getType() == CraftType::forbid)
				field.setColor(sf::Color::Blue);*/

			
			//Board player
			if (turn && !Ai && this->leftMouseBtnPressed) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
				sf::Vector2f worldPos = mWindow.mapPixelToCoords(mousePosition);

				float mouseX = worldPos.x;
				float mouseY = worldPos.y;

				if (field.onClick(mouseX, mouseY)) {
					
					this->setClickedField(field);
					this->updateTabEl(field);

					//check if craft is destroyed
					checkCraftIsDestroyed(field);
				}
			}

			mWindow.draw(field.renderField());
		}
	}
}

void randomField()
{

}

void Board::checkNSDirection(int rowIndex, int colIndex, int type, bool& allowCraft, int direction)
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

void Board::checkVertical(int rowIndex, int colIndex, int type, bool& allowCraft, char& allowedDirection)
{
	allowCraft = true;
	allowedDirection = 'S';

	if (rowIndex + type - 1 <= 9)
	{
		allowCraft = true;
		checkNSDirection(rowIndex, colIndex, type, allowCraft, 1);
		
		if (!allowCraft)
		{
			allowCraft = true;
			allowedDirection = 'N';

			checkNSDirection(rowIndex, colIndex, type, allowCraft, -1);
		}
	}
	else if(rowIndex-type-1>=0)
	{
		allowCraft = true;
		allowedDirection = 'N';
		checkNSDirection(rowIndex, colIndex, type, allowCraft, -1);

		if (!allowCraft)
		{
			allowCraft = true;
			allowedDirection = 'S';

			checkNSDirection(rowIndex, colIndex, type, allowCraft, 1);
		}
	}
	else
	{
		std::cout << "WARNING VERTICAL CHECK" << std::endl;
	}
}

void Board::checkWEDirection(int rowIndex, int colIndex, int type, bool& allowCraft, int direction)
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

void Board::checkHorizontal(int rowIndex, int colIndex, int type, bool& allowCraft, char& allowedDirection)
{
	allowCraft = true;
	allowedDirection = 'E';
	if (colIndex + type - 1 <= 9)
	{
		checkWEDirection(rowIndex, colIndex, type, allowCraft, 1);

		if (!allowCraft)
		{
			allowCraft = true;
			allowedDirection = 'W';

			checkWEDirection(rowIndex, colIndex, type, allowCraft, -1);
		}
	}
	else if (colIndex - type - 1 >= 0)
	{
		allowCraft = true;
		allowedDirection = 'W';

		checkWEDirection(rowIndex, colIndex, type, allowCraft, -1);
			
		if(!allowCraft)
		{
			allowCraft = true;
			allowedDirection = 'E';

			checkWEDirection(rowIndex, colIndex, type, allowCraft, 1);	
		}
	}
	else
	{
		std::cout << "WARNING HORIZONTAL CHECK" << std::endl;
	}
}

Field Board::getAvailableField()
{
	int availableFieldSize = availableField.size();
	int randField = rand() % availableFieldSize;
	int randX = availableField[randField][1];
	int randY = availableField[randField][0];
	
	return this->fieldTab[randY][randX];
}

void Board::delAvailableField(int index)
{
	availableField.erase(availableField.begin() + index);
}

void Board::delForbidAvailableField(std::vector<Field> forbidArea)
{
	for (int i = 0; i < forbidArea.size(); i++)
	{
		int coordinateX = forbidArea[i].getCoordinateX();
		int coordinateY = forbidArea[i].getCoordinateY();
		int index = getIndexAvailableField(coordinateX, coordinateY);
		
		if (index >= 0)
			delAvailableField(index);
	}
}

int Board::getIndexAvailableField(int coordinateX, int coordinateY)
{
	for (int i = 0; i < availableField.size(); i++)
	{
		if (availableField[i][0] == coordinateY && availableField[i][1] == coordinateX)
			return i;
	}

	return -1;
}

int Board::getCraft(Field field)
{
	int coordinateX = field.getCoordinateX();
	int coordinateY = field.getCoordinateY();
	CraftType craftType = field.getType();

	int start = 0;
	int stop = 0;

	switch (craftType)
	{
	case CraftType::fourMasted:
		start = 0;
		stop = 0;
		break;
	case CraftType::threeMasted:
		start = 1;
		stop = 2;
		break;
	case CraftType::twoMasted:
		start = 3;
		stop = 5;
		break;
	case CraftType::oneMasted:
		start = 6;
		stop = 9;
		break;
	}

	for (int i = start; i <= stop; i++)
	{
		for (int j = 0; j < craftTab[i].getArea().size(); j++)
		{
			if (craftTab[i].getArea()[j].getCoordinateX() == field.getCoordinateX() &&
				craftTab[i].getArea()[j].getCoordinateY() == field.getCoordinateY())
			{
				return i;
			}
		}
	}

	return -1;
}

int Board::getHitCraft(Field field)
{
	return 0;
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
		CraftType craftType;

		switch (type)
		{
			case 1:
				craftType = CraftType::oneMasted;
				break;
			case 2:
				craftType = CraftType::twoMasted;
				break;
			case 3:
				craftType = CraftType::threeMasted;
				break;
			case 4:
				craftType = CraftType::fourMasted;
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

		//std::cout << std::endl << "Rand field" << rowIndex << ' ' << colIndex << std::endl;

		//Check if field is empty vertical
		if (direction == 1)
		{
			do {
				randomEmptyField(rowIndex, colIndex, this->fieldTab);
				checkVertical(rowIndex, colIndex, type, allowCraft, allowedDirection);
			} while (allowCraft != true);
		}
		else // check if field is empty horizontal
		{
			do {
				randomEmptyField(rowIndex, colIndex, this->fieldTab);
				checkHorizontal(rowIndex, colIndex, type, allowCraft, allowedDirection);
			} while (allowCraft != true);
		}
		
		Craft craftModel;
		craftModel.setCraftType(craftType);
		craftModel.setOrientation(direction == 1 ? "vertical" : "horizontal");

		//If checked set craft on map
		if (allowCraft && allowedDirection == 'S')
		{
			//Top left
			if (colIndex > 0 && rowIndex > 0 && (fieldTab[rowIndex - 1][colIndex - 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex - 1][colIndex - 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex - 1][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex - 1][colIndex - 1]);
			}
				
			//Top center
			if (rowIndex > 0 && (fieldTab[rowIndex - 1][colIndex].getType() == CraftType::zeroMasted || fieldTab[rowIndex - 1][colIndex].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex - 1][colIndex].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex - 1][colIndex]);
			}	

			//TopRight
			if (colIndex < 9 && rowIndex>0 && (fieldTab[rowIndex - 1][colIndex + 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex - 1][colIndex + 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex - 1][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex - 1][colIndex + 1]);
			}	

			for (int i = 0; i < type; i++)
			{
				//left forbid field
				if (colIndex > 0 && (fieldTab[rowIndex + i][colIndex - 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex + i][colIndex - 1].getType() == CraftType::forbid))
				{
					fieldTab[rowIndex + i][colIndex - 1].setType(CraftType::forbid);
					craftModel.addForbidArea(fieldTab[rowIndex + i][colIndex - 1]);
				}					

				//set field's craft
				fieldTab[rowIndex + i][colIndex].setType(craftType);
				craftModel.addField(fieldTab[rowIndex + i][colIndex]);

				//right forbied field
				if (colIndex < 9 && (fieldTab[rowIndex + i][colIndex + 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex + i][colIndex + 1].getType() == CraftType::forbid))
				{
					fieldTab[rowIndex + i][colIndex + 1].setType(CraftType::forbid);
					craftModel.addForbidArea(fieldTab[rowIndex + i][colIndex + 1]);
				}	
			}

			//Bottom left
			if (colIndex > 0 && rowIndex + type <= 9 && (fieldTab[rowIndex + type][colIndex - 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex + type][colIndex - 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex + type][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex + type][colIndex - 1]);
			}

			//Bottom center
			if (rowIndex + type <= 9 && (fieldTab[rowIndex + type][colIndex].getType() == CraftType::zeroMasted || fieldTab[rowIndex + type][colIndex].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex + type][colIndex].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex + type][colIndex]);
			}
				
			//Bottom right
			if (colIndex < 9 && rowIndex + type <= 9 && (fieldTab[rowIndex + type][colIndex + 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex + type][colIndex + 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex + type][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex + type][colIndex + 1]);
			}	
		}
		else if (allowCraft && allowedDirection == 'N')
		{
			//Bottom left
			if (colIndex > 0 && rowIndex < 9 && (fieldTab[rowIndex + 1][colIndex - 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex + 1][colIndex - 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex + 1][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex + 1][colIndex - 1]);
			}
				
			//Bottom center
			if (rowIndex < 9 && (fieldTab[rowIndex + 1][colIndex].getType() == CraftType::zeroMasted || fieldTab[rowIndex + 1][colIndex].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex + 1][colIndex].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex + 1][colIndex]);
			}

			//Bottom right
			if (rowIndex < 9 && colIndex < 9 && (fieldTab[rowIndex + 1][colIndex + 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex + 1][colIndex + 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex + 1][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex + 1][colIndex + 1]);
			}	

			for (int i = 0; i < type; i++)
			{
				if (colIndex > 0 && (fieldTab[rowIndex - i][colIndex - 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex - i][colIndex - 1].getType() == CraftType::forbid))
				{
					fieldTab[rowIndex - i][colIndex - 1].setType(CraftType::forbid);
					craftModel.addForbidArea(fieldTab[rowIndex - i][colIndex - 1]);
				}	

				fieldTab[rowIndex - i][colIndex].setType(craftType);
				craftModel.addField(fieldTab[rowIndex - i][colIndex]);

				if (colIndex < 9 && (fieldTab[rowIndex - i][colIndex + 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex - i][colIndex + 1].getType() == CraftType::forbid))
				{
					fieldTab[rowIndex - i][colIndex + 1].setType(CraftType::forbid);
					craftModel.addForbidArea(fieldTab[rowIndex - i][colIndex + 1]);
				}		
			}

			//Top left
			if (colIndex > 0 && rowIndex - type >= 0 && (fieldTab[rowIndex - type][colIndex - 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex - type][colIndex - 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex - type][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex - type][colIndex - 1]);
			}

			//Top center
			if (rowIndex - type >= 0 && (fieldTab[rowIndex - type][colIndex].getType() == CraftType::zeroMasted || fieldTab[rowIndex - type][colIndex].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex - type][colIndex].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex - type][colIndex]);
			}

			//Top right
			if (rowIndex - type >= 0 && colIndex < 9 && (fieldTab[rowIndex - type][colIndex + 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex - type][colIndex + 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex - type][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex - type][colIndex + 1]);
			}	
		}
		else if (allowCraft && allowedDirection == 'E')
		{
			//top
			if (colIndex > 0 && rowIndex > 0 && (fieldTab[rowIndex - 1][colIndex - 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex - 1][colIndex - 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex - 1][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex - 1][colIndex - 1]);
			}
				
			//center
			if (colIndex > 0 && (fieldTab[rowIndex][colIndex - 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex][colIndex - 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex][colIndex - 1]);
			}

			//bottom
			if (colIndex > 0 && rowIndex < 9 && (fieldTab[rowIndex + 1][colIndex - 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex + 1][colIndex - 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex + 1][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex + 1][colIndex - 1]);
			}			

			for (int i = 0; i < type; i++)
			{
				//Top
				if (colIndex <= 9 && rowIndex>0 && (fieldTab[rowIndex - 1][colIndex + i].getType() == CraftType::zeroMasted || fieldTab[rowIndex - 1][colIndex + i].getType() == CraftType::forbid))
				{
					fieldTab[rowIndex - 1][colIndex + i].setType(CraftType::forbid);
					craftModel.addForbidArea(fieldTab[rowIndex - 1][colIndex + i]);
				}

				//Center
				fieldTab[rowIndex][colIndex+i].setType(craftType);
				craftModel.addField(fieldTab[rowIndex][colIndex + i]);

				//Bottom
				if (rowIndex < 9 && (fieldTab[rowIndex + 1][colIndex + i].getType() == CraftType::zeroMasted || fieldTab[rowIndex + 1][colIndex + i].getType() == CraftType::forbid))
				{
					fieldTab[rowIndex + 1][colIndex + i].setType(CraftType::forbid);
					craftModel.addForbidArea(fieldTab[rowIndex + 1][colIndex + i]);
				}	
			}
			
			//Top
			if (colIndex + type <= 9 && rowIndex > 0 && (fieldTab[rowIndex - 1][colIndex + type].getType() == CraftType::zeroMasted || fieldTab[rowIndex - 1][colIndex + type].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex - 1][colIndex + type].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex - 1][colIndex + type]);
			}

			//Center
			if (colIndex + type <= 9 && (fieldTab[rowIndex][colIndex + type].getType() == CraftType::zeroMasted || fieldTab[rowIndex][colIndex + type].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex][colIndex + type].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex][colIndex + type]);
			}

			//Bottom
			if (colIndex + type <= 9 && rowIndex < 9 && (fieldTab[rowIndex + 1][colIndex + type].getType() == CraftType::zeroMasted || fieldTab[rowIndex + 1][colIndex + type].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex + 1][colIndex + type].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex + 1][colIndex + type]);
			}
				

		}
		else if (allowCraft && allowedDirection == 'W')
		{
			//Top
			if (colIndex < 9 && rowIndex>0 && (fieldTab[rowIndex - 1][colIndex + 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex - 1][colIndex + 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex - 1][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex - 1][colIndex + 1]);
			}
				

			//Center
			if (colIndex < 9 && (fieldTab[rowIndex][colIndex + 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex][colIndex + 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex][colIndex + 1]);
			}	

			//Bottom
			if (colIndex < 9 && rowIndex < 9 && (fieldTab[rowIndex + 1][colIndex + 1].getType() == CraftType::zeroMasted || fieldTab[rowIndex + 1][colIndex + 1].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex + 1][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex + 1][colIndex + 1]);
			}

			for (int i = 0; i < type; i++)
			{
				if (colIndex - i >= 0 && rowIndex > 0 && (fieldTab[rowIndex - 1][colIndex - i].getType() == CraftType::zeroMasted || fieldTab[rowIndex - 1][colIndex - i].getType() == CraftType::forbid))
				{
					fieldTab[rowIndex - 1][colIndex - i].setType(CraftType::forbid);
					craftModel.addForbidArea(fieldTab[rowIndex - 1][colIndex - i]);
				}
	
				fieldTab[rowIndex][colIndex - i].setType(craftType);
				craftModel.addField(fieldTab[rowIndex][colIndex - i]);

				if (rowIndex < 9 && (fieldTab[rowIndex + 1][colIndex - i].getType() == CraftType::zeroMasted || fieldTab[rowIndex + 1][colIndex - i].getType() == CraftType::forbid))
				{
					fieldTab[rowIndex + 1][colIndex - i].setType(CraftType::forbid);
					craftModel.addForbidArea(fieldTab[rowIndex + 1][colIndex - i]);
				}	
			}

			//Top
			if (colIndex - type >= 0 && rowIndex > 0 && (fieldTab[rowIndex - 1][colIndex - type].getType() == CraftType::zeroMasted || fieldTab[rowIndex - 1][colIndex - type].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex - 1][colIndex - type].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex - 1][colIndex - type]);
			}

			//Center
			if (colIndex - type >= 0 && (fieldTab[rowIndex][colIndex - type].getType() == CraftType::zeroMasted || fieldTab[rowIndex][colIndex - type].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex][colIndex - type].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex][colIndex - type]);
			}

			//Bottom
			if (colIndex - type >= 0 && rowIndex < 9 && (fieldTab[rowIndex + 1][colIndex - type].getType() == CraftType::zeroMasted || fieldTab[rowIndex + 1][colIndex - type].getType() == CraftType::forbid))
			{
				fieldTab[rowIndex + 1][colIndex - type].setType(CraftType::forbid);
				craftModel.addForbidArea(fieldTab[rowIndex + 1][colIndex - type]);
			}	
		}
		if (allowCraft)
		{
			this->addCraft(craftModel);
		}
	}
}

void Board::checkCraftIsDestroyed(Field field)
{
	int craftIndex = getCraft(field);
	if (craftIndex >= 0)
	{
		craftTab[craftIndex].destroyEl();

		if (craftTab[craftIndex].checkStateCraft())
		{
			std::cout << "Destroyed threeMasted craft" << std::endl;

			//Tick field around craft
			this->tickForbidArea(craftTab[craftIndex]);

			//delete forbid element from available field
			delForbidAvailableField(craftTab[craftIndex].getForbidArea());

			//delete element from hitCraftTab
			hitCraftTab.clear();
		}
	}
}

void Board::tickForbidArea(Craft craft)
{
	for (int i = 0; i < craft.getForbidArea().size(); i++)
	{
		Field forbidField = craft.getForbidArea()[i];
		forbidField.setColor(sf::Color::Magenta);
		forbidField.setChecked(true);
		this->updateTabEl(forbidField);
	}
}
