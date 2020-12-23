#include "GridField.h"

GridField::GridField() :m_width{ 20.f }
{
	m_coordinate.push_back(10);
	m_coordinate.push_back(10);
	m_color = sf::Color::Red;
	m_width = 20.f;
	m_height = 20.f;
	m_spaceBetweenField = 40;
	m_sprite.setPosition(float(m_coordinate[0]), float(m_coordinate[1]));
}

GridField::~GridField()
{
	m_coordinate.clear();
}


void GridField::setCoordinate(int x, int y)
{
	m_coordinate[0] = x;
	m_coordinate[1] = y;
}

std::vector<int> GridField::getCoordinate() const
{
	return m_coordinate;
}

int GridField::getCoordinateX() const
{
	return m_coordinate[0];
}

int GridField::getCoordinateY() const
{
	return m_coordinate[1];
}

void GridField::setColor(sf::Color color)
{
	m_color = color;
}

sf::Color GridField::getColor() const
{
	return m_color;
}

void GridField::setWidth(float width)
{
	m_width = width;
}

float GridField::getWidth() const 
{
	return m_width;
}

void GridField::setHeight(float height)
{
	m_height = height;
}

float GridField::getHeight() const
{
	return m_height;
}

void GridField::setSpaceBetweenField(int spaceBetweenField)
{
	m_spaceBetweenField = spaceBetweenField;
}

int GridField::getSpaceBetweenField() const
{
	return m_spaceBetweenField;
}

bool GridField::onClick(float mouseX, float mouseY)
{
	auto fieldPositionX = float(m_coordinate[0]);
	auto fieldPositionY = float(m_coordinate[1]);

	if (mouseX > fieldPositionX && mouseX < fieldPositionX + m_width
		&& mouseY > fieldPositionY && mouseY < fieldPositionY + m_height)
	{
		return true;
	}

	return false;
}

sf::RectangleShape GridField::renderField() const
{
	return sf::RectangleShape();
}

void GridField::setSprite(const sf::Texture& texture)
{
	m_sprite.setTexture(texture, true);
	auto x = float(m_coordinate[0]);
	auto y = float(m_coordinate[1]);

	m_sprite.setPosition(x, y);
}

sf::Sprite GridField::getSprite() const
{
	return m_sprite;
}
