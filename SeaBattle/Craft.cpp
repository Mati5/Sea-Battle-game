#include "Craft.h"

Craft::Craft()
{
	m_craftType = CraftType::zeroMasted;
	m_quantityDestroyedEl = 0;
}

std::vector<Field> Craft::getArea() const
{
	return m_area;
}

std::vector<Field> Craft::getForbidArea() const
{
	return m_forbidArea;
}

void Craft::addField(const Field& field)
{
	m_area.push_back(field);
}

void Craft::addForbidArea(const Field& field)
{
	m_forbidArea.push_back(field);
}

void Craft::setOrientation(const std::string& orientation)
{
	m_orientation = orientation;
}

std::string Craft::getOrientation() const
{
	return m_orientation;
}

void Craft::setCraftType(CraftType craftType)
{
	m_craftType = craftType;
}

CraftType Craft::getCraftType() const
{
	return m_craftType;
}

int Craft::getCraftTypeNumber(CraftType craftType) const
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
	m_quantityDestroyedEl = quantityDestroyedEl;
}

int Craft::getQuantityDestroyedEl() const
{
	return m_quantityDestroyedEl;
}

void Craft::destroyEl()
{
	m_quantityDestroyedEl += 1;
}

bool Craft::checkStateCraft() const
{
	if(getCraftTypeNumber(m_craftType)>0 && getCraftTypeNumber(m_craftType)<=4)
		return m_quantityDestroyedEl == getCraftTypeNumber(m_craftType);
	return false;
}