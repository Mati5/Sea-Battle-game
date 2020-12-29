#include "IScreen.h"

IScreen::~IScreen()
{
}

void IScreen::setBackground(const std::string& location)
{
	if (!backgroundTexture.loadFromFile(location))
	{
		std::cout << "Error load craft texture!" << std::endl;
	}
	backgroundTexture.setRepeated(true);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, int(windowWidth), int(windowHeight)));

}

void IScreen::setMousePosition(const sf::RenderWindow& window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

	mouseX = worldPos.x;
	mouseY = worldPos.y;
}
