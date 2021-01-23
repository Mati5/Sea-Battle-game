#pragma once
#include "Button.h"

class IncDecBtn
{
	Button m_incButton;
	Button m_decButton;

public:
	IncDecBtn();

	Button getIncButton() const;

	Button getDecButton() const;

	void renderIncDecBtn(sf::RenderWindow& window);

	void setPosition(int x, int y);
};

