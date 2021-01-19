#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "CheckboxBtn.h"
#include "Button.h"
#include "Settings.h"
#include "Game.h"
#include "StartScreen.h"

class SettingsScreen: public IScreen
{
	sf::Texture m_logoTexture;
	sf::Sprite m_logoSprite;
	sf::Text m_tickForbidAreaText;
	sf::Font m_font;
	CheckboxBtn m_tickForbidAreaBtn;
	sf::Texture m_backBtnTexture;
	Button m_backBtn;

public:
	SettingsScreen();
	/*implementacja funkcji z interfesju*/
	void handleInput(sf::RenderWindow& window, const sf::Event& event) override;
	void update(sf::Time deltaTime) override;
	void render(sf::RenderWindow& window) override;
};

