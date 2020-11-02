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
		sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
	}
}

void Game::render()
{
	sf::View playerView_1(sf::FloatRect(0.f, 0.f, 1140.f, 680.f));
	playerView_1.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	sf::View playerView_2(sf::FloatRect(0.f, 0.f, 1140.f, 680.f));
	playerView_2.setViewport(sf::FloatRect(0.5f, 0.f, 1.f, 1.f));

	mWindow.clear();

	mWindow.setView(playerView_1);
	this->playerBoard_1.renderBoard(mWindow, leftMouseBtnPressed);

	mWindow.setView(playerView_2);
	this->playerBoard_2.renderBoard(mWindow, leftMouseBtnPressed);

	mWindow.display();
	//mWindow.setFramerateLimit(0);
	mWindow.setVerticalSyncEnabled(true);
}