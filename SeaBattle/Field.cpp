#include "Field.h"

Field::Field()
{
	m_width = 45;
	m_height = 45;
	m_type = CraftType::zeroMasted;
	m_spaceBetweenField = 50;
	m_checked = false;
	m_position = Orientation::Horizontal;
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
	m_coordinate[0] = x * m_spaceBetweenField;
	m_coordinate[1] = y * m_spaceBetweenField;

	m_sprite.setPosition(m_coordinate[0], m_coordinate[1]);
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
	return int(m_type) > 0 && int(m_type) < 5;
}

void Field::rotateField(sf::Texture& texture)
{
	
	if (m_position == Orientation::Horizontal)
	{
		switch (m_type)
		{
		case CraftType::fourMasted:	
			m_height = 180;
			break;
		case CraftType::threeMasted:
			m_height = 135;
			break;
		case CraftType::twoMasted:
			m_height = 90;
			break;
		case CraftType::oneMasted:
			m_height = 45;
			break;
		}
		m_width = 45;
		m_position = Orientation::Vertical;
		m_sprite.setTextureRect(sf::IntRect(0, 0, int(m_width), int(m_height)));
		m_sprite.setTexture(texture);
	} 
	else
	{
		switch (m_type)
		{
		case CraftType::fourMasted:
			m_width = 180;
			break;
		case CraftType::threeMasted:
			m_width = 135;
			break;
		case CraftType::twoMasted:
			m_width = 90;
			break;
		case CraftType::oneMasted:
			m_width = 45;
			break;
		}
		
		m_height = 45;
		m_position = Orientation::Horizontal;
		m_sprite.setTextureRect(sf::IntRect(0, 0, int(m_width), int(m_height)));
		m_sprite.setTexture(texture);
	}
}

Orientation Field::getPosition() const
{
	return m_position;
}
