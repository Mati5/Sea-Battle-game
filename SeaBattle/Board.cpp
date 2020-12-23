#include "Board.h"

Board::Board()
{
	for (int y = 0; y < getDimensionY(); y++) {
		for (int x = 0; x < getDimensionX(); x++) {
			Craft craft;
			Field field;
			
			field.setCoordinate(x, y);
			field.setColor(sf::Color::Cyan);
			craft.addField(field);
			m_fieldTab[y][x] = field;

			m_availableField.push_back({ y,x });
		}
	}

	m_leftMouseBtnPressed = false;
}

Board::~Board()
{
	m_craftTab.clear();
}

void Board::setDimensionX(int dimensionX)
{
	m_dimensionX = dimensionX;
}

int Board::getDimensionX() const
{
	return m_dimensionX;
}

void Board::setDimensionY(int dimensionY)
{
	m_dimensionY = dimensionY;
}

int Board::getDimensionY() const
{
	return m_dimensionY;
}

std::array<std::array<Field, 10>, 10> Board::getFieldTab() const
{
	return m_fieldTab;
}

void Board::addCraft(const Craft& craft)
{
	m_craftTab.push_back(craft);
}

std::vector<Craft> Board::getCraftTab() const
{
	return m_craftTab;
}

void Board::setClickedField(const Field& clickedField)
{
	m_clickedField = clickedField;
}

Field Board::getClickedField() const
{
	return m_clickedField;
}

void Board::updateTabEl(const Field& field)
{
	int tabY = field.getCoordinate()[1] / field.getSpaceBetweenField();
	int tabX = field.getCoordinate()[0] / field.getSpaceBetweenField();

	m_fieldTab[tabY][tabX] = field;
}

void Board::updateCraftTab(const Craft& craft, int index)
{
	m_craftTab[index] = craft;
}

void Board::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Mouse::Left)
	{
		m_leftMouseBtnPressed = isPressed;
	}
}

void Board::handleInput(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		handlePlayerInput(event.key.code, true);
		break;
	case sf::Event::MouseButtonReleased:
		handlePlayerInput(event.key.code, false);
		break;
	default:
		break;
	}
}

void Board::renderBoard(sf::RenderWindow& mWindow, bool turn, bool Ai)
{
	Field field2;
		
	if (Ai && turn)
	{
		if (m_hitCraftTab.size()==1)
		{
			field2 = m_hitCraftTab[0];

			//Tick 4 option (random 4 direction)
			std::vector<char> direction = {};
			int x = field2.getCoordinateX();
			int y = field2.getCoordinateY();

			//1 check which direction is available
			// all 4 direction
			if (x > 0 && x < 9 && y > 0 && y < 9)
			{
				if (!m_fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!m_fieldTab[y][x + 1].getChecked()) direction.push_back('E');
				if (!m_fieldTab[y + 1][x].getChecked()) direction.push_back('S');
				if (!m_fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}
			else if (x==0 && y==0)
			{
				if (!m_fieldTab[y][x + 1].getChecked()) direction.push_back('E');
				if (!m_fieldTab[y + 1][x].getChecked()) direction.push_back('S');
			}
			else if (x == 0 && y == 9)
			{
				if (!m_fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!m_fieldTab[y][x + 1].getChecked()) direction.push_back('E');
			}
			else if (x == 9 && y == 0)
			{
				if (!m_fieldTab[y + 1][x].getChecked()) direction.push_back('S');
				if (!m_fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}
			else if (x == 9 && y == 9)
			{
				if (!m_fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!m_fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}
			else if (x == 0 && y > 0 && y < 9)
			{
				if (!m_fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!m_fieldTab[y][x + 1].getChecked()) direction.push_back('E');
				if (!m_fieldTab[y + 1][x].getChecked()) direction.push_back('S');
			}
			else if (x == 9 && y>0 && y<9)
			{
				if (!m_fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!m_fieldTab[y + 1][x].getChecked()) direction.push_back('S');
				if (!m_fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}
			else if (x > 0 && x < 9 && y == 0)
			{
				if (!m_fieldTab[y][x + 1].getChecked()) direction.push_back('E');
				if (!m_fieldTab[y + 1][x].getChecked()) direction.push_back('S');
				if (!m_fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}
			else if (x > 0 && x < 9 && y == 9)
			{
				if (!m_fieldTab[y - 1][x].getChecked()) direction.push_back('N');
				if (!m_fieldTab[y][x + 1].getChecked()) direction.push_back('E');
				if (!m_fieldTab[y][x - 1].getChecked()) direction.push_back('W');
			}

			if (!direction.empty())
			{
				int randDirectionNum = rand() % direction.size();
				char randDirection = direction[randDirectionNum];

				switch (randDirection)
				{
				case 'N':
					field2 = m_fieldTab[y - 1][x];
					break;
				case 'E':
					field2 = m_fieldTab[y][x + 1];
					break;
				case 'S':
					field2 = m_fieldTab[y + 1][x];
					break;
				case 'W':
					field2 = m_fieldTab[y][x - 1];;
					break;
				default:
					break;
				}
			}
			else {
				field2 = getAvailableField();
			}
		}
		else if (m_hitCraftTab.size() > 1)
		{
			int hitCraftIndex = getCraft(m_hitCraftTab[0]);
			std::string hitCraftDirection = m_craftTab[hitCraftIndex].getOrientation();

			if (hitCraftDirection == "vertical") //N/S
			{
				for (auto&& value : m_hitCraftTab)
				{
					int x = value.getCoordinateX();
					int y = value.getCoordinateY();

					if (y-1>=0 && !m_fieldTab[y - 1][x].getChecked()) {
						field2 = m_fieldTab[y - 1][x];
						break;
					}
					else if (y+1<=9 && !m_fieldTab[y + 1][x].getChecked())
					{
						field2 = m_fieldTab[y + 1][x];
						break;
					}
				}
			}
			else//E/W
			{
				for (auto&& value : m_hitCraftTab)
				{
					int x = value.getCoordinateX();
					int y = value.getCoordinateY();

					if (x-1>=0 && !m_fieldTab[y][x - 1].getChecked()) {
						field2 = m_fieldTab[y][x - 1];
						break;
					}
					else if (x+1<=9 && !m_fieldTab[y][x + 1].getChecked())
					{
						field2 = m_fieldTab[y][x + 1];
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
				m_hitCraftTab.push_back(field2);
			}

			setClickedField(field2);
			updateTabEl(field2);
			int checkedFieldIndex = getIndexAvailableField(field2.getCoordinateX(), field2.getCoordinateY());
			delAvailableField(checkedFieldIndex);

			checkCraftIsDestroyed(field2);
		}
		else
		{
			std::cout << "Not work Ai" << std::endl;
		}
	}

	for (int y = 0; y < getDimensionY(); y++)
	{
		for (int x = 0; x < getDimensionX(); x++)
		{
			Field field = getFieldTab()[y][x];

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
			if (turn && !Ai && m_leftMouseBtnPressed) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
				sf::Vector2f worldPos = mWindow.mapPixelToCoords(mousePosition);

				float mouseX = worldPos.x;
				float mouseY = worldPos.y;

				if (field.onClick(mouseX, mouseY)) {
					
					setClickedField(field);
					updateTabEl(field);

					//check if craft is destroyed
					checkCraftIsDestroyed(field);
				}
			}

			mWindow.draw(field.renderField());
		}
	}
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

		if (m_fieldTab[rowIndex + (i*direction)][colIndex].getType() != CraftType::zeroMasted)
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

		if (m_fieldTab[rowIndex][colIndex + (i*direction)].getType() != CraftType::zeroMasted)
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
	int availableFieldSize = m_availableField.size();
	int randField = rand() % availableFieldSize;
	int randX = m_availableField[randField][1];
	int randY = m_availableField[randField][0];
	
	return m_fieldTab[randY][randX];
}

void Board::delAvailableField(int index)
{
	m_availableField.erase(m_availableField.begin() + index);
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
	for (int i = 0; i < m_availableField.size(); i++)
	{
		if (m_availableField[i][0] == coordinateY && m_availableField[i][1] == coordinateX)
			return i;
	}

	return -1;
}

int Board::getCraft(const Field& field)
{
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
	default:
		break;
	}

	for (int i = start; i <= stop; i++)
	{
		for (int j = 0; j < m_craftTab[i].getArea().size(); j++)
		{
			if (m_craftTab[i].getArea()[j].getCoordinateX() == field.getCoordinateX() &&
				m_craftTab[i].getArea()[j].getCoordinateY() == field.getCoordinateY())
			{
				return i;
			}
		}
	}

	return -1;
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
			default:
				craftType = CraftType::zeroMasted;
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
		randomEmptyField(rowIndex, colIndex, m_fieldTab);

		//std::cout << std::endl << "Rand field" << rowIndex << ' ' << colIndex << std::endl;

		//Check if field is empty vertical
		if (direction == 1)
		{
			do {
				randomEmptyField(rowIndex, colIndex, m_fieldTab);
				checkVertical(rowIndex, colIndex, type, allowCraft, allowedDirection);
			} while (allowCraft != true);
		}
		else // check if field is empty horizontal
		{
			do {
				randomEmptyField(rowIndex, colIndex, m_fieldTab);
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
			if (colIndex > 0 && rowIndex > 0 && (m_fieldTab[rowIndex - 1][colIndex - 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex - 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - 1][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex - 1]);
			}
				
			//Top center
			if (rowIndex > 0 && (m_fieldTab[rowIndex - 1][colIndex].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - 1][colIndex].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex]);
			}	

			//TopRight
			if (colIndex < 9 && rowIndex>0 && (m_fieldTab[rowIndex - 1][colIndex + 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex + 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - 1][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex + 1]);
			}	

			for (int i = 0; i < type; i++)
			{
				//left forbid field
				if (colIndex > 0 && (m_fieldTab[rowIndex + i][colIndex - 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + i][colIndex - 1].getType() == CraftType::forbid))
				{
					m_fieldTab[rowIndex + i][colIndex - 1].setType(CraftType::forbid);
					craftModel.addForbidArea(m_fieldTab[rowIndex + i][colIndex - 1]);
				}					

				//set field's craft
				m_fieldTab[rowIndex + i][colIndex].setType(craftType);
				craftModel.addField(m_fieldTab[rowIndex + i][colIndex]);

				//right forbied field
				if (colIndex < 9 && (m_fieldTab[rowIndex + i][colIndex + 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + i][colIndex + 1].getType() == CraftType::forbid))
				{
					m_fieldTab[rowIndex + i][colIndex + 1].setType(CraftType::forbid);
					craftModel.addForbidArea(m_fieldTab[rowIndex + i][colIndex + 1]);
				}	
			}

			//Bottom left
			if (colIndex > 0 && rowIndex + type <= 9 && (m_fieldTab[rowIndex + type][colIndex - 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + type][colIndex - 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex + type][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex + type][colIndex - 1]);
			}

			//Bottom center
			if (rowIndex + type <= 9 && (m_fieldTab[rowIndex + type][colIndex].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + type][colIndex].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex + type][colIndex].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex + type][colIndex]);
			}
				
			//Bottom right
			if (colIndex < 9 && rowIndex + type <= 9 && (m_fieldTab[rowIndex + type][colIndex + 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + type][colIndex + 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex + type][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex + type][colIndex + 1]);
			}	
		}
		else if (allowCraft && allowedDirection == 'N')
		{
			//Bottom left
			if (colIndex > 0 && rowIndex < 9 && (m_fieldTab[rowIndex + 1][colIndex - 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + 1][colIndex - 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex + 1][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex + 1][colIndex - 1]);
			}
				
			//Bottom center
			if (rowIndex < 9 && (m_fieldTab[rowIndex + 1][colIndex].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + 1][colIndex].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex + 1][colIndex].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex + 1][colIndex]);
			}

			//Bottom right
			if (rowIndex < 9 && colIndex < 9 && (m_fieldTab[rowIndex + 1][colIndex + 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + 1][colIndex + 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex + 1][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex + 1][colIndex + 1]);
			}	

			for (int i = 0; i < type; i++)
			{
				if (colIndex > 0 && (m_fieldTab[rowIndex - i][colIndex - 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - i][colIndex - 1].getType() == CraftType::forbid))
				{
					m_fieldTab[rowIndex - i][colIndex - 1].setType(CraftType::forbid);
					craftModel.addForbidArea(m_fieldTab[rowIndex - i][colIndex - 1]);
				}	

				m_fieldTab[rowIndex - i][colIndex].setType(craftType);
				craftModel.addField(m_fieldTab[rowIndex - i][colIndex]);

				if (colIndex < 9 && (m_fieldTab[rowIndex - i][colIndex + 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - i][colIndex + 1].getType() == CraftType::forbid))
				{
					m_fieldTab[rowIndex - i][colIndex + 1].setType(CraftType::forbid);
					craftModel.addForbidArea(m_fieldTab[rowIndex - i][colIndex + 1]);
				}		
			}

			//Top left
			if (colIndex > 0 && rowIndex - type >= 0 && (m_fieldTab[rowIndex - type][colIndex - 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - type][colIndex - 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - type][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - type][colIndex - 1]);
			}

			//Top center
			if (rowIndex - type >= 0 && (m_fieldTab[rowIndex - type][colIndex].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - type][colIndex].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - type][colIndex].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - type][colIndex]);
			}

			//Top right
			if (rowIndex - type >= 0 && colIndex < 9 && (m_fieldTab[rowIndex - type][colIndex + 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - type][colIndex + 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - type][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - type][colIndex + 1]);
			}	
		}
		else if (allowCraft && allowedDirection == 'E')
		{
			//top
			if (colIndex > 0 && rowIndex > 0 && (m_fieldTab[rowIndex - 1][colIndex - 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex - 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - 1][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex - 1]);
			}
				
			//center
			if (colIndex > 0 && (m_fieldTab[rowIndex][colIndex - 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex][colIndex - 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex][colIndex - 1]);
			}

			//bottom
			if (colIndex > 0 && rowIndex < 9 && (m_fieldTab[rowIndex + 1][colIndex - 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + 1][colIndex - 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex + 1][colIndex - 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex + 1][colIndex - 1]);
			}			

			for (int i = 0; i < type; i++)
			{
				//Top
				if (colIndex <= 9 && rowIndex>0 && (m_fieldTab[rowIndex - 1][colIndex + i].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex + i].getType() == CraftType::forbid))
				{
					m_fieldTab[rowIndex - 1][colIndex + i].setType(CraftType::forbid);
					craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex + i]);
				}

				//Center
				m_fieldTab[rowIndex][colIndex+i].setType(craftType);
				craftModel.addField(m_fieldTab[rowIndex][colIndex + i]);

				//Bottom
				if (rowIndex < 9 && (m_fieldTab[rowIndex + 1][colIndex + i].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + 1][colIndex + i].getType() == CraftType::forbid))
				{
					m_fieldTab[rowIndex + 1][colIndex + i].setType(CraftType::forbid);
					craftModel.addForbidArea(m_fieldTab[rowIndex + 1][colIndex + i]);
				}	
			}
			
			//Top
			if (colIndex + type <= 9 && rowIndex > 0 && (m_fieldTab[rowIndex - 1][colIndex + type].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex + type].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - 1][colIndex + type].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex + type]);
			}

			//Center
			if (colIndex + type <= 9 && (m_fieldTab[rowIndex][colIndex + type].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex][colIndex + type].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex][colIndex + type].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex][colIndex + type]);
			}

			//Bottom
			if (colIndex + type <= 9 && rowIndex < 9 && (m_fieldTab[rowIndex + 1][colIndex + type].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + 1][colIndex + type].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex + 1][colIndex + type].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex + 1][colIndex + type]);
			}
				

		}
		else if (allowCraft && allowedDirection == 'W')
		{
			//Top
			if (colIndex < 9 && rowIndex>0 && (m_fieldTab[rowIndex - 1][colIndex + 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex + 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - 1][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex + 1]);
			}
				

			//Center
			if (colIndex < 9 && (m_fieldTab[rowIndex][colIndex + 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex][colIndex + 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex][colIndex + 1]);
			}	

			//Bottom
			if (colIndex < 9 && rowIndex < 9 && (m_fieldTab[rowIndex + 1][colIndex + 1].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + 1][colIndex + 1].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex + 1][colIndex + 1].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex + 1][colIndex + 1]);
			}

			for (int i = 0; i < type; i++)
			{
				if (colIndex - i >= 0 && rowIndex > 0 && (m_fieldTab[rowIndex - 1][colIndex - i].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex - i].getType() == CraftType::forbid))
				{
					m_fieldTab[rowIndex - 1][colIndex - i].setType(CraftType::forbid);
					craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex - i]);
				}
	
				m_fieldTab[rowIndex][colIndex - i].setType(craftType);
				craftModel.addField(m_fieldTab[rowIndex][colIndex - i]);

				if (rowIndex < 9 && (m_fieldTab[rowIndex + 1][colIndex - i].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + 1][colIndex - i].getType() == CraftType::forbid))
				{
					m_fieldTab[rowIndex + 1][colIndex - i].setType(CraftType::forbid);
					craftModel.addForbidArea(m_fieldTab[rowIndex + 1][colIndex - i]);
				}	
			}

			//Top
			if (colIndex - type >= 0 && rowIndex > 0 && (m_fieldTab[rowIndex - 1][colIndex - type].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex - type].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - 1][colIndex - type].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex - type]);
			}

			//Center
			if (colIndex - type >= 0 && (m_fieldTab[rowIndex][colIndex - type].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex][colIndex - type].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex][colIndex - type].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex][colIndex - type]);
			}

			//Bottom
			if (colIndex - type >= 0 && rowIndex < 9 && (m_fieldTab[rowIndex + 1][colIndex - type].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex + 1][colIndex - type].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex + 1][colIndex - type].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex + 1][colIndex - type]);
			}	
		}
		if (allowCraft)
		{
			addCraft(craftModel);
		}
	}
}

void Board::checkCraftIsDestroyed(const Field& field)
{
	int craftIndex = getCraft(field);
	if (craftIndex >= 0)
	{
		m_craftTab[craftIndex].destroyEl();

		if (m_craftTab[craftIndex].checkStateCraft())
		{
			std::cout << "Destroyed threeMasted craft" << std::endl;

			//Tick field around craft
			tickForbidArea(m_craftTab[craftIndex]);

			//delete forbid element from available field
			delForbidAvailableField(m_craftTab[craftIndex].getForbidArea());

			//delete element from hitCraftTab
			m_hitCraftTab.clear();
		}
	}
}

void Board::tickForbidArea(const Craft& craft)
{
	for (int i = 0; i < craft.getForbidArea().size(); i++)
	{
		Field forbidField = craft.getForbidArea()[i];
		forbidField.setColor(sf::Color::Magenta);
		forbidField.setChecked(true);
		updateTabEl(forbidField);
	}
}
