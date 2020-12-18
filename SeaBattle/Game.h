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

	void handleInput();
	void update();
	void render();

public:
	Game();

	/*Wskaünik na interfejs z metodami wirtualnymi*/
	static std::shared_ptr<IScreen> Screen;

	void run();
};