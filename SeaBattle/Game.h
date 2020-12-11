#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "IScreen.h"
#include "GameScreen.h"
#include "StartScreen.h"

class Game
{
	
private:
	sf::RenderWindow _window;
	bool leftMouseBtnPressed{ false };
	float mouseX;
	float mouseY;

	void processEvents();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void update();
	void render();

public:
	Game();

	/*Wskaünik na interfejs z metodami wirtualnymi*/
	static std::shared_ptr<IScreen> Screen;

	void run();
};