#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "BoardPlayer.h"
#include "BoardAi.h"
#include "GameSettings.h"
#include<Windows.h>

class GameScreen: public IScreen
{
	BoardPlayer m_playerBoard_1;
	BoardPlayer m_playerBoard_2;
	BoardAi m_boardAi;
	GameMode m_gameMode;
	sf::View playerView_1;
	sf::View playerView_2;
	bool m_turn = false;
	static const float DelayAi;
	float timer;
	sf::Texture m_arrowRightTexture;
	sf::Sprite m_arrowRightSprite;
	sf::Texture m_arrowLeftTexture;
	sf::Sprite m_arrowLeftSprite;

public:
	explicit GameScreen(const GameSettings& gameSettings);

	/*implementacja funkcji z interfesju*/
	void handleInput(sf::RenderWindow& window, const sf::Event& event) override;
	void update(sf::Time deltaTime) override;
	void render(sf::RenderWindow& window) override;
	
	void setTurn(bool turn);
	bool getTurn() const;
};

