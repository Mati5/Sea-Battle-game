#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "GridField.h"
#include "Board.h"

class DrawLotsBtn: public GridField
{
	sf::Font myFont;
	sf::Text title;
	int fontSize;
	//sf::Font myFont;

public:
	DrawLotsBtn();
	void setTitle(std::string title);
	sf::RectangleShape renderField();
	sf::Text renderText();
};

