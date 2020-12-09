#include "StartScreen.h"


StartScreen::StartScreen()
{
	startBtn.setWidth(180);
	startBtn.setTitle("Play with firend");
}

void StartScreen::update(bool leftMouseBtnPressed, float mouseX, float mouseY)
{
	if (leftMouseBtnPressed)
	{
		if (startBtn.onClick(mouseX, mouseY))
		{
			std::cout << "CLICKED BUTTON Start" << std::endl;
			Game::Screen = std::make_shared<GameScreen>();
		}
	}
}

void StartScreen::render(sf::RenderWindow& window)
{
	startBtn.setCoordinate(window.getSize().x/2-startBtn.getWidth()/2, 20);
	


	window.draw(startBtn.renderField());
	window.draw(startBtn.renderText());
}


