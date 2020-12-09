#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 30.f);

std::shared_ptr<IScreen> Game::Screen = std::make_shared<GameScreen>();

Game::Game() : _window(sf::VideoMode(1140, 680), "Sea Battle")
{
	
}

void Game::run()
{
	while (_window.isOpen())
	{
		processEvents();
		//handleInput();
		update(TimePerFrame);
		render();
	}
}

void Game::handleInput()
{
	

	Game::Screen->handleInput(_window);
}

void Game::processEvents()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_window.close();
	}

	Game::Screen->handleInput(_window);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	_window.clear();
	Game::Screen->render(_window);
	_window.display();
	_window.setVerticalSyncEnabled(true);
}


