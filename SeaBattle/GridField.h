#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class GridField
{
protected:
	int coordinate[2];
	sf::Color color;
	float width;
	float height;
	int spaceBetweenField;
	sf::Sprite sprite;

public:
	GridField();
	
	GridField(const GridField& gridField);

	void setCoordinate(int x, int y);

	int* getCoordinate();

	int getCoordinateX();

	int getCoordinateY();

	void setColor(sf::Color color);

	sf::Color getColor();

	void setWidth(float width);

	float getWidth();

	void setHeight(float height);

	float getHeight();

	void setSpaceBetweenField(int spaceBetweenField);

	int getSpaceBetweenField();

	virtual bool onClick(float mouseX, float mouseY);

	virtual sf::RectangleShape renderField();

	void setSprite(sf::Texture& texture);

	sf::Sprite getSprite();
};