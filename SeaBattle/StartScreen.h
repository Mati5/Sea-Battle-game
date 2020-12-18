#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "Button.h"
#include "Game.h"
#include "SelectCraftWindow.h"

class StartScreen: public IScreen
{
	Button startBtn;

public:
	StartScreen();
	/*implementacja funkcji z interfesju*/
	//void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) override;
	void handleInput(sf::RenderWindow& window, sf::Event event);
	void update() override;
	void render(sf::RenderWindow& window) override;
};

