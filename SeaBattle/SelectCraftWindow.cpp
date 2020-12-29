#include "SelectCraftWindow.h"

SelectCraftWindow::SelectCraftWindow() : 
	m_boardView(sf::FloatRect(-60.F, -60.F, 1140.F, 680.F)),
	m_controlView(sf::FloatRect(-60.F, 0.F, 1140.F, 680.F))
{
	m_boardView.setViewport(sf::FloatRect(0.F, 0.0F, 1.F, 1.F));
	m_controlView.setViewport(sf::FloatRect(0.F, 0.8F, 1.F, 1.F));

	m_backBtn.setCoordinate(0, 0);
	m_backBtn.setWidth(160);
	m_backBtn.setHeight(50);
	m_backBtn.loadTexture("../images/back-btn.png");

	m_randomCraftBtn.setCoordinate(200, 0);
	m_randomCraftBtn.setWidth(160);
	m_randomCraftBtn.setHeight(50);
	m_randomCraftBtn.loadTexture("../images/rand-craft-btn.png");
	
	m_nextPlayerBtn.setCoordinate(400, 0);
	m_nextPlayerBtn.setWidth(160);
	m_nextPlayerBtn.setHeight(50);
	m_nextPlayerBtn.loadTexture("../images/next-btn.png");

	m_startGameBtn.setCoordinate(400, 0);
	m_startGameBtn.setWidth(160);
	m_startGameBtn.setHeight(50);
	m_startGameBtn.loadTexture("../images/start-btn.png");

	m_startGame = false;
}

SelectCraftWindow::SelectCraftWindow(GameMode gameMode):
	m_boardView(sf::FloatRect(-60.F, -50.F, 1140.F, 680.F)),
	m_controlView(sf::FloatRect(-60.F, 0.F, 1140.F, 680.F))
{
	m_gameSettings.setSelectedGameMode(gameMode);

	setBackground("../images/bg1.png");

	m_boardView.setViewport(sf::FloatRect(0.F, 0.0F, 1.F, 1.F));
	m_controlView.setViewport(sf::FloatRect(0.F, 0.87F, 1.F, 1.F));

	m_backBtn.setCoordinate(0, 0);
	m_backBtn.setWidth(160);
	m_backBtn.setHeight(50);
	m_backBtn.loadTexture("../images/back-btn.png");

	m_randomCraftBtn.setCoordinate(200, 0);
	m_randomCraftBtn.setWidth(160);
	m_randomCraftBtn.setHeight(50);
	m_randomCraftBtn.loadTexture("../images/rand-craft-btn.png");

	m_nextPlayerBtn.setCoordinate(400, 0);
	m_nextPlayerBtn.setWidth(160);
	m_nextPlayerBtn.setHeight(50);
	m_nextPlayerBtn.loadTexture("../images/next-btn.png");

	m_startGameBtn.setCoordinate(400, 0);
	m_startGameBtn.setWidth(160);
	m_startGameBtn.setHeight(50);
	m_startGameBtn.loadTexture("../images/start-btn.png");

	m_startGame = false;
}

void SelectCraftWindow::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	//Run only when pressed not realese and hold
	if(event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		window.setView(m_controlView);
		setMousePosition(window);
		if (m_backBtn.onClick(mouseX, mouseY))
		{
			Game::Screen = std::make_shared<StartScreen>();
			return;
		}

		if (m_randomCraftBtn.onClick(mouseX, mouseY))
		{
			m_boardPlayer.resetBoard();
			m_boardPlayer.randomCraft(4, 1);
			m_boardPlayer.randomCraft(3, 2);
			m_boardPlayer.randomCraft(2, 3);
			m_boardPlayer.randomCraft(1, 4);
		}

		if (!m_startGame && !m_boardPlayer.getCraftTab().empty() && m_nextPlayerBtn.onClick(mouseX, mouseY))
		{
			switch (m_gameSettings.getSelectedGameMode())
			{
			case GameMode::OneVsOne:
				m_gameSettings.setPlayerBoard_1(m_boardPlayer);
				m_boardPlayer.resetBoard();
				setStartGame(true);
				break;
			case GameMode::OneVsAi:
				m_gameSettings.setPlayerBoard_1(m_boardPlayer);
				m_boardAi.resetBoard();
				m_boardAi.randomCraft(4, 1);
				m_boardAi.randomCraft(3, 2);
				m_boardAi.randomCraft(2, 3);
				m_boardAi.randomCraft(1, 4);
				m_gameSettings.setBoardAi(m_boardAi);
				Game::Screen = std::make_shared<GameScreen>(m_gameSettings);
				break;
			default:
				break;
			}

			return;
		}

		if (m_startGame && !m_boardPlayer.getCraftTab().empty() && m_startGameBtn.onClick(mouseX, mouseY))
		{
			m_gameSettings.setPlayerBoard_2(m_boardPlayer);
			Game::Screen = std::make_shared<GameScreen>(m_gameSettings);
			return;
		}
	}
}

void SelectCraftWindow::update(sf::Time deltaTime)
{

}

void SelectCraftWindow::render(sf::RenderWindow& window)
{
	window.clear();

	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);

	window.setView(m_boardView);
	m_boardPlayer.renderBoard(window, true);

	//Control view buttons
	window.setView(m_controlView);
	window.draw(m_backBtn.getSprite());
	window.draw(m_randomCraftBtn.getSprite());
	if(!m_startGame)
		window.draw(m_nextPlayerBtn.getSprite());
	if (m_startGame)
		window.draw(m_startGameBtn.getSprite());
}

void SelectCraftWindow::setStartGame(bool startGame)
{
	m_startGame = startGame;
}