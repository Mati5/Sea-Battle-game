#pragma once
#include "IScreen.h"
#include "GameSettings.h"

class SelectCraftWindow: public IScreen
{
	/*implementacja funkcji z interfesju*/
	void update(bool leftMouseBtnPressed, float mouseX, float mouseY) override;
	void render(sf::RenderWindow& window) override;
};

