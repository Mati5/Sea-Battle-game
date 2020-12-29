#include "Board.h"

Board::Board()
{
	if (!m_fieldTexture.loadFromFile("../images/field.png"))
		std::cout << "Error load craft texture!" << std::endl;

	if (!m_craftTexture.loadFromFile("../images/craft.png"))
		std::cout << "Error load craft texture!" << std::endl;

	if (!m_checkedTexture.loadFromFile("../images/checked.png"))
		std::cout << "Error load craft texture!" << std::endl;

	if (!m_hitCraftTexture.loadFromFile("../images/hitCraft.png"))
		std::cout << "Error load craft texture!" << std::endl;

	for (int y = 0; y < getDimensionY(); y++) {
		for (int x = 0; x < getDimensionX(); x++) {
			Craft craft;
			Field field;
			
			field.setCoordinate(x, y);
			field.setSprite(m_fieldTexture);
			craft.addField(field);
			m_fieldTab[y][x] = field;
		}
	}
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

void Board::renderBoard(sf::RenderWindow& mWindow, bool showCraft) const
{	
	for (int y = 0; y < m_dimensionY; y++)
	{
		for (int x = 0; x < m_dimensionX; x++)
		{
			Field field = m_fieldTab[y][x];
			
			field.setSprite(m_fieldTexture);

			if(showCraft && int(field.getType())>0 && int(field.getType())<=4)
				field.setSprite(m_craftTexture);

			if (field.getChecked())
				field.setSprite(m_checkedTexture);
			
			if (field.getChecked() && field.getType() != CraftType::zeroMasted && field.getType() != CraftType::forbid)
				field.setSprite(m_hitCraftTexture);

			mWindow.draw(field.getSprite());
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

int Board::getCraft(std::vector<Craft> craftTab, const Field& field) const
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

bool Board::checkCraftIsDestroyed(const Field& field)
{
	int craftIndex = getCraft(m_craftTab, field);
	if (craftIndex >= 0)
	{
		m_craftTab[craftIndex].destroyEl();

		if (m_craftTab[craftIndex].checkStateCraft())
		{
			//Tick field around craft
			tickForbidArea(m_craftTab[craftIndex]);

			return true;
		}
	}

	return false;
}

void Board::tickForbidArea(const Craft& craft)
{
	for (int i = 0; i < craft.getForbidArea().size(); i++)
	{
		Field forbidField = craft.getForbidArea()[i];
		forbidField.setChecked(true);
		updateTabEl(forbidField);
	}
}

void Board::handleInput(const sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int y = 0; y < m_dimensionY; y++)
		{
			for (int x = 0; x < m_dimensionX; x++)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

				float mouseX = worldPos.x;
				float mouseY = worldPos.y;

				if (!m_fieldTab[y][x].getChecked() && m_fieldTab[y][x].onClick(mouseX, mouseY))
				{
					m_fieldTab[y][x].setChecked(true);
					setClickedField(m_fieldTab[y][x]);
					updateTabEl(m_fieldTab[y][x]);

					if (m_fieldTab[y][x].hitCraft())
						m_boardStats++;

					//check if craft is destroyed
					checkCraftIsDestroyed(m_fieldTab[y][x]);
				}
			}
		}
	}
}

int Board::getBoardStats() const
{
	return m_boardStats;
}