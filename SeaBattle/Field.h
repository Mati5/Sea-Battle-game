#pragma once
#include <SFML/Graphics.hpp>

class Field
{
	int coordinate[2];
	char* type;
	bool checked;
	sf::Color color;
	float width;
	float height;
	int spaceBetweenField;

public:
	Field();

	void setCoordinate(int x, int y);

	int* getCoordinate();

	void setType(char* type);

	char* getType();

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
};

