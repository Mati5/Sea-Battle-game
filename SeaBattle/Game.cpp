#include "Game.h"

Game::Game() : mWindow(sf::VideoMode(1140, 680), "Sea Battle")
{
	
}

void Game::run()
{
	while (mWindow.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::setTurn(bool turn)
{
	this->turn = turn;
}

bool Game::getTurn()
{
	return this->turn;
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type) {
			case sf::Event::MouseButtonPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::MouseButtonReleased:
				handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Mouse::Left)
	{
		leftMouseBtnPressed = isPressed;
	}
}

void Game::update()
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


		//Btn rand crafts
		sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
		sf::Vector2f worldPos = mWindow.mapPixelToCoords(mousePosition);

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
}

void Game::render()
{
	sf::View playerView_1(sf::FloatRect(0.f, 0.f, 1140.f, 680.f));
	playerView_1.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	sf::View playerView_2(sf::FloatRect(0.f, 0.f, 1140.f, 680.f));
	playerView_2.setViewport(sf::FloatRect(0.5f, 0.f, 1.f, 1.f));

	sf::View control(sf::FloatRect(0.f, 0.f, 100.f, 100.f));
	control.setViewport(sf::FloatRect(0.0f, 0.5f, 1.f, 1.f));


	mWindow.clear();
	
	mWindow.setView(playerView_1);
	this->playerBoard_1.renderBoard(mWindow, leftMouseBtnPressed, true); //!this->getTurn()

	mWindow.setView(playerView_2);
	this->playerBoard_2.renderBoard(mWindow, leftMouseBtnPressed, true); //this->getTurn()

	mWindow.setView(control);
	mWindow.draw(playerDrawLotsBtn_1.renderField());

	mWindow.display();
	//mWindow.setFramerateLimit(0);
	mWindow.setVerticalSyncEnabled(true);
}