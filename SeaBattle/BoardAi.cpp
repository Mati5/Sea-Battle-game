#include "BoardAi.h"

BoardAi::BoardAi()
{
	for (int y = 0; y < getDimensionY(); y++) {
		for (int x = 0; x < getDimensionX(); x++) {
			Craft craft;
			Field field;

			field.setCoordinate(x, y);
			craft.addField(field);
			m_fieldTab[y][x] = field;

			m_availableField.push_back({ y,x });
		}
	}
}

Field BoardAi::action(std::array<std::array<Field, 10>, 10> fieldTab, std::vector<Craft> craftTab)
{
	Field field;

	if (m_hitCraftTab.size() == 1)
	{
		field = m_hitCraftTab[0];

		//Tick 4 option (random 4 direction)
		std::vector<Direction> direction = {};
		int x = field.getCoordinateX();
		int y = field.getCoordinateY();

		//1 check which direction is available
		// all 4 direction
		if (x > 0 && x < 9 && y > 0 && y < 9)
		{
			if (!fieldTab[y - 1][x].getChecked()) direction.push_back(Direction::N);
			if (!fieldTab[y][x + 1].getChecked()) direction.push_back(Direction::E);
			if (!fieldTab[y + 1][x].getChecked()) direction.push_back(Direction::S);
			if (!fieldTab[y][x - 1].getChecked()) direction.push_back(Direction::W);
		}
		else if (x == 0 && y == 0)
		{
			if (!fieldTab[y][x + 1].getChecked()) direction.push_back(Direction::E);
			if (!fieldTab[y + 1][x].getChecked()) direction.push_back(Direction::S);
		}
		else if (x == 0 && y == 9)
		{
			if (!fieldTab[y - 1][x].getChecked()) direction.push_back(Direction::N);
			if (!fieldTab[y][x + 1].getChecked()) direction.push_back(Direction::E);
		}
		else if (x == 9 && y == 0)
		{
			if (!fieldTab[y + 1][x].getChecked()) direction.push_back(Direction::S);
			if (!fieldTab[y][x - 1].getChecked()) direction.push_back(Direction::W);
		}
		else if (x == 9 && y == 9)
		{
			if (!fieldTab[y - 1][x].getChecked()) direction.push_back(Direction::N);
			if (!fieldTab[y][x - 1].getChecked()) direction.push_back(Direction::W);
		}
		else if (x == 0 && y > 0 && y < 9)
		{
			if (!fieldTab[y - 1][x].getChecked()) direction.push_back(Direction::N);
			if (!fieldTab[y][x + 1].getChecked()) direction.push_back(Direction::E);
			if (!fieldTab[y + 1][x].getChecked()) direction.push_back(Direction::S);
		}
		else if (x == 9 && y > 0 && y < 9)
		{
			if (!fieldTab[y - 1][x].getChecked()) direction.push_back(Direction::N);
			if (!fieldTab[y + 1][x].getChecked()) direction.push_back(Direction::S);
			if (!fieldTab[y][x - 1].getChecked()) direction.push_back(Direction::W);
		}
		else if (x > 0 && x < 9 && y == 0)
		{
			if (!fieldTab[y][x + 1].getChecked()) direction.push_back(Direction::E);
			if (!fieldTab[y + 1][x].getChecked()) direction.push_back(Direction::S);
			if (!fieldTab[y][x - 1].getChecked()) direction.push_back(Direction::W);
		}
		else if (x > 0 && x < 9 && y == 9)
		{
			if (!fieldTab[y - 1][x].getChecked()) direction.push_back(Direction::N);
			if (!fieldTab[y][x + 1].getChecked()) direction.push_back(Direction::E);
			if (!fieldTab[y][x - 1].getChecked()) direction.push_back(Direction::W);
		}

		if (!direction.empty())
		{
			int randDirectionNum = RandNum(direction.size());
			Direction randDirection = direction[randDirectionNum];

			switch (randDirection)
			{
			case Direction::N:
				field = fieldTab[y - 1][x];
				break;
			case Direction::E:
				field = fieldTab[y][x + 1];
				break;
			case Direction::S:
				field = fieldTab[y + 1][x];
				break;
			case Direction::W:
				field = fieldTab[y][x - 1];
				break;
			default:
				break;
			}
		}
		else {
			field = getAvailableField(fieldTab);
		}
	}
	else if (m_hitCraftTab.size() > 1)
	{
		int hitCraftIndex = getCraft(craftTab, m_hitCraftTab[0]);
		Orientation hitCraftOrientation = craftTab[hitCraftIndex].getOrientation();

		if (hitCraftOrientation == Orientation::Vertical) //N/S
		{
			for (auto&& value : m_hitCraftTab)
			{
				int x = value.getCoordinateX();
				int y = value.getCoordinateY();

				if (y - 1 >= 0 && !fieldTab[y - 1][x].getChecked()) {
					field = fieldTab[y - 1][x];
					break;
				}
				else if (y + 1 <= 9 && !fieldTab[y + 1][x].getChecked())
				{
					field = fieldTab[y + 1][x];
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
					field = fieldTab[y][x - 1];
					break;
				}
				else if (x + 1 <= 9 && !fieldTab[y][x + 1].getChecked())
				{
					field = fieldTab[y][x + 1];
					break;
				}
			}
		}
	}
	else
	{
		field = getAvailableField(fieldTab);
	}
	
	if (!field.getChecked())
	{

		if (field.hitCraft()) {
			//add to hitCraftTab to remeber which craft is partly destroyed
			m_hitCraftTab.push_back(field);
		}

		int checkedFieldIndex = getIndexAvailableField(field.getCoordinateX(), field.getCoordinateY());
		if(checkedFieldIndex>=0)
			delAvailableField(checkedFieldIndex);
	}

	return field;
}

Field BoardAi::getAvailableField(const std::array<std::array<Field, 10>, 10>& fieldTab)
{
	int availableFieldSize = m_availableField.size();
	int randField = RandNum(availableFieldSize);
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
