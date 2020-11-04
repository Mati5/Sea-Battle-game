#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CraftType.h";

class Field
{
	int coordinate[2];
	CraftType type;
	bool checked;
	sf::Color color;
	float width;
	float height;
	int spaceBetweenField;

public:
	Field();

	void setCoordinate(int x, int y);

	int* getCoordinate();

	void setType(CraftType type);

	CraftType getType();

	void setChecked(bool checked);

	bool getChecked();

	void setColor(sf::Color color);

	sf::Color getColor();

	void setWidth(float width);

	float getWidth();

	void setHeight(float height);

	float getHeight();

	void setSpaceBetweenField(int spaceBetweenField);

	int getSpaceBetweenField();

	sf::RectangleShape renderField();

	bool onClick(float mouseX, float mouseY);

	bool hitCraft();
};

