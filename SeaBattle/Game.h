#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Game
{
	
private:
	sf::RenderWindow mWindow;
	Board playerBoard_1;
	Board playerBoard_2;
	bool leftMouseBtnPressed{ false };
	void processEvents();
	void update();
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

public:
	Game();
	void run();

};

