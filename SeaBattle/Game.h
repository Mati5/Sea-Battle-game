#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "DrawLotsBtn.h"
#include "IScreen.h"
#include "GameScreen.h"

class Game
{
	
private:
	sf::RenderWindow _window;
	static const sf::Time TimePerFrame;

	void processEvents();
	void update(sf::Time delta);
	void render();
	void handleInput();

public:
	Game();

	/*Wskaünik na interfejs z metodami wirtualnymi*/
	static std::shared_ptr<IScreen> Screen;

	void run();
};