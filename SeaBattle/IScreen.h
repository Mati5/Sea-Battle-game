#pragma once
#include <SFML/Graphics.hpp>
class IScreen
{
public:
	/*metody czysto wirtualne
		nie maj� definicji <jedynie deklaracj�>, nie mo�e zosta� wyko�ana
		jest przyr�wna do zera aby poinformowa� kompilator �e brak definicji i mo�liwo�ci wyw�ania jest zamierzony

		deklaracja tych funkcji wyst�puje w klasach gdiz nast�puje dziedziczenie	*/
	virtual void processEvents(sf::RenderWindow& window) = 0;
	virtual void update(sf::Time delta) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};