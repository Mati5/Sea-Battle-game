#include "SelectCraftWindow.h"



SelectCraftWindow::SelectCraftWindow()
{
	m_randomCraftBtn.setCoordinate(50, 400);
	
	m_nextPlayerBtn.setCoordinate(400, 400);
	m_nextPlayerBtn.setColor(sf::Color::Green);

	m_startGameBtn.setCoordinate(550, 400);
	m_startGameBtn.setColor(sf::Color::Cyan);

	m_startGame = false;

	// Load a texture from a file
	m_craft.getSpriteField().setCoordinate(10, 6);
	if (!m_threeMastedTexture.loadFromFile("../images/craft_3.png"))
	{
		std::cout << "Error load craft texture!" << std::endl;
	}
	else
	{
		// Assign it to a sprite
		m_craft.getSpriteField().setSprite(m_threeMastedTexture);
	}
}

void SelectCraftWindow::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	float mouseX = IScreen::mouseX;
	float mouseY = IScreen::mouseY;

	//Run only when pressed not realese and hold
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left) {

			if (m_craft.getSpriteField().getChecked())
			{
				m_craft.getSpriteField().setChecked(false);
			}
			else {
				if (m_craft.getSpriteField().onClick(mouseX, mouseY))
					std::cout << "Clicked craft" << std::endl;
			}

			if (m_randomCraftBtn.onClick(mouseX, mouseY))
			{
				m_boardPlayer.resetBoard();
				m_boardPlayer.randomCraft(4, 1);
				m_boardPlayer.randomCraft(3, 2);
				m_boardPlayer.randomCraft(2, 3);
				m_boardPlayer.randomCraft(1, 4);
			}

			if (m_nextPlayerBtn.onClick(mouseX, mouseY))
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

			if (m_startGameBtn.onClick(mouseX, mouseY))
			{
				m_gameSettings.setPlayerBoard_2(m_boardPlayer);
				Game::Screen = std::make_shared<GameScreen>(m_gameSettings);
				return;
			}
		}
	}
	
}

void SelectCraftWindow::update()
{

	if (m_craft.getSpriteField().getChecked())
	{
		int x = int(mouseX) / m_craft.getSpriteField().getSpaceBetweenField();
		int y = int(mouseY) / m_craft.getSpriteField().getSpaceBetweenField();
		m_craft.getSpriteField().setCoordinate(x,y);
		m_craft.getSpriteField().setSprite(m_threeMastedTexture);	
	}
}

void SelectCraftWindow::render(sf::RenderWindow& window)
{


	for (int y = 0; y < m_boardPlayer.getDimensionY(); y++)
	{
		for (int x = 0; x < m_boardPlayer.getDimensionX(); x++)
		{
			Field field = m_boardPlayer.getFieldTab()[y][x];

			//Display craft
			if (field.getType() != CraftType::zeroMasted && field.getType() != CraftType::forbid)
				field.setColor(sf::Color::Green);

			window.draw(field.renderField());
		}
	}

	window.draw(m_craft.getSpriteField().getSprite());

	window.draw(m_randomCraftBtn.renderField());
	if(!m_startGame)
		window.draw(m_nextPlayerBtn.renderField());
	if (m_startGame)
		window.draw(m_startGameBtn.renderField());
}

void SelectCraftWindow::setStartGame(bool startGame)
{
	m_startGame = startGame;
}
