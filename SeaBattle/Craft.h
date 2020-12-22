#pragma once
#include "CraftType.h"
#include "Field.h"

class Craft
{
	Field sprite;
	std::vector<Field> area;
	std::vector<Field> forbidArea;
	std::string orientation; //horizontal/vertical
	CraftType craftType;
	int quantityDestroyedEl;
	

public:
	Craft();

	Field& getSpriteField();

	std::vector<Field> getArea();

	std::vector<Field> getForbidArea();

	void addField(const Field& field);

	void addForbidArea(Field field);

	void setOrientation(std::string orientation);

	std::string getOrientation();

	void setCraftType(CraftType craftType);

	CraftType getCraftType();

	int getCraftTypeNumber(CraftType craftType);

	void setQuantityDestroyedEl(int quantityDestroyedEl);

	int getQuantityDestroyedEl();

	void destroyEl();

	//return true if craft destroyed
	bool checkStateCraft();
};

