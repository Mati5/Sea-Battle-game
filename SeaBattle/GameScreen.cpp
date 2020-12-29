#include "GameScreen.h"

const float GameScreen::DelayAi = 1.5;

GameScreen::GameScreen(const GameSettings& gameSettings) :
	m_playerBoard_1{ gameSettings.getPlayerBoard_1() },
	m_playerBoard_2{ gameSettings.getPlayerBoard_2() },
	m_boardAi{ gameSettings.getBoardAi() },
	m_gameMode{ gameSettings.getSelectedGameMode() },
	m_playerView_1(sf::FloatRect(-36.F, -50.F, 1140.F, 680.F)),
	m_playerView_2(sf::FloatRect(-36.F, -50.F, 1140.F, 680.F)),
	m_bottomView(sf::FloatRect(0.F, 0.F, 1140.F, 680.F))
{
	setBackground("../images/bg1.png");
	m_playerView_1.setViewport(sf::FloatRect(0.F, 0.F, 1.F, 1.F));
	m_playerView_2.setViewport(sf::FloatRect(0.5F, 0.F, 1.F, 1.F));
	m_bottomView.setViewport(sf::FloatRect(0.0F, 0.85F, 1.F, 1.F));

	m_timer = DelayAi;

	if (!m_arrowRightTexture.loadFromFile("../images/arrow-right.png"))
		std::cout << "Error load craft texture!" << std::endl;

	if (!m_arrowLeftTexture.loadFromFile("../images/arrow-left.png"))
		std::cout << "Error load craft texture!" << std::endl;
	
	m_arrowSprite.setTexture(m_arrowRightTexture);
	m_arrowSprite.setPosition((windowWidth - 55) / 2, (windowHeight - 110) / 2);

	if (!m_playerOneWinTexture.loadFromFile("../images/player-1-win.png"))
		std::cout << "Error load craft texture!" << std::endl;
	
	if (!m_playerTwoWinTexture.loadFromFile("../images/player-2-win.png"))
		std::cout << "Error load craft texture!" << std::endl;
	
	m_playerWinSprite.setPosition((windowWidth - m_playerOneWinTexture.getSize().x) / 2, 0);

	m_homeBtn.setWidth(160);
	m_homeBtn.setHeight(50);
	m_homeBtn.setCoordinate(int(windowWidth / 2 - m_homeBtn.getWidth() / 2), 40);
	m_homeBtn.loadTexture("../images/back-btn.png");
}

void GameScreen::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	setMousePosition(window);
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		if (m_homeBtn.onClick(mouseX, mouseY))
		{
			Game::Screen = std::make_shared<StartScreen>();
			return;
		}
	}

	window.setView(m_playerView_1);
	if(!m_endGame && m_turn)
	{
		switch (m_gameMode)
		{
		case GameMode::OneVsOne:
			m_playerBoard_1.handleInput(window);
			break;
		case GameMode::OneVsAi:
			
			break;
		default:
			break;
		}
	}

	window.setView(m_playerView_2);
	if (!m_endGame && !m_turn)
	{
		switch (m_gameMode)
		{
		case GameMode::OneVsOne:
			m_playerBoard_2.handleInput(window);
				break;
		case GameMode::OneVsAi:
			m_boardAi.handleInput(window);
			break;
		default:
			break;
		}
	}	
}

void GameScreen::update(sf::Time deltaTime)
{
	if (m_gameMode == GameMode::OneVsAi && m_turn)
		m_timer -= deltaTime.asSeconds();

	if (m_playerBoard_1.getClickedField().getChecked() && !m_playerBoard_1.getClickedField().hitCraft())
	{
		Field none;
		m_playerBoard_1.setClickedField(none);
		this->setTurn(false);
		m_arrowSprite.setTexture(m_arrowRightTexture);
	}

	if (m_playerBoard_2.getClickedField().getChecked() && !m_playerBoard_2.getClickedField().hitCraft())
	{
		Field none;
		m_playerBoard_2.setClickedField(none);
		this->setTurn(true);
		m_arrowSprite.setTexture(m_arrowLeftTexture);
	}

	//Player tick Field on Ai Board
	if (m_boardAi.getClickedField().getChecked() && !m_boardAi.getClickedField().hitCraft())
	{
		Field none;
		m_boardAi.setClickedField(none);
		this->setTurn(true);
		m_arrowSprite.setTexture(m_arrowLeftTexture);
	}

	//Player2 win
	if (m_playerBoard_1.getBoardStats() == 20)
	{
		m_endGame = true;
		m_playerWinSprite.setTexture(m_playerTwoWinTexture);
	}

	//Player1 win
	if (m_playerBoard_2.getBoardStats() == 20)
	{
		m_endGame = true;
		m_playerWinSprite.setTexture(m_playerOneWinTexture);
	}

	//Player1 win
	if (m_boardAi.getBoardStats() == 20)
	{
		m_endGame = true;
		m_playerWinSprite.setTexture(m_playerOneWinTexture);
	}

	//Ai action
	if (m_timer<=0 && m_gameMode == GameMode::OneVsAi && m_turn)
	{
		Field selectedField = m_boardAi.action(m_playerBoard_1.getFieldTab(), m_playerBoard_1.getCraftTab());
		m_timer = DelayAi;
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

	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);
	window.draw(m_arrowSprite);

	window.setView(m_playerView_1);
	m_playerBoard_1.renderBoard(window, m_gameMode == GameMode::OneVsAi && true);

	window.setView(m_playerView_2);
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

	window.setView(m_bottomView);
	if (m_endGame)
	{
		window.draw(m_playerWinSprite);
	}
	window.draw(m_homeBtn.getSprite());
}

void GameScreen::setTurn(bool turn)
{
	m_turn = turn;
}

bool GameScreen::getTurn() const
{
	return m_turn;
}