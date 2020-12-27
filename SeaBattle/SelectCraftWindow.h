#pragma once
#include "IScreen.h"
#include "GameSettings.h"
#include "BoardPlayer.h"
#include "BoardAi.h"
#include "Button.h"
#include "Game.h"
#include "GameScreen.h"
#include "SelectCraftWindow.h"
#include "Craft.h"

class SelectCraftWindow: public IScreen
{
	GameSettings m_gameSettings;
	BoardPlayer m_boardPlayer;
	BoardAi m_boardAi;
	Button m_randomCraftBtn;
	Button m_nextPlayerBtn;
	Button m_startGameBtn;
	bool m_startGame;
	sf::Texture m_threeMastedTexture;
	Craft m_craft;
	Craft m_selectedCraft;

public:
	SelectCraftWindow();
	/*implementacja funkcji z interfesju*/
	void handleInput(sf::RenderWindow& window, const sf::Event& event) override;
	void update(sf::Time deltaTime) override;
	void render(sf::RenderWindow& window) override;

	void setStartGame(bool startGame);
};