#include "StartScreen.h"


StartScreen::StartScreen()
{
	if (!logoTexture.loadFromFile("../images/logo-sea-battle.png"))
	{
		std::cout << "Error load craft texture!" << std::endl;
	}

	logoTexture.setRepeated(true);
	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(windowWidth / 2 - float(logoTexture.getSize().x) / 2, 70);
	
	oneVsOneBtn.setCoordinate(int(windowWidth / 2 - oneVsOneBtn.getWidth() / 2), 200);
	oneVsOneBtn.loadTexture("../images/play-one-vs-one-btn.png");

	oneVsAiBtn.setCoordinate(int(windowWidth / 2 - oneVsOneBtn.getWidth() / 2), 280);
	oneVsAiBtn.loadTexture("../images/play-one-vs-bot-btn.png");

	exitBtn.setCoordinate(int(windowWidth / 2 - oneVsOneBtn.getWidth() / 2), 360);
	exitBtn.loadTexture("../images/exit-btn.png");
}

void StartScreen::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{	
		if (oneVsOneBtn.onClick(mouseX, mouseY))
		{
			Game::Screen = std::make_shared<SelectCraftWindow>(GameMode::OneVsOne);
			return;
		}
				
		if (oneVsAiBtn.onClick(mouseX, mouseY))
		{
			Game::Screen = std::make_shared<SelectCraftWindow>(GameMode::OneVsAi);
			return;
		}
	}
}

void StartScreen::update(sf::Time deltaTime)
{
	
}

void StartScreen::render(sf::RenderWindow& window)
{
	window.draw(logoSprite);
	window.draw(oneVsOneBtn.getSprite());
	window.draw(oneVsAiBtn.getSprite());
	window.draw(exitBtn.getSprite());
}