#include "Field.h"

Field::Field()
{
	m_width = 45;
	m_height = 45;
	m_type = CraftType::zeroMasted;
	m_spaceBetweenField = 50;
}

Field::~Field() = default;

void Field::setType(const CraftType type)
{
	m_type = type;
}

CraftType Field::getType() const
{
	return m_type;
}

void Field::setChecked(bool checked)
{
	m_checked = checked;
}

bool Field::getChecked() const
{
	return m_checked;
}

void Field::setSpaceBetweenField(int spaceBetweenField)
{
	m_spaceBetweenField = spaceBetweenField;
}

int Field::getSpaceBetweenField() const
{
	return m_spaceBetweenField;
}

void Field::setCoordinate(int x, int y)
{
	m_coordinate[0] = x * this->getSpaceBetweenField();
	m_coordinate[1] = y * this->getSpaceBetweenField();
}

int Field::getCoordinateX() const
{
	return GridField::getCoordinateX() > 0 ? GridField::getCoordinateX() / m_spaceBetweenField : GridField::getCoordinateX();
}

int Field::getCoordinateY() const
{
	return GridField::getCoordinateY() > 0 ? GridField::getCoordinateY() / m_spaceBetweenField : GridField::getCoordinateY();
}

bool Field::hitCraft() const
{
	return int(this->getType()) > 0 && int(this->getType()) < 5;
}