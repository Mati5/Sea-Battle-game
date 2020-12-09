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
		update(TimePerFrame);
		render();
	}
}

void Game::processEvents()
{
	Game::Screen->processEvents(_window);
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
	_window.setFramerateLimit(15);
}


