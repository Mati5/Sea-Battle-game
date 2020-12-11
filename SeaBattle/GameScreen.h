#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "Board.h"
#include "GameSettings.h"

class GameScreen: public IScreen
{
	Board playerBoard_1;
	Board playerBoard_2;
	bool leftMouseBtnPressed{ false };
	bool turn = false;

public:
	GameScreen(GameSettings gameSettings);

	/*implementacja funkcji z interfesju*/
	void update(bool leftMouseBtnPressed, float mouseX, float mouseY) override;
	void render(sf::RenderWindow& window) override;

	void setLeftMouseBtnPressed(bool leftMouseBtnPressed);
	
	void setTurn(bool turn);
	bool getTurn();
};

