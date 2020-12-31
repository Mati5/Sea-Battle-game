#pragma once
#include "CraftType.h"
#include "Field.h"

class Craft
{
	std::vector<Field> m_area;
	std::vector<Field> m_forbidArea;
	Orientation m_orientation;
	CraftType m_craftType;
	int m_quantityDestroyedEl;
	Field m_craftSprite;
	
public:
	Craft();

	std::vector<Field> getArea() const;

	std::vector<Field> getForbidArea() const;

	void addField(const Field& field);

	void addForbidArea(const Field& field);

	void setOrientation(const Orientation& orientation);

	Orientation getOrientation() const;

	void setCraftType(CraftType craftType);

	CraftType getCraftType() const;

	int getCraftTypeNumber(CraftType craftType) const;

	void setQuantityDestroyedEl(int quantityDestroyedEl);

	int getQuantityDestroyedEl() const;

	void destroyEl();

	//return true if craft destroyed
	bool checkStateCraft() const;

	void setCraftSprite(const Field& craftSprite);

	void setCraftSpriteTexture(const sf::Texture& texture);

	Field& getCraftSprite();

	void clearArea();

	void clearForbidArea();
};