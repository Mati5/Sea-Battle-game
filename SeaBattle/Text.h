#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Text
{
	sf::Text m_text;
	sf::Font m_font;

public:
	Text();

	void setFont(const sf::Font& font);

	void setPosition(float x, float y);

	void setText(const std::string& text);

	sf::Text getText() const;
};

