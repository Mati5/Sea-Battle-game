#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class GridField
{
protected:
	std::vector<int> m_coordinate;
	sf::Color m_color;
	float m_width;
	float m_height;
	int m_spaceBetweenField;
	sf::Sprite m_sprite;

public:
	GridField();

	virtual ~GridField();

	virtual void setCoordinate(int x, int y);

	std::vector<int> getCoordinate() const;

	virtual int getCoordinateX() const;

	virtual int getCoordinateY() const;

	void setColor(sf::Color color);

	sf::Color getColor() const;

	void setWidth(float width);

	float getWidth() const;

	void setHeight(float height);

	float getHeight() const;

	void setSpaceBetweenField(int spaceBetweenField);

	int getSpaceBetweenField() const;

	virtual bool onClick(float mouseX, float mouseY);

	virtual sf::RectangleShape renderField() const;

	void setSprite(const sf::Texture& texture);

	sf::Sprite getSprite() const;
};