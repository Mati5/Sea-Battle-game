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

	if (!m_fiveMasthedTexture.loadFromFile("../images/five-masthed.png"))
		std::cout << "Error load texture" << std::endl;

	if (!m_fiveMasthedVTexture.loadFromFile("../images/five-masthed-vertical.png"))
		std::cout << "Error load texture" << std::endl;

	if (!m_fourMasthedTexture.loadFromFile("../images/four-masthed.png"))
		std::cout << "Error load texture" << std::endl;

	if (!m_fourMasthedVTexture.loadFromFile("../images/four-masthed-vertical.png"))
		std::cout << "Error load texture" << std::endl;

	if (!m_threeMasthedTexture.loadFromFile("../images/three-masthed.png"))
		std::cout << "Error load texture" << std::endl;

	if (!m_threeMasthedVTexture.loadFromFile("../images/three-masthed-vertical.png"))
		std::cout << "Error load texture" << std::endl;

	if (!m_twoMasthedTexture.loadFromFile("../images/two-masthed.png"))
		std::cout << "Error load texture" << std::endl;

	if (!m_twoMasthedVTexture.loadFromFile("../images/two-masthed-vertical.png"))
		std::cout << "Error load texture" << std::endl;

	if (!m_oneMasthedTexture.loadFromFile("../images/one-masthed.png"))
		std::cout << "Error load texture" << std::endl;

	m_boardPlayer.setCraftTab(m_fiveMasthedTexture, m_fourMasthedTexture, m_threeMasthedTexture, m_twoMasthedTexture, m_oneMasthedTexture);
	m_craftToSetOnMap = m_boardPlayer.getCraftTab();
}

void SelectCraftWindow::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	window.setView(m_boardView);
	setMousePosition(window);
	for (int i = 0; i < m_boardPlayer.getCraftTab().size(); i++)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right)
		{
			Craft craft = m_boardPlayer.getCraftTab()[i];
			Field craftSprite = craft.getCraftSprite();
			
			if (craftSprite.getChecked())
			{
				if (craftSprite.getPosition() == Orientation::Vertical)
				{
					switch (craft.getCraftType())
					{
					case CraftType::fiveMasted:
						craftSprite.rotateField(m_fiveMasthedTexture);
						break;
					case CraftType::fourMasted:
						craftSprite.rotateField(m_fourMasthedTexture);
						break;
					case CraftType::threeMasted:
						craftSprite.rotateField(m_threeMasthedTexture);
						break;
					case CraftType::twoMasted:
						craftSprite.rotateField(m_twoMasthedTexture);
						break;
					case CraftType::oneMasted:
						craftSprite.rotateField(m_oneMasthedTexture);
						break;
					default:
						break;
					}
				}
				else
				{
					switch (craft.getCraftType())
					{
					case CraftType::fiveMasted:
						craftSprite.rotateField(m_fiveMasthedVTexture);
						break;
					case CraftType::fourMasted:
						craftSprite.rotateField(m_fourMasthedVTexture);
						break;
					case CraftType::threeMasted:
						craftSprite.rotateField(m_threeMasthedVTexture);
						break;
					case CraftType::twoMasted:
						craftSprite.rotateField(m_twoMasthedVTexture);
						break;
					case CraftType::oneMasted:
						craftSprite.rotateField(m_oneMasthedTexture);
						break;
					default:
						break;
					}
				}	
			}

			craft.setCraftSprite(craftSprite);
			m_boardPlayer.updateCraftTab(i, craft);
		}

		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
		{
			Craft craft = m_boardPlayer.getCraftTab()[i];
			Field craftSprite = craft.getCraftSprite();

			if (craftSprite.onClick(mouseX, mouseY))
			{
				if (craftSprite.getChecked())
				{
					craftSprite.setChecked(false);

					if (craftSprite.getCoordinateX() >= 0 && craftSprite.getCoordinateX() <= 9 &&
						craftSprite.getCoordinateY() >= 0 && craftSprite.getCoordinateY() <= 9)
					{
						bool allowCraft = true;
						switch (craftSprite.getPosition())
						{
						case Orientation::Horizontal:
							m_boardPlayer.checkWEDirection(craftSprite.getCoordinateY(), craftSprite.getCoordinateX(), int(craft.getCraftType()), allowCraft, 1);
							break;
						case Orientation::Vertical:
							m_boardPlayer.checkNSDirection(craftSprite.getCoordinateY(), craftSprite.getCoordinateX(), int(craft.getCraftType()), allowCraft, 1);
							break;
						default:
							break;
						}

						if (allowCraft)
						{
							switch (craftSprite.getPosition())
							{
							case Orientation::Horizontal:
								m_boardPlayer.setCraftOnMap(Direction::E, craft, i);
								break;
							case Orientation::Vertical:
								m_boardPlayer.setCraftOnMap(Direction::S, craft, i);
								break;
							default:
								break;
							}
							m_quantitySetCraft++;
						}

						if(!allowCraft)
							craftSprite.setChecked(true);
					}
				}
				else
				{
					craftSprite.setChecked(true);

					if (craftSprite.getChecked() && craftSprite.getCoordinateX() >= 0 && craftSprite.getCoordinateX() <= 9 &&
						craftSprite.getCoordinateY() >= 0 && craftSprite.getCoordinateY() <= 9)
					{
						m_boardPlayer.delCraft(i);
						craft.clearArea();
						craft.clearForbidArea();
						m_quantitySetCraft--;
						m_craftToSetOnMap.push_back(craft);
					}
				}
			}

			craft.setCraftSprite(craftSprite);
			m_boardPlayer.updateCraftTab(i, craft);
		}
	}

	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
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
			/*if (m_craftToSetOnMap.size() < 10) {
				for (int i = 0; i < m_craftToSetOnMap.size(); i++)
				{
					m_boardPlayer.randomCraft(int(m_craftToSetOnMap[i].getCraftType()));
				}
				m_craftToSetOnMap.clear();
				m_boardPlayer.clearCraftTab();
			}
			else
			{*/
				m_boardPlayer.resetBoard();
				m_boardPlayer.randomCraft(5, Settings::get().getQuantityFiveMasthed());
				m_boardPlayer.randomCraft(4, Settings::get().getQuantityFourMasthed());
				m_boardPlayer.randomCraft(3, Settings::get().getQuantityThreeMasthed());
				m_boardPlayer.randomCraft(2, Settings::get().getQuantityTwoMasthed());
				m_boardPlayer.randomCraft(1, Settings::get().getQuantityOneMasthed());
			//}
			
			m_quantitySetCraft = m_boardPlayer.getCraftTab().size();
		}

		if (m_quantitySetCraft == m_boardPlayer.getCraftTab().size() && !m_startGame && !m_boardPlayer.getCraftTab().empty() && m_nextPlayerBtn.onClick(mouseX, mouseY))
		{
			m_quantitySetCraft = 0;
			switch (m_gameSettings.getSelectedGameMode())
			{
			case GameMode::OneVsOne:
				m_gameSettings.setPlayerBoard_1(m_boardPlayer);
				m_boardPlayer.resetBoard();
				m_boardPlayer.setCraftTab(m_fiveMasthedTexture, m_fourMasthedTexture, m_threeMasthedTexture, m_twoMasthedTexture, m_oneMasthedTexture);
				setStartGame(true);
				break;
			case GameMode::OneVsAi:
				m_gameSettings.setPlayerBoard_1(m_boardPlayer);
				m_boardAi.resetBoard();
				m_boardAi.randomCraft(5, Settings::get().getQuantityFiveMasthed());
				m_boardAi.randomCraft(4, Settings::get().getQuantityFourMasthed());
				m_boardAi.randomCraft(3, Settings::get().getQuantityThreeMasthed());
				m_boardAi.randomCraft(2, Settings::get().getQuantityTwoMasthed());
				m_boardAi.randomCraft(1, Settings::get().getQuantityOneMasthed());
				m_gameSettings.setBoardAi(m_boardAi);
				Game::Screen = std::make_shared<GameScreen>(m_gameSettings);
				break;
			default:
				break;
			}

			return;
		}

		if (m_quantitySetCraft == m_boardPlayer.getCraftTab().size() && m_startGame && !m_boardPlayer.getCraftTab().empty() && m_startGameBtn.onClick(mouseX, mouseY))
		{
			m_gameSettings.setPlayerBoard_2(m_boardPlayer);
			Game::Screen = std::make_shared<GameScreen>(m_gameSettings);
			return;
		}
	}
	window.setView(m_boardView);
}

void SelectCraftWindow::update(sf::Time deltaTime)
{
	for (int i = 0; i < m_boardPlayer.getCraftTab().size(); i++)
	{
		Craft craft = m_boardPlayer.getCraftTab()[i];

		if (craft.getCraftSprite().getChecked())
		{
			auto x = int(mouseX) / craft.getCraftSprite().getSpaceBetweenField();
			auto y = int(mouseY) / craft.getCraftSprite().getSpaceBetweenField();

			craft.getCraftSprite().setCoordinate(x, y);
		}

		m_boardPlayer.updateCraftTab(i, craft);
	}
}

void SelectCraftWindow::render(sf::RenderWindow& window)
{
	window.clear();

	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);
	
	window.setView(m_boardView);
	m_boardPlayer.renderBoard(window, true);

	for (int i = 0; i < m_boardPlayer.getCraftTab().size(); i++)
	{
		window.draw(m_boardPlayer.getCraftTab()[i].getCraftSprite().getSprite());
	}

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