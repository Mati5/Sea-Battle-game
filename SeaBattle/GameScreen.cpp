#include "GameScreen.h"

GameScreen::GameScreen(const GameSettings& gameSettings) : 
	m_playerBoard_1{gameSettings.getPlayerBoard_1()},
	m_playerBoard_2{gameSettings.getPlayerBoard_2()},
	m_gameMode{gameSettings.getSelectedGameMode()}
{

}

void GameScreen::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left)
		{
			//Set user turn
			
		}
	}

	m_playerBoard_1.handleInput(event);
	m_playerBoard_2.handleInput(event);
}

void GameScreen::update()
{
	if (m_playerBoard_1.getClickedField().getChecked() && !m_playerBoard_1.getClickedField().hitCraft())
	{
		Field none;
		m_playerBoard_1.setClickedField(none);
		this->setTurn(false);
	}
	if (m_playerBoard_2.getClickedField().getChecked() && !m_playerBoard_2.getClickedField().hitCraft())
	{
		Field none;
		m_playerBoard_2.setClickedField(none);
		this->setTurn(true);
	}
}

void GameScreen::render(sf::RenderWindow& window)
{
	sf::View playerView_1(sf::FloatRect(0.F, 0.F, 1140.F, 680.F));
	playerView_1.setViewport(sf::FloatRect(0.F, 0.F, 1.F, 1.F));

	sf::View playerView_2(sf::FloatRect(0.F, 0.F, 1140.F, 680.F));
	playerView_2.setViewport(sf::FloatRect(0.5F, 0.F, 1.F, 1.F));

	window.clear();

	window.setView(playerView_1);
	m_playerBoard_1.renderBoard(window, m_turn, m_gameMode == GameMode::OneVsAi && true); //!this->getTurn()

	window.setView(playerView_2);
	m_playerBoard_2.renderBoard(window, !m_turn); //this->getTurn() gameMode == GameMode::OneVsAi && true
}

void GameScreen::setTurn(bool turn)
{
	m_turn = turn;
}

bool GameScreen::getTurn() const
{
	return m_turn;
}
