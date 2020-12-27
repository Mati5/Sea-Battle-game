#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.F / 30.F);

std::shared_ptr<IScreen> Game::Screen = std::make_shared<StartScreen>(); //StartScreen()

Game::Game() : _window(sf::VideoMode(1140, 680), "Sea Battle", sf::Style::Titlebar | sf::Style::Close)
{
	
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (_window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();	
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::handleInput()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_window.close();

		Game::Screen->handleInput(_window, event);
	}
}

void Game::update(sf::Time deltaTime) const
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
	sf::Vector2f worldPos = _window.mapPixelToCoords(mousePosition);

	Game::Screen->mouseX = worldPos.x;
	Game::Screen->mouseY = worldPos.y;

	Game::Screen->update(deltaTime);
}

void Game::render()
{
	_window.clear();
	Game::Screen->render(_window);
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(15);
	_window.display();
}


