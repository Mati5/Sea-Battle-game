#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "DrawLotsBtn.h"

class Game
{
	
private:
	sf::RenderWindow mWindow;
	Board playerBoard_1;
	Board playerBoard_2;
	DrawLotsBtn playerDrawLotsBtn_1;
	DrawLotsBtn playerDrawLotsBtn_2;
	bool leftMouseBtnPressed{ false };
	bool turn = false;
	void processEvents();
	void update();
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

public:
	Game();
	void run();
	void setTurn(bool turn);
	bool getTurn();

};

