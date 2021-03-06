#pragma once
#include "CraftType.h"
#include "GridField.h"
#include "Orientation.h"

class Field: public GridField
{
	CraftType m_type;
	int m_spaceBetweenField;
	bool m_checked;
	Orientation m_position;

public:
	Field();

	~Field() override;

	void setType(const CraftType type);

	CraftType getType() const;

	void setChecked(bool checked);

	bool getChecked() const;

	void setSpaceBetweenField(int spaceBetweenField);

	int getSpaceBetweenField() const;

	void setCoordinate(int x, int y) override;

	int getCoordinateX() const override;

	int getCoordinateY() const override;

	bool hitCraft()const;

	void rotateField(const sf::Texture& texture);

	Orientation getPosition() const;
};