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
			Field field;
			field.setCoordinate(x, y);
			field.setSprite(m_fieldTexture);

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

void Board::updateCraftTab(int index, const Craft& craft)
{
	m_craftTab[index] = craft;
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

void Board::renderBoard(sf::RenderWindow& mWindow, bool showCraft, bool showForbidArea) const
{	
	for (int y = 0; y < m_dimensionY; y++)
	{
		for (int x = 0; x < m_dimensionX; x++)
		{
			Field field = m_fieldTab[y][x];
			
			field.setSprite(m_fieldTexture);

			if(showCraft && int(field.getType())>0 && int(field.getType())<=4)
				field.setSprite(m_craftTexture);

			if(showForbidArea && field.getType() == CraftType::forbid)
				field.setSprite(m_checkedTexture);

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
	if (rowIndex > 0 && (m_fieldTab[rowIndex-1][colIndex].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex-1][colIndex].getType() != CraftType::forbid))
	{
		allowCraft = false;
		return;
	}

	if (rowIndex > 0 && colIndex > 0 && (m_fieldTab[rowIndex - 1][colIndex - 1].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex - 1][colIndex - 1].getType() != CraftType::forbid))
	{
		allowCraft = false;
		return;
	}

	if (rowIndex > 0 && colIndex < 9 && (m_fieldTab[rowIndex - 1][colIndex + 1].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex - 1][colIndex + 1].getType() != CraftType::forbid))
	{
		allowCraft = false;
		return;
	}

	for (int i = 0; i <= type; i++)
	{
		if (i>0 && (rowIndex + ((i-1) * direction) > 9 || rowIndex + ((i-1) * direction) < 0))
		{
			allowCraft = false;
			return;
		}

		if (rowIndex + (i * direction) <=9 && rowIndex + (i * direction) >=0 && m_fieldTab[rowIndex + (i*direction)][colIndex].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex + (i * direction)][colIndex].getType() != CraftType::forbid)
		{
			allowCraft = false;
			return;
		}

		if (rowIndex + (i * direction)>=0 && rowIndex + (i * direction) <=9 && colIndex>0 && m_fieldTab[rowIndex + (i * direction)][colIndex-1].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex + (i * direction)][colIndex-1].getType() != CraftType::forbid)
		{
			allowCraft = false;
			return;
		}

		if (colIndex<9 && rowIndex + (i * direction)>=0 && rowIndex + (i * direction)<=9 && m_fieldTab[rowIndex + (i * direction)][colIndex + 1].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex + (i * direction)][colIndex + 1].getType() != CraftType::forbid)
		{
			allowCraft = false;
			return;
		}
	}
}

void Board::checkVertical(int rowIndex, int colIndex, int type, bool& allowCraft, Direction& allowedDirection)
{
	allowCraft = true;
	allowedDirection = Direction::S;

	if (rowIndex + type - 1 <= 9)
	{
		allowCraft = true;
		checkNSDirection(rowIndex, colIndex, type, allowCraft, 1);
		
		if (!allowCraft)
		{
			allowCraft = true;
			allowedDirection = Direction::N;

			checkNSDirection(rowIndex, colIndex, type, allowCraft, -1);
		}
	}
	else if(rowIndex-type-1>=0)
	{
		allowCraft = true;
		allowedDirection = Direction::N;
		checkNSDirection(rowIndex, colIndex, type, allowCraft, -1);

		if (!allowCraft)
		{
			allowCraft = true;
			allowedDirection = Direction::S;

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
	if (colIndex>0 && (m_fieldTab[rowIndex][colIndex - 1].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex][colIndex - 1].getType() != CraftType::forbid))
	{
		allowCraft = false;
		return;
	}

	if (rowIndex > 0 && colIndex > 0 && (m_fieldTab[rowIndex-1][colIndex - 1].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex-1][colIndex - 1].getType() != CraftType::forbid))
	{
		allowCraft = false;
		return;
	}

	if (rowIndex < 9 && colIndex > 0 && (m_fieldTab[rowIndex+1][colIndex -1].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex+1][colIndex - 1].getType() != CraftType::forbid))
	{
		allowCraft = false;
		return;
	}

	for (int i = 0; i <= type; i++)
	{
		if (i>0 && colIndex + ((i-1) * direction) < 0 || colIndex + ((i-1) * direction) > 9)
		{
			allowCraft = false;
			return;
		}

		if ((colIndex + (i * direction)<=9 && colIndex + (i * direction) >= 0) && m_fieldTab[rowIndex][colIndex + (i*direction)].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex][colIndex + (i * direction)].getType() != CraftType::forbid)
		{
			allowCraft = false;
			return;
		}

		if (rowIndex>0 && colIndex + (i * direction)>=0 && colIndex + (i * direction) <=9 && m_fieldTab[rowIndex-1][colIndex + (i * direction)].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex-1][colIndex + (i * direction)].getType() != CraftType::forbid)
		{
			allowCraft = false;
			return;
		}

		if (rowIndex < 9 && colIndex + (i * direction)>=0 && colIndex + (i * direction)<=9 && m_fieldTab[rowIndex + 1][colIndex + (i * direction)].getType() != CraftType::zeroMasted && m_fieldTab[rowIndex+1][colIndex + (i * direction)].getType() != CraftType::forbid)
		{
			allowCraft = false;
			return;
		}
	}
}

void Board::checkHorizontal(int rowIndex, int colIndex, int type, bool& allowCraft, Direction& allowedDirection)
{
	allowCraft = true;
	allowedDirection = Direction::E;
	if (colIndex + type - 1 <= 9)
	{
		checkWEDirection(rowIndex, colIndex, type, allowCraft, 1);

		if (!allowCraft)
		{
			allowCraft = true;
			allowedDirection = Direction::W;

			checkWEDirection(rowIndex, colIndex, type, allowCraft, -1);
		}
	}
	else if (colIndex - type - 1 >= 0)
	{
		allowCraft = true;
		allowedDirection = Direction::W;

		checkWEDirection(rowIndex, colIndex, type, allowCraft, -1);
			
		if(!allowCraft)
		{
			allowCraft = true;
			allowedDirection = Direction::E;

			checkWEDirection(rowIndex, colIndex, type, allowCraft, 1);	
		}
	}
	else
	{
		std::cout << "WARNING HORIZONTAL CHECK" << std::endl;
	}
}

void Board::setCraftOnMap(const Direction& allowedDirection, Craft& craftModel, int craftIndex)
{
	int direction = 0;
	int colIndex = craftModel.getCraftSprite().getCoordinateX();
	int rowIndex = craftModel.getCraftSprite().getCoordinateY();
	auto type = int(craftModel.getCraftType());
	CraftType craftType = craftModel.getCraftType();

	switch (allowedDirection)
	{
	case Direction::N:
	case Direction::S:
		direction = 1;
		break;
	default:
		break;
	}

	craftModel.setOrientation(direction == 1 ? Orientation::Vertical : Orientation::Horizontal);

	if (allowedDirection == Direction::S)
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
	else if (allowedDirection == Direction::N)
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
	else if (allowedDirection == Direction::E)
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
			if (colIndex <= 9 && rowIndex > 0 && (m_fieldTab[rowIndex - 1][colIndex + i].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex + i].getType() == CraftType::forbid))
			{
				m_fieldTab[rowIndex - 1][colIndex + i].setType(CraftType::forbid);
				craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex + i]);
			}

			//Center
			m_fieldTab[rowIndex][colIndex + i].setType(craftType);
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
	else if (allowedDirection == Direction::W)
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
	
	updateCraftTab(craftIndex, craftModel);
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
		for (size_t j = 0; j < craftTab[i].getArea().size(); j++)
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

void randomEmptyField(int& rowIndex, int& colIndex, const std::array<std::array<Field, 10>, 10>& fieldTab)
{
	do
	{
		rowIndex = RandNum(10);
		colIndex = RandNum(10);

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
		Direction allowedDirection;

		//rand direction (vertical(1)/horizontal(0))
		int orientation = RandNum(2);

		//Rand row
		int rowIndex = RandNum(10);

		//rand cols
		int colIndex = RandNum(10);

		//Rand empty field
		randomEmptyField(rowIndex, colIndex, m_fieldTab);

		//std::cout << std::endl << "Rand field" << rowIndex << ' ' << colIndex << std::endl;

		//Check if field is empty vertical
		if (orientation == 1)
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
		
		m_fieldTab[rowIndex][colIndex].setType(craftType);
		Craft craftModel;
		craftModel.setCraftType(craftType);
		craftModel.setOrientation(orientation == 1 ? Orientation::Vertical : Orientation::Horizontal);

		//If checked set craft on map
		if (allowCraft && allowedDirection == Direction::S)
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
		else if (allowCraft && allowedDirection == Direction::N)
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
		else if (allowCraft && allowedDirection == Direction::E)
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
				if (colIndex <= 9 && rowIndex > 0 && (m_fieldTab[rowIndex - 1][colIndex + i].getType() == CraftType::zeroMasted || m_fieldTab[rowIndex - 1][colIndex + i].getType() == CraftType::forbid))
				{
					m_fieldTab[rowIndex - 1][colIndex + i].setType(CraftType::forbid);
					craftModel.addForbidArea(m_fieldTab[rowIndex - 1][colIndex + i]);
				}

				//Center
				m_fieldTab[rowIndex][colIndex + i].setType(craftType);
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
		else if (allowCraft && allowedDirection == Direction::W)
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

		/*if (allowCraft)
		{
			setCraftOnMap(allowedDirection, craftModel);
		}*/
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
	for (size_t i = 0; i<craft.getForbidArea().size(); i++)
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

void Board::delCraft(int craftIndex)
{
	Craft craft = m_craftTab[craftIndex];
	
	for (size_t i = 0; i < craft.getArea().size(); i++)
	{
		Field field;
		field.setCoordinate(craft.getArea()[i].getCoordinateX(), craft.getArea()[i].getCoordinateY());
		field.setSprite(m_fieldTexture);
		m_fieldTab[craft.getArea()[i].getCoordinateY()][craft.getArea()[i].getCoordinateX()] = field;
	}

	for (size_t i = 0;i < craft.getForbidArea().size(); i++)
	{
		Field field;
		field.setCoordinate(craft.getForbidArea()[i].getCoordinateX(), craft.getForbidArea()[i].getCoordinateY());
		field.setSprite(m_fieldTexture);
		m_fieldTab[craft.getForbidArea()[i].getCoordinateY()][craft.getForbidArea()[i].getCoordinateX()] = field;
	}


	//m_craftTab.erase(m_craftTab.begin() + craftIndex);
}

void Board::setCraftTab(const sf::Texture& fourMTexture, const sf::Texture& threeMTexture, const sf::Texture& twoMTexture, const sf::Texture& oneMTexture)
{
	m_craftTab.clear();

	for (int i = 0; i < 1; i++)
	{
		Craft craft;
		craft.getCraftSprite().setType(CraftType::fourMasted);
		craft.setCraftType(CraftType::fourMasted);
		craft.getCraftSprite().setWidth(180);
		craft.getCraftSprite().setHeight(45);
		craft.getCraftSprite().setCoordinate(11, 3);
		craft.getCraftSprite().setSprite(fourMTexture);
		m_craftTab.push_back(craft);
	}

	for (int i = 0; i < 2; i++)
	{
		Craft craft;
		craft.getCraftSprite().setType(CraftType::threeMasted);
		craft.setCraftType(CraftType::threeMasted);
		craft.getCraftSprite().setWidth(135);
		craft.getCraftSprite().setHeight(45);
		craft.getCraftSprite().setCoordinate(11+(i*3), 4);
		craft.getCraftSprite().setSprite(threeMTexture);
		m_craftTab.push_back(craft);
	}

	for (int i = 0; i < 3; i++)
	{
		Craft craft;
		craft.getCraftSprite().setType(CraftType::twoMasted);
		craft.setCraftType(CraftType::twoMasted);
		craft.getCraftSprite().setWidth(90);
		craft.getCraftSprite().setHeight(45);
		craft.getCraftSprite().setCoordinate(11+(i*2), 5);
		craft.getCraftSprite().setSprite(twoMTexture);
		m_craftTab.push_back(craft);
	}

	for (int i = 0; i < 4; i++)
	{
		Craft craft;
		craft.getCraftSprite().setType(CraftType::oneMasted);
		craft.setCraftType(CraftType::oneMasted);
		craft.getCraftSprite().setWidth(45);
		craft.getCraftSprite().setHeight(45);
		craft.getCraftSprite().setCoordinate(11+(i*1), 6);
		craft.getCraftSprite().setSprite(oneMTexture);
		m_craftTab.push_back(craft);
	}
}
