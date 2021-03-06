#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class IScreen
{
public:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	float mouseX{0};
	float mouseY{0};
	float windowWidth{ 1140 };
	float windowHeight{ 680 };

	virtual ~IScreen();
	void setBackground(const std::string& location);
	void setMousePosition(const sf::RenderWindow& window);
	/*metody czysto wirtualne
		nie maj� definicji <jedynie deklaracj�>, nie mo�e zosta� wyko�ana
		jest przyr�wna do zera aby poinformowa� kompilator �e brak definicji i mo�liwo�ci wyw�ania jest zamierzony

		deklaracja tych funkcji wyst�puje w klasach gdiz nast�puje dziedziczenie	*/

	virtual void handleInput(sf::RenderWindow& window, const sf::Event& event) = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};