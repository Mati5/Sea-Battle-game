#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "BoardPlayer.h"
#include "BoardAi.h"
#include "GameSettings.h"
#include "Button.h"
#include "StartScreen.h"

class GameScreen: public IScreen
{
	BoardPlayer m_playerBoard_1;
	BoardPlayer m_playerBoard_2;
	BoardAi m_boardAi;
	GameMode m_gameMode;
	sf::View m_playerView_1;
	sf::View m_playerView_2;
	sf::View m_bottomView;
	bool m_turn = false;
	bool m_endGame = false;
	static const float DelayAi;
	float m_timer;
	sf::Texture m_arrowRightTexture;
	sf::Texture m_arrowLeftTexture;
	sf::Sprite m_arrowSprite;

	sf::Texture m_playerOneWinTexture;
	sf::Texture m_playerTwoWinTexture;
	sf::Sprite m_playerWinSprite;
	Button m_homeBtn;

public:
	explicit GameScreen(const GameSettings& gameSettings);

	/*implementacja funkcji z interfesju*/
	void handleInput(sf::RenderWindow& window, const sf::Event& event) override;
	void update(sf::Time deltaTime) override;
	void render(sf::RenderWindow& window) override;
	
	void setTurn(bool turn);
	bool getTurn() const;
};

