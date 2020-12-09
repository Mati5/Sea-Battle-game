#pragma once
#include <SFML/Graphics.hpp>
class IScreen
{
public:
	/*metody czysto wirtualne
		nie maj¹ definicji <jedynie deklaracjê>, nie mo¿e zostaæ wyko³ana
		jest przyrówna do zera aby poinformowaæ kompilator ¿e brak definicji i mo¿liwoœci wyw³ania jest zamierzony

		deklaracja tych funkcji wystêpuje w klasach gdiz nastêpuje dziedziczenie	*/
	//virtual void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) = 0;
	virtual void update(bool leftMouseBtnPressed, float mouseX, float mouseY) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};