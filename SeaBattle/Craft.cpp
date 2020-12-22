#include "Craft.h"

Craft::Craft()
{
	craftType = CraftType::zeroMasted;
	quantityDestroyedEl = 0;
}


Field& Craft::getSpriteField()
{
	return this->sprite;
}

std::vector<Field> Craft::getArea()
{
	return this->area;
}

std::vector<Field> Craft::getForbidArea()
{
	return this->forbidArea;
}

void Craft::addField(const Field& field)
{
	area.push_back(field);
}

void Craft::addForbidArea(Field field)
{
	this->forbidArea.push_back(field);
}

void Craft::setOrientation(std::string orientation)
{
	this->orientation = orientation;
}

std::string Craft::getOrientation()
{
	return this->orientation;
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
	if(getCraftTypeNumber(this->craftType)>0 && getCraftTypeNumber(this->craftType)<=4)
		return this->quantityDestroyedEl == getCraftTypeNumber(this->craftType);
	return false;
}

