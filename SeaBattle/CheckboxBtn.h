#pragma once
#include "GridField.h"

class CheckboxBtn: public GridField
{
	bool m_isChecked;
	sf::Texture m_checkedTexture;

public:
	CheckboxBtn();

	CheckboxBtn(bool isChecked);

	void setChecked(bool isChecked);

	bool getChecked() const;

	void checkIsChecked();

	void updateCoordinate();
};