#pragma once
#include "CraftType.h"
#include "Field.h"

class Craft
{
	std::vector<Field> m_area;
	std::vector<Field> m_forbidArea;
	std::string m_orientation; //horizontal/vertical
	CraftType m_craftType;
	int m_quantityDestroyedEl;
	
public:
	Craft();

	std::vector<Field> getArea() const;

	std::vector<Field> getForbidArea() const;

	void addField(const Field& field);

	void addForbidArea(const Field& field);

	void setOrientation(const std::string& orientation);

	std::string getOrientation() const;

	void setCraftType(CraftType craftType);

	CraftType getCraftType() const;

	int getCraftTypeNumber(CraftType craftType) const;

	void setQuantityDestroyedEl(int quantityDestroyedEl);

	int getQuantityDestroyedEl() const;

	void destroyEl();

	//return true if craft destroyed
	bool checkStateCraft() const;
};