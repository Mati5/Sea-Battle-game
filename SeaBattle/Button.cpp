#include "Button.h"

Button::Button()
{
	m_width = 100;
	m_height = 50;
	m_color = sf::Color::Red;
	m_coordinate[0] = 20;
	m_coordinate[1] = 20;
}


sf::RectangleShape Button::renderField() const
{
	sf::RectangleShape shape;
	sf::Vector2f kratkaSize(m_width, m_height);

	shape.setSize(kratkaSize);
	shape.setFillColor(m_color);
	auto x = float(m_coordinate[0]);
	auto y = float(m_coordinate[1]);
	shape.setPosition(x, y);

	return shape;
}