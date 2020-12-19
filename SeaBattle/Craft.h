#pragma once
#include "CraftType.h"
#include "Field.h"

class Craft
{
	Field sprite;
	std::vector<std::vector<Field>> area;
	std::vector<Field> forbidArea;
	CraftType craftType;
	int craftTypeNumber;
	int quantityDestroyedEl=0;
	

public:
	Craft();



	Field& getSpriteField();

	std::vector<std::vector<Field>> getArea();

	std::vector<Field> getForbidArea();

	void addField(Field field);

	void addForbidArea(Field field);

	void setCraftType(CraftType craftType);

	CraftType getCraftType();

	int getCraftTypeNumber(CraftType craftType);

	void setQuantityDestroyedEl(int quantityDestroyedEl);

	int getQuantityDestroyedEl();

	void destroyEl();

	//return true if craft destroyed
	bool checkStateCraft();
};

