#include "Craft.h"

/*void Craft::setArea(Field* area)
{
	this->area = area;
}*/



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

bool Craft::onClick(Field& field, float mouseX, float mouseY)
{
	if (field.onClick(mouseX, mouseY))
	{
		CraftType craftType = field.getType();
		if (craftType == this->getCraftType())
		{

			std::cout << "You hit a craft" << std::endl;
			std::cout << int(field.getType()) << std::endl;
			field.setColor(sf::Color::Blue);

			this->destroyEl();
			std::cout << "==================== " << this->quantityDestroyedEl << "=========" << std::endl;

			if (this -> getQuantityDestroyedEl() == this->getCraftTypeNumber(this->getCraftType())) {
				//destroyed all craft
				std::cout << "DESTROYED craft";
			}
		}
		return true;
	}

	return false;
}