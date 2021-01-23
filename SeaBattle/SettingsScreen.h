#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "CheckboxBtn.h"
#include "Button.h"
#include "Settings.h"
#include "Game.h"
#include "StartScreen.h"
#include "Text.h"
#include "IncDecBtn.h"

class SettingsScreen: public IScreen
{
	sf::Texture m_logoTexture;
	sf::Sprite m_logoSprite;
	Text m_tickForbidAreaText;
	Text m_fiveMasthedQuantityInfoText;
	Text m_fiveMasthedQuantityText;
	Text m_fourMasthedQuantityInfoText;
	Text m_fourMasthedQuantityText;
	Text m_threeMasthedQuantityInfoText;
	Text m_threeMasthedQuantityText;
	Text m_twoMasthedQuantityInfoText;
	Text m_twoMasthedQuantityText;
	Text m_oneMasthedQuantityInfoText;
	Text m_oneMasthedQuantityText;
	Text m_maxCraftFieldText;
	Text m_currentCraftFieldText;
	Text m_quantityCraftFieldText;

	IncDecBtn m_fiveMasthedIncDecBtn;
	IncDecBtn m_fourMasthedIncDecBtn;
	IncDecBtn m_threeMasthedIncDecBtn;
	IncDecBtn m_twoMasthedIncDecBtn;
	IncDecBtn m_oneMasthedIncDecBtn;

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

