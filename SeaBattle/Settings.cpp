#include "Settings.h"

bool Settings::getShowForbidArea() const
{
    return m_showForbidArea;
}

void Settings::setShowForbidArea(bool showForbidArea)
{
    m_showForbidArea = showForbidArea;
}

int Settings::getQuantityFiveMasthed() const
{
	return m_quantityFiveMasthed;
}

int Settings::getQuantityFourMasthed() const
{
	return m_quantityFourMasthed;
}

int Settings::getQuantityThreeMasthed() const
{
	return m_quantityThreeMasthed;
}

int Settings::getQuantityTwoMasthed() const
{
	return m_quantityTwoMasthed;
}

int Settings::getQuantityOneMasthed() const
{
	return m_quantityOneMasthed;
}

Settings& Settings::get()
{
	static Settings instance;
	return instance;
}
