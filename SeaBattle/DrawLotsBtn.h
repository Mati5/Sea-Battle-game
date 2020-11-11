#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "GridField.h"
#include "Board.h"

class DrawLotsBtn: public GridField
{
	

public:
	sf::RectangleShape renderField();
};

