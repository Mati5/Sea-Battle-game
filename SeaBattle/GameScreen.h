#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "Board.h"

class GameScreen: public IScreen
{
	Board playerBoard_1;
	Board playerBoard_2;
	DrawLotsBtn playerDrawLotsBtn_1;
	DrawLotsBtn playerDrawLotsBtn_2;
	bool leftMouseBtnPressed{ false };
	bool turn = false;

public:
	
	/*implementacja funkcji z interfesju*/
	void update(bool leftMouseBtnPressed, float mouseX, float mouseY) override;
	void render(sf::RenderWindow& window) override;

	void setLeftMouseBtnPressed(bool leftMouseBtnPressed);
	
	void setTurn(bool turn);
	bool getTurn();
};

