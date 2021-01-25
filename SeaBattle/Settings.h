#pragma once
#include "GameMode.h"
#include "CraftType.h"

class Settings
{
	bool m_showForbidArea{ true };
	int m_maxCraftField{ 23 };
	int m_currentCraftField{ 20 };
	int m_maxOneMasthed{ 10 };
	int m_maxFiveMasthed{ 2 };
	int m_quantityFiveMasthed{ 0 };
	int m_quantityFourMasthed{ 1 };
	int m_quantityThreeMasthed{ 2 };
	int m_quantityTwoMasthed{ 3 };
	int m_quantityOneMasthed{ 4 };

public:
	bool getShowForbidArea() const;

	void setShowForbidArea(bool showForbidArea);

	int getQuantityFiveMasthed() const;

	int getQuantityFourMasthed() const;

	int getQuantityThreeMasthed() const;

	int getQuantityTwoMasthed() const;

	int getQuantityOneMasthed() const;

	int getMaxCraftField() const;

	int getCurrentCraftField() const;

	void incDecQuantityCraft(CraftType craftType, int number);

	int getMaxOneMasthed() const;

	int getMaxFiveMasthed() const;

	int getQuantityCraft() const;

	static Settings& get();
};

