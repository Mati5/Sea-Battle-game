#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "Button.h"
#include "Game.h"
#include "SelectCraftWindow.h"

class StartScreen: public IScreen
{
	Button m_oneVsOneBtn;
	Button m_oneVsAiBtn;
	Button m_settingsBtn;
	Button m_exitBtn;
	sf::Texture m_logoTexture;
	sf::Sprite m_logoSprite;

public:
	StartScreen();
	/*implementacja funkcji z interfesju*/
	void handleInput(sf::RenderWindow& window, const sf::Event& event) override;
	void update(sf::Time deltaTime) override;
	void render(sf::RenderWindow& window) override;
};