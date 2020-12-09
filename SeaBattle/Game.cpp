#include "Game.h"

std::shared_ptr<IScreen> Game::Screen = std::make_shared<StartScreen>();

Game::Game() : _window(sf::VideoMode(1140, 680), "Sea Battle", sf::Style::Titlebar | sf::Style::Close)
{
	
}



void Game::run()
{
	while (_window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::MouseButtonPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::MouseButtonReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			_window.close();
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
	sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
	sf::Vector2f worldPos = _window.mapPixelToCoords(mousePosition);

	mouseX = worldPos.x;
	mouseY = worldPos.y;

	Game::Screen->update(leftMouseBtnPressed, mouseX, mouseY);
}

void Game::render()
{
	_window.clear();
	Game::Screen->render(_window);
	_window.display();
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(15);
}


