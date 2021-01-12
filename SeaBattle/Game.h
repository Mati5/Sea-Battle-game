#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "StartScreen.h"
#include "GameSettings.h"

class Game
{
	
private:
	sf::RenderWindow _window;
	static const sf::Time TimePerFrame;
	sf::Image gameIcon;

	void handleInput();
	void update(sf::Time deltaTime) const;
	void render();

public:
	Game();

	/*Wskaünik na interfejs z metodami wirtualnymi*/
	static std::shared_ptr<IScreen> Screen;

	void run();
};