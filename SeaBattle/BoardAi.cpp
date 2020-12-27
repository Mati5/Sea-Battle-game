#include "BoardAi.h"

BoardAi::BoardAi()
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
}

Field BoardAi::action(std::array<std::array<Field, 10>, 10> fieldTab, std::vector<Craft> craftTab)
{
	Field field2;

	if (m_hitCraftTab.size() == 1)
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
			if (!fieldTab[y - 1][x].getChecked()) direction.push_back('N');
			if (!fieldTab[y][x + 1].getChecked()) direction.push_back('E');
			if (!fieldTab[y + 1][x].getChecked()) direction.push_back('S');
			if (!fieldTab[y][x - 1].getChecked()) direction.push_back('W');
		}
		else if (x == 0 && y == 0)
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
		else if (x == 9 && y > 0 && y < 9)
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

		if (!direction.empty())
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
				field2 = fieldTab[y][x - 1];
				break;
			default:
				break;
			}
		}
		else {
			field2 = getAvailableField(fieldTab);
		}
	}
	else if (m_hitCraftTab.size() > 1)
	{
		int hitCraftIndex = getCraft(craftTab, m_hitCraftTab[0]);
		std::string hitCraftDirection = craftTab[hitCraftIndex].getOrientation();

		if (hitCraftDirection == "vertical") //N/S
		{
			for (auto&& value : m_hitCraftTab)
			{
				int x = value.getCoordinateX();
				int y = value.getCoordinateY();

				if (y - 1 >= 0 && !fieldTab[y - 1][x].getChecked()) {
					field2 = fieldTab[y - 1][x];
					break;
				}
				else if (y + 1 <= 9 && !fieldTab[y + 1][x].getChecked())
				{
					field2 = fieldTab[y + 1][x];
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

				if (x - 1 >= 0 && !fieldTab[y][x - 1].getChecked()) {
					field2 = fieldTab[y][x - 1];
					break;
				}
				else if (x + 1 <= 9 && !fieldTab[y][x + 1].getChecked())
				{
					field2 = fieldTab[y][x + 1];
					break;
				}
			}
		}
	}
	else
	{
		field2 = getAvailableField(fieldTab);
	}
	
	if (!field2.getChecked())
	{

		if (field2.hitCraft()) {
			//add to hitCraftTab to remeber which craft is partly destroyed
			m_hitCraftTab.push_back(field2);
		}

		int checkedFieldIndex = getIndexAvailableField(field2.getCoordinateX(), field2.getCoordinateY());
		if(checkedFieldIndex>=0)
			delAvailableField(checkedFieldIndex);
	}

	return field2;
}

Field BoardAi::getAvailableField(std::array<std::array<Field, 10>, 10> fieldTab)
{
	int availableFieldSize = m_availableField.size();
	int randField = rand() % availableFieldSize;
	int randX = m_availableField[randField][1];
	int randY = m_availableField[randField][0];

	return fieldTab[randY][randX];
}

void BoardAi::delAvailableField(int index)
{
	m_availableField.erase(m_availableField.begin() + index);
}

void BoardAi::delForbidAvailableField(const std::vector<Field>& forbidArea)
{
	for (auto&& value: forbidArea)
	{
		int coordinateX = value.getCoordinateX();
		int coordinateY = value.getCoordinateY();
		int index = getIndexAvailableField(coordinateX, coordinateY);

		if (index >= 0)
			delAvailableField(index);
	}
}

int BoardAi::getIndexAvailableField(int coordinateX, int coordinateY)
{
	for (int i = 0; i < m_availableField.size(); i++)
	{
		if (m_availableField[i][0] == coordinateY && m_availableField[i][1] == coordinateX)
			return i;
	}

	return -1;
}

void BoardAi::clearHitCraftTab()
{
	m_hitCraftTab.clear();
}
