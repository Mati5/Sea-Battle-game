#pragma once
#include <SFML/Graphics.hpp>
class IScreen
{
public:
	float mouseX;
	float mouseY;

	virtual ~IScreen();
	/*metody czysto wirtualne
		nie maj¹ definicji <jedynie deklaracjê>, nie mo¿e zostaæ wyko³ana
		jest przyrówna do zera aby poinformowaæ kompilator ¿e brak definicji i mo¿liwoœci wyw³ania jest zamierzony

		deklaracja tych funkcji wystêpuje w klasach gdiz nastêpuje dziedziczenie	*/
	//virtual void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) = 0;
	virtual void handleInput(sf::RenderWindow& window, const sf::Event& event) = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

};