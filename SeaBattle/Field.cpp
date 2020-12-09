#include "Field.h"

Field::Field()
{
	this->type = CraftType::zeroMasted;
	this->checked = false;
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

void Field::setCoordinate(int x, int y)
{
	this->coordinate[0] = x * this->getSpaceBetweenField();
	this->coordinate[1] = y * this->getSpaceBetweenField();
}

int Field::getCoordinateX()
{
	return GridField::getCoordinateX() > 0 ? GridField::getCoordinateX() / GridField::getSpaceBetweenField() : GridField::getCoordinateX();
}

int Field::getCoordinateY()
{
	return GridField::getCoordinateY() > 0 ? GridField::getCoordinateY() / GridField::getSpaceBetweenField() : GridField::getCoordinateY();
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
	if (!this->getChecked() && GridField::onClick(mouseX, mouseY)) 
	{
		std::cout << "clicked field: " << this->getCoordinate()[1] / this->getSpaceBetweenField() << " " << this->getCoordinate()[0] / this->getSpaceBetweenField() << std::endl;
		
		this->setColor(sf::Color::White);
		this->setChecked(true);

		if (this->hitCraft()) {
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