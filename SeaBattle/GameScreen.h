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
	
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	/*implementacja funkcji z interfesju*/
	void processEvents(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;
	
	void setTurn(bool turn);
	bool getTurn();
};

