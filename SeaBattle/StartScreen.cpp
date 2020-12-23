#include "StartScreen.h"


StartScreen::StartScreen()
{
	startBtn.setWidth(180);
}

void StartScreen::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left) {
			std::cout << "CLICKED BUTTON Start" << std::endl;
			Game::Screen = std::make_shared<SelectCraftWindow>();
		}
	}
}

void StartScreen::update()
{
	
}

void StartScreen::render(sf::RenderWindow& window)
{
	startBtn.setCoordinate(window.getSize().x/2-startBtn.getWidth()/2, 20);
	
	window.draw(startBtn.renderField());
}