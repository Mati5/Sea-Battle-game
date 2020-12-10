#pragma once
#include "IScreen.h"
#include "GameSettings.h"
#include "Board.h"

class SelectCraftWindow: public IScreen
{
	Board board;

public:
	/*implementacja funkcji z interfesju*/
	void update(bool leftMouseBtnPressed, float mouseX, float mouseY) override;
	void render(sf::RenderWindow& window) override;
};

