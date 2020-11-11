#pragma once
#include "CraftType.h"
#include "Field.h"

class Craft
{
	Field* area;
	CraftType craftType;
	int craftTypeNumber;
	int quantityDestroyedEl;

public:
	void setArea(Field* area);

	Field* getArea();

	void setCraftType(CraftType craftType);

	CraftType getCraftType();

	void setQuantityDestroyedEl(int quantityDestroyedEl);

	int getQuantityDestroyedEl();

	void destroyEl();

	//return true if craft destroyed
	bool checkStateCraft();
};

