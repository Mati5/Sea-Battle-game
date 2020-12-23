#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CraftType.h"
#include "GridField.h"

class Field: public GridField
{
	CraftType m_type;
	bool m_checked{false};

public:
	Field();

	~Field() override;

	void setType(const CraftType type);

	CraftType getType() const;

	void setChecked(bool checked);

	bool getChecked() const;

	void setCoordinate(int x, int y) override;

	int getCoordinateX() const override;

	int getCoordinateY() const override;

	sf::RectangleShape renderField() const override;

	bool onClick(float mouseX, float mouseY) override;

	bool hitCraft()const;
};

