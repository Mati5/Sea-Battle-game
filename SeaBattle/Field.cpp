#include "Field.h"

Field::Field()
{
	m_type = CraftType::zeroMasted;
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

void Field::setCoordinate(int x, int y)
{
	m_coordinate[0] = x * this->getSpaceBetweenField();
	m_coordinate[1] = y * this->getSpaceBetweenField();
}

int Field::getCoordinateX() const
{
	return GridField::getCoordinateX() > 0 ? GridField::getCoordinateX() / GridField::getSpaceBetweenField() : GridField::getCoordinateX();
}

int Field::getCoordinateY() const
{
	return GridField::getCoordinateY() > 0 ? GridField::getCoordinateY() / GridField::getSpaceBetweenField() : GridField::getCoordinateY();
}

sf::RectangleShape Field::renderField() const
{
	sf::RectangleShape shape;
	sf::Vector2f kratkaSize(this->getWidth(), this->getHeight());

	shape.setSize(kratkaSize);
	shape.setFillColor(this->getColor());
	auto x = float(m_coordinate[0]);
	auto y = float(m_coordinate[1]);
	shape.setPosition(x, y);

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

bool Field::hitCraft() const
{
	return int(this->getType()) > 0 && int(this->getType()) < 5;
}