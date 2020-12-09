#include "Craft.h"

std::vector<std::vector<Field>> Craft::getArea()
{
	return this->area;
}

std::vector<Field> Craft::getForbidArea()
{
	return this->forbidArea;
}

void Craft::addField(Field field)
{
	int sizeY = this->area.size();
	
	if (sizeY > 0)
	{
		int sizeX = this->area[sizeY - 1].size();
		if (this->area[sizeY - 1][sizeX - 1].getCoordinateY() == field.getCoordinateY())
		{
			this->area[sizeY - 1].push_back(field);
		}
		else
		{
			this->area.push_back(std::vector<Field>{field});
		}
	}
	else
	{
		this->area.push_back(std::vector<Field>{field});
	}

}

void Craft::addForbidArea(Field field)
{
	this->forbidArea.push_back(field);
}

void Craft::setCraftType(CraftType craftType)
{
	this->craftType = craftType;
}

CraftType Craft::getCraftType()
{
	return this->craftType;
}

int Craft::getCraftTypeNumber(CraftType craftType)
{
	switch (craftType)
	{
		case CraftType::zeroMasted:
			return 0;
		case CraftType::oneMasted:
			return 1;
		case CraftType::twoMasted:
			return 2;
		case CraftType::threeMasted:
			return 3;
		case CraftType::fourMasted:
			return 4;
		default:
			return -1;
	}
}

void Craft::setQuantityDestroyedEl(int quantityDestroyedEl)
{
	this->quantityDestroyedEl = quantityDestroyedEl;
}

int Craft::getQuantityDestroyedEl()
{
	return this->quantityDestroyedEl;
}

void Craft::destroyEl()
{
	this->quantityDestroyedEl += 1;

	std::cout << "destroyed el " << this->quantityDestroyedEl << std::endl;
}

bool Craft::checkStateCraft()
{
	return this->quantityDestroyedEl == getCraftTypeNumber(this->craftType);
}
