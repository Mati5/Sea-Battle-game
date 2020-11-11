#include "DrawLotsBtn.h"

sf::RectangleShape DrawLotsBtn::renderField()
{
	sf::RectangleShape shape;
	sf::Vector2f kratkaSize(this->width, this->height);

	shape.setSize(kratkaSize);
	shape.setFillColor(this->color);
	shape.setPosition(this->coordinate[0], this->coordinate[1]);

	return shape;
}
