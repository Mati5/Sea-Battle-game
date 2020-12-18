#include "Game.h"

std::shared_ptr<IScreen> Game::Screen = std::make_shared<SelectCraftWindow>(); //StartScreen()

Game::Game() : _window(sf::VideoMode(1140, 680), "Sea Battle", sf::Style::Titlebar | sf::Style::Close)
{

}


void Game::run()
{
	while (_window.isOpen())
	{
		handleInput();
		update();
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

void Game::update()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
	sf::Vector2f worldPos = _window.mapPixelToCoords(mousePosition);

	Game::Screen->mouseX= worldPos.x;
	Game::Screen->mouseY = worldPos.y;

	Game::Screen->update();
}

void Game::render()
{
	_window.clear();
	Game::Screen->render(_window);
	_window.display();
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(15);
}


