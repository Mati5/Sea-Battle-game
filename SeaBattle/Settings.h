#pragma once
#include "GameMode.h"

class Settings
{
	bool m_showForbidArea{ true };
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

	static Settings& get();
};

