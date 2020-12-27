#include "GameScreen.h"

const float GameScreen::DelayAi = 1.5;

GameScreen::GameScreen(const GameSettings& gameSettings) :
	m_playerBoard_1{ gameSettings.getPlayerBoard_1() },
	m_playerBoard_2{ gameSettings.getPlayerBoard_2() },
	m_boardAi{ gameSettings.getBoardAi() },
	m_gameMode{ gameSettings.getSelectedGameMode() },
	playerView_1(sf::FloatRect(0.F, 0.F, 1140.F, 680.F)),
	playerView_2(sf::FloatRect(0.F, 0.F, 1140.F, 680.F))

{
	playerView_1.setViewport(sf::FloatRect(0.F, 0.F, 1.F, 1.F));
	playerView_2.setViewport(sf::FloatRect(0.5F, 0.F, 1.F, 1.F));
	timer = DelayAi;
}

void GameScreen::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	float mouseX = IScreen::mouseX;
	float mouseY = IScreen::mouseY;

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left)
		{
			//Set user turn
			
		}
	}

	window.setView(playerView_1);
	if(m_turn)
	{
		switch (m_gameMode)
		{
		case GameMode::OneVsOne:
			m_playerBoard_1.handleInput(window, event);
			break;
		case GameMode::OneVsAi:
			
			break;
		default:
			break;
		}
	}

	window.setView(playerView_2);
	if (!m_turn)
	{
		switch (m_gameMode)
		{
		case GameMode::OneVsOne:
			m_playerBoard_2.handleInput(window, event);
				break;
		case GameMode::OneVsAi:
			m_boardAi.handleInput(window, event);
			break;
		default:
			break;
		}
		
	}	
}

void GameScreen::update(sf::Time deltaTime)
{
	if (m_gameMode == GameMode::OneVsAi && m_turn)
		timer -= deltaTime.asSeconds();


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

	//Player tick Field on Ai Board
	if (m_boardAi.getClickedField().getChecked() && !m_boardAi.getClickedField().hitCraft())
	{
		Field none;
		m_boardAi.setClickedField(none);
		this->setTurn(true);
	}

	//Ai action
	if (timer<=0 && m_gameMode == GameMode::OneVsAi && m_turn)
	{
		Field selectedField = m_boardAi.action(m_playerBoard_1.getFieldTab(), m_playerBoard_1.getCraftTab());
		timer = DelayAi;
		m_playerBoard_1.tickField(selectedField);
		int craftIndex = m_playerBoard_1.getCraft(m_playerBoard_1.getCraftTab(), selectedField);
		if (craftIndex >= 0 && m_playerBoard_1.getCraftTab()[craftIndex].checkStateCraft())
		{
			//delete forbid element from available field
			m_boardAi.delForbidAvailableField(m_playerBoard_1.getCraftTab()[craftIndex].getForbidArea());

			//delete element from hitCraftTab
			m_boardAi.clearHitCraftTab();
		}
	}
}

void GameScreen::render(sf::RenderWindow& window)
{
	window.clear();

	window.setView(playerView_1);
	m_playerBoard_1.renderBoard(window);

	window.setView(playerView_2);
	switch (m_gameMode)
	{
	case GameMode::OneVsOne:
		m_playerBoard_2.renderBoard(window);
		break;
	case GameMode::OneVsAi:
		m_boardAi.renderBoard(window);
		break;
	default:
		break;
	}
	
}

void GameScreen::setTurn(bool turn)
{
	m_turn = turn;
}

bool GameScreen::getTurn() const
{
	return m_turn;
}
