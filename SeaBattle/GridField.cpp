#include "GridField.h"

GridField::GridField()
{
	this->coordinate[0] = 10;
	this->coordinate[1] = 10;
	this->color = sf::Color::Red;
	this->width = 20.f;
	this->height = 20.f;
	this->spaceBetweenField = 40;
	this->sprite.setPosition(coordinate[0], coordinate[1]);
}

GridField::GridField(const GridField& gridField)
{
	coordinate[0] = gridField.coordinate[0];
	coordinate[1] = gridField.coordinate[1];
	color = gridField.color;
	width = gridField.width;
	height = gridField.height;
	spaceBetweenField = gridField.spaceBetweenField;
	sprite = gridField.sprite;
}

void GridField::setCoordinate(int x, int y)
{
	this->coordinate[0] = x;
	this->coordinate[1] = y;
	this->sprite.setPosition(x, y);
}

int* GridField::getCoordinate()
{
	return this->coordinate;
}

int GridField::getCoordinateX()
{
	return this->coordinate[0];
}

int GridField::getCoordinateY()
{
	return this->coordinate[1];
}

void GridField::setColor(sf::Color color)
{
	this -> color = color;
}

sf::Color GridField::getColor()
{
	return this->color;
}

void GridField::setWidth(float width)
{
	this->width = width;
}

float GridField::getWidth()
{
	return this->width;
}

void GridField::setHeight(float height)
{
	this->height = height;
}

float GridField::getHeight()
{
	return this->height;
}

void GridField::setSpaceBetweenField(int spaceBetweenField)
{
	this->spaceBetweenField = spaceBetweenField;
}

int GridField::getSpaceBetweenField()
{
	return this->spaceBetweenField;
}

bool GridField::onClick(float mouseX, float mouseY)
{
	int fieldPositionX = this->coordinate[0];
	int fieldPositionY = this->coordinate[1];

	if (mouseX > fieldPositionX && mouseX < fieldPositionX + this->width
		&& mouseY > fieldPositionY && mouseY < fieldPositionY + this->height)
	{
		return true;
	}

	return false;
}

sf::RectangleShape GridField::renderField()
{
	return sf::RectangleShape();
}

void GridField::setSprite(sf::Texture& texture)
{
	this->sprite.setTexture(texture, true);
	this->sprite.setPosition(coordinate[0], coordinate[1]);
}

sf::Sprite GridField::getSprite()
{
	return this->sprite;
}
