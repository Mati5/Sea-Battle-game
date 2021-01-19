#include "StartScreen.h"
#include "SettingsScreen.h"

StartScreen::StartScreen()
{
	setBackground("../images/bg1.png");

	if (!m_logoTexture.loadFromFile("../images/logo-sea-battle.png"))
	{
		std::cout << "Error load craft texture!" << std::endl;
	}

	m_logoTexture.setRepeated(true);
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(windowWidth / 2 - float(m_logoTexture.getSize().x) / 2, 70);
	
	m_oneVsOneBtn.setCoordinate(int(windowWidth / 2 - m_oneVsOneBtn.getWidth() / 2), 200);
	m_oneVsOneBtn.loadTexture("../images/play-one-vs-one-btn.png");

	m_oneVsAiBtn.setCoordinate(int(windowWidth / 2 - m_oneVsOneBtn.getWidth() / 2), 280);
	m_oneVsAiBtn.loadTexture("../images/play-one-vs-bot-btn.png");

	m_settingsBtn.setCoordinate(int(windowWidth / 2 - m_oneVsOneBtn.getWidth() / 2), 360);
	m_settingsBtn.loadTexture("../images/settings-btn.png");

	m_exitBtn.setCoordinate(int(windowWidth / 2 - m_oneVsOneBtn.getWidth() / 2), 440);
	m_exitBtn.loadTexture("../images/exit-btn.png");
}

void StartScreen::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{	
		if (m_oneVsOneBtn.onClick(mouseX, mouseY))
		{
			Game::Screen = std::make_shared<SelectCraftWindow>(GameMode::OneVsOne);
			return;
		}
				
		if (m_oneVsAiBtn.onClick(mouseX, mouseY))
		{
			Game::Screen = std::make_shared<SelectCraftWindow>(GameMode::OneVsAi);
			return;
		}

		if (m_settingsBtn.onClick(mouseX, mouseY))
		{
			Game::Screen = std::make_shared<SettingsScreen>();
			return;
		}

		if (m_exitBtn.onClick(mouseX, mouseY))
		{
			window.close();
			return;
		}
	}
}

void StartScreen::update(sf::Time deltaTime)
{
	
}

void StartScreen::render(sf::RenderWindow& window)
{
	window.clear();
	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);
	window.draw(m_logoSprite);
	window.draw(m_oneVsOneBtn.getSprite());
	window.draw(m_oneVsAiBtn.getSprite());
	window.draw(m_settingsBtn.getSprite());
	window.draw(m_exitBtn.getSprite());
}