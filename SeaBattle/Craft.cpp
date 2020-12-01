#include "Craft.h"

/*void Craft::setArea(Field* area)
{
	this->area = area;
}

Field* Craft::getArea()
{
	return this->area;
}*/

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

void Craft::setCraftType(CraftType craftType)
{
	this->craftType = craftType;
}

CraftType Craft::getCraftType()
{
	return this->craftType;
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
}

bool Craft::checkStateCraft()
{
	return this->quantityDestroyedEl == this->craftTypeNumber;
}
