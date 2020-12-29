#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "Button.h"
#include "Game.h"
#include "SelectCraftWindow.h"

class StartScreen: public IScreen
{
	Button oneVsOneBtn;
	Button oneVsAiBtn;
	Button exitBtn;
	sf::Texture logoTexture;
	sf::Sprite logoSprite;

public:
	StartScreen();
	/*implementacja funkcji z interfesju*/
	void handleInput(sf::RenderWindow& window, const sf::Event& event) override;
	void update(sf::Time deltaTime) override;
	void render(sf::RenderWindow& window) override;
};