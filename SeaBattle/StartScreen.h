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
	void update(bool leftMouseBtnPressed, float mouseX, float mouseY) override;
	void render(sf::RenderWindow& window) override;
};
