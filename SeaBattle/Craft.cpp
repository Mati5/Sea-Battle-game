#include "Craft.h"

void Craft::setArea(Field* area)
{
	this->area = area;
}

Field* Craft::getArea()
{
	return this->area;
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
