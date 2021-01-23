#pragma once
#include "IScreen.h"
#include "GameSettings.h"
#include "BoardPlayer.h"
#include "BoardAi.h"
#include "Button.h"
#include "GameScreen.h"
#include "SetCraftTab.h"

class SelectCraftWindow: public IScreen 
{
	GameSettings m_gameSettings;
	BoardPlayer m_boardPlayer;
	BoardAi m_boardAi;
	Button m_randomCraftBtn;
	Button m_nextPlayerBtn;
	Button m_startGameBtn;
	Button m_backBtn;
	sf::View m_boardView;
	sf::View m_controlView;
	bool m_startGame;
	std::vector<Craft> m_craftToSetOnMap;
	int m_quantitySetCraft{ 0 };

	sf::Texture m_fiveMasthedTexture;
	sf::Texture m_fiveMasthedVTexture;
	
	sf::Texture m_fourMasthedTexture;
	sf::Texture m_fourMasthedVTexture;

	sf::Texture m_threeMasthedTexture;
	sf::Texture m_threeMasthedVTexture;

	sf::Texture m_twoMasthedTexture;
	sf::Texture m_twoMasthedVTexture;

	sf::Texture m_oneMasthedTexture;

public:
	SelectCraftWindow();
	SelectCraftWindow(GameMode gameMode);
	/*implementacja funkcji z interfesju*/
	void handleInput(sf::RenderWindow& window, const sf::Event& event) override;
	void update(sf::Time deltaTime) override;
	void render(sf::RenderWindow& window) override;

	void setStartGame(bool startGame);
};