#include "GameScreen.h"

void GameScreen::processEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::MouseButtonPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::MouseButtonReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void GameScreen::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Mouse::Left)
	{
		leftMouseBtnPressed = isPressed;
	}
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		leftMouseBtnPressed = true;
	}
	else
	{
		leftMouseBtnPressed = false;
	}
}

void GameScreen::update(sf::Time delta)
{
	if (leftMouseBtnPressed)
	{
		//Set user turn
		if (this->playerBoard_1.getClickedField().getChecked() && !this->playerBoard_1.getClickedField().hitCraft())
		{
			Field none;
			this->playerBoard_1.setClickedField(none);
			this->setTurn(true);
		}
		if (this->playerBoard_2.getClickedField().getChecked() && !this->playerBoard_2.getClickedField().hitCraft())
		{
			Field none;
			this->playerBoard_2.setClickedField(none);
			this->setTurn(false);
		}
	}
}

void GameScreen::render(sf::RenderWindow& window)
{
	sf::View playerView_1(sf::FloatRect(0.f, 0.f, 1140.f, 680.f));
	playerView_1.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	sf::View playerView_2(sf::FloatRect(0.f, 0.f, 1140.f, 680.f));
	playerView_2.setViewport(sf::FloatRect(0.5f, 0.f, 1.f, 1.f));

	sf::View control(sf::FloatRect(0.f, 0.f, 100.f, 100.f));
	control.setViewport(sf::FloatRect(0.0f, 0.5f, 1.f, 1.f));

	window.clear();

	window.setView(playerView_1);
	this->playerBoard_1.renderBoard(window, leftMouseBtnPressed, true); //!this->getTurn()

	window.setView(playerView_2);
	this->playerBoard_2.renderBoard(window, leftMouseBtnPressed, true); //this->getTurn()

	window.setView(control);
	window.draw(playerDrawLotsBtn_1.renderField());

	//Btn rand crafts
	if (leftMouseBtnPressed) 
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

		float mouseX = worldPos.x;
		float mouseY = worldPos.y;

		if (playerDrawLotsBtn_1.onClick(mouseX, mouseY))
		{
			this->playerBoard_1.resetBoard();
			this->playerBoard_1.randomCraft(4, 1);
			this->playerBoard_1.randomCraft(3, 2);
			this->playerBoard_1.randomCraft(2, 3);
			this->playerBoard_1.randomCraft(1, 4);
		}
	}
	

	//window.display();
	//mWindow.setFramerateLimit(0);
	
}

void GameScreen::setTurn(bool turn)
{
	this->turn = turn;
}

bool GameScreen::getTurn()
{
	return this->turn;
}
