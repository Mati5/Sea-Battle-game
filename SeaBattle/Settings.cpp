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

int Settings::getMaxCraftField() const
{
	return m_maxCraftField;
}

int Settings::getCurrentCraftField() const
{
	return m_currentCraftField;
}

void Settings::incDecQuantityCraft(CraftType craftType, int number)
{
	switch (craftType)
	{
	case CraftType::oneMasted:
		if (m_quantityOneMasthed > 0 || m_quantityOneMasthed == 0 && number > 0)
		{
			m_quantityOneMasthed += number;
			m_currentCraftField += number*(1);
		}
		break;
	case CraftType::twoMasted:
		if (m_quantityTwoMasthed > 0 || m_quantityTwoMasthed == 0 && number > 0)
		{
			m_quantityTwoMasthed += number;
			m_currentCraftField += number*(2);
		}
		break;
	case CraftType::threeMasted:
		if (m_quantityThreeMasthed > 0 || m_quantityThreeMasthed == 0 && number > 0)
		{
			m_quantityThreeMasthed += number;
			m_currentCraftField += number*(3);
		}	
		break;
	case CraftType::fourMasted:
		if (m_quantityFourMasthed > 0 || m_quantityFourMasthed == 0 && number > 0)
		{
			m_quantityFourMasthed += number;
			m_currentCraftField += number*(4);
		}
		break;
	case CraftType::fiveMasted:
		if (m_quantityFiveMasthed > 0 || m_quantityFiveMasthed == 0 && number > 0)
		{
			m_quantityFiveMasthed += number;
			m_currentCraftField += number * (5);
		}
		break;
	}
}

int Settings::getMaxOneMasthed() const
{
	return m_maxOneMasthed;
}

int Settings::getMaxFiveMasthed() const
{
	return m_maxFiveMasthed;
}

int Settings::getQuantityCraft() const
{
	return m_quantityFiveMasthed + m_quantityFourMasthed + m_quantityThreeMasthed + m_quantityTwoMasthed + m_quantityOneMasthed;
}

Settings& Settings::get()
{
	static Settings instance;
	return instance;
}
