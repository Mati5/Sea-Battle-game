#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(): m_tickForbidAreaBtn(Settings::get().getShowForbidArea())
{
	setBackground("../images/bg1.png");

	m_logoTexture.setRepeated(true);
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(windowWidth / 2 - float(m_logoTexture.getSize().x) / 2, 70);

	m_backBtn.setCoordinate(int(windowWidth / 2 - m_backBtn.getWidth() / 2), int(windowHeight-100));
	m_backBtn.setWidth(160);
	m_backBtn.setHeight(50);
	m_backBtn.loadTexture("../images/back-btn.png");
	
	if (!m_font.loadFromFile("../fonts/Roboto/Roboto-Regular.ttf"))
		std::cout << "ERROR: load font" << std::endl;
	m_tickForbidAreaText.setFont(m_font);
	m_tickForbidAreaText.setCharacterSize(24);
	m_tickForbidAreaText.setFillColor(sf::Color::Black);
	m_tickForbidAreaText.setString("Tick forbid area:");
	m_tickForbidAreaText.setPosition(450, 140);

	m_tickForbidAreaBtn.setCoordinate(650, 135);
	m_tickForbidAreaBtn.updateCoordinate();
}

void SettingsScreen::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		if (m_tickForbidAreaBtn.onClick(mouseX, mouseY))
		{
			m_tickForbidAreaBtn.setChecked(!m_tickForbidAreaBtn.getChecked());
			m_tickForbidAreaBtn.checkIsChecked();
			Settings::get().setShowForbidArea(m_tickForbidAreaBtn.getChecked());		
		}

		if (m_backBtn.onClick(mouseX, mouseY))
		{
			Game::Screen = std::make_shared<StartScreen>();
		}
	}
}

void SettingsScreen::update(sf::Time deltaTime)
{
	
}

void SettingsScreen::render(sf::RenderWindow& window)
{
	window.clear();
	window.draw(backgroundSprite);
	window.draw(m_logoSprite);
	window.draw(m_tickForbidAreaText);

	window.draw(m_tickForbidAreaBtn.getSprite());

	window.draw(m_backBtn.getSprite());
}
