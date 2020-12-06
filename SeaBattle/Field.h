#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CraftType.h"
#include "GridField.h"

class Field: public GridField
{
	CraftType type;
	bool checked;


public:
	Field();

	void setType(CraftType type);

	CraftType getType();

	void setChecked(bool checked);

	bool getChecked();

	int getCoordinateX();

	int getCoordinateY();

	sf::RectangleShape renderField();

	bool onClick(float mouseX, float mouseY);

	bool hitCraft();
};

