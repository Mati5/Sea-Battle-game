#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "Board.h"
#include "GameSettings.h"

class GameScreen: public IScreen
{
	Board m_playerBoard_1;
	Board m_playerBoard_2;
	GameMode m_gameMode;
	bool m_turn = false;

public:
	explicit GameScreen(const GameSettings& gameSettings);

	/*implementacja funkcji z interfesju*/
	void handleInput(sf::RenderWindow& window, const sf::Event& event) override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	
	void setTurn(bool turn);
	bool getTurn() const;
};

