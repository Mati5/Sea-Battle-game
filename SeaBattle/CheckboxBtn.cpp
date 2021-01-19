#include "CheckboxBtn.h"

CheckboxBtn::CheckboxBtn():GridField()
{
	m_width = 45;
	m_height = 45;
	m_isChecked = false;
	loadTexture("../images/field.png");

	if (!m_checkedTexture.loadFromFile("../images/checked.png"))
		std::cout << "Error load craft texture!" << std::endl;
}

CheckboxBtn::CheckboxBtn(bool isChecked):m_isChecked(isChecked)
{
	m_width = 45;
	m_height = 45;
	loadTexture("../images/field.png");

	if (!m_checkedTexture.loadFromFile("../images/checked.png"))
		std::cout << "Error load craft texture!" << std::endl;

	checkIsChecked();
}

void CheckboxBtn::setChecked(bool isChecked)
{
	m_isChecked = isChecked;
}

bool CheckboxBtn::getChecked() const
{
	return m_isChecked;
}

void CheckboxBtn::checkIsChecked()
{
	if (m_isChecked)
		m_sprite.setTexture(m_checkedTexture);
	else
		m_sprite.setTexture(m_texture);
}

void CheckboxBtn::updateCoordinate()
{
	auto x = float(m_coordinate[0]);
	auto y = float(m_coordinate[1]);

	m_sprite.setPosition(x, y);
}
