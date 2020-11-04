#include "Field.h"



Field::Field()
{
	this->coordinate[0] = 0;
	this->coordinate[1] = 0;
	this->type = CraftType::zeroMasted;
	this->checked = false;
	this->width = 20.f;
	this->height = 20.f;
	this->spaceBetweenField = 40;
}

void Field::setCoordinate(int x, int y)
{
	this->coordinate[0] = x * this->getSpaceBetweenField();
	this->coordinate[1] = y * this->getSpaceBetweenField();;
}

int* Field::getCoordinate()
{
	return coordinate;
}

void Field::setType(CraftType type)
{
	this->type = type;
}

CraftType Field::getType()
{
	return this->type;
}

void Field::setChecked(bool checked)
{
	this->checked = checked;
}

bool Field::getChecked()
{
	return this->checked;
}

void Field::setColor(sf::Color color)
{
	this->color = color;
}

sf::Color Field::getColor()
{
	return this->color;
}

void Field::setWidth(float width)
{
	this->width = width;
}

float Field::getWidth()
{
	return this->width;
}

void Field::setHeight(float height)
{
	this->height = height;
}

float Field::getHeight()
{
	return this->height;
}

void Field::setSpaceBetweenField(int spaceBetweenSpace)
{
	this->spaceBetweenField = spaceBetweenField;
}

int Field::getSpaceBetweenField()
{
	return this->spaceBetweenField;
}

sf::RectangleShape Field::renderField()
{
	sf::RectangleShape shape;
	sf::Vector2f kratkaSize(this->getWidth(), this->getHeight());

	shape.setSize(kratkaSize);
	shape.setFillColor(this->getColor());
	shape.setPosition(this->getCoordinate()[0], this->getCoordinate()[1]);

	return shape;
}

bool Field::onClick(float mouseX, float mouseY)
{
	float fieldPositionX = this->getCoordinate()[0];
	float fieldPositionY = this->getCoordinate()[1];

	if (!this->getChecked() && mouseX > fieldPositionX && mouseX < fieldPositionX+this->getWidth()
		&& mouseY > fieldPositionY && mouseY<fieldPositionY+this->getHeight()) 
	{
		std::cout << "clicked field: " << this->getCoordinate()[1] / this->getSpaceBetweenField() << " " << this->getCoordinate()[0] / this->getSpaceBetweenField() << std::endl;
		this->setColor(sf::Color::White);
		this->setChecked(true);

		if (this->hitCraft()) {
			std::cout << "You hit a craft" << std::endl;
			std::cout << int(this->getType())<<std::endl;
			this->setColor(sf::Color::Blue);
		}

		return true;
	}

	return false;
}

bool Field::hitCraft()
{
	return int(this->getType()) > 0 && int(this->getType()) < 5;
}