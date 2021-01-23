#include "Text.h"

Text::Text()
{
	if (!m_font.loadFromFile("../fonts/Roboto/Roboto-Regular.ttf"))
		std::cout << "ERROR: load font" << std::endl;

	m_text.setFont(m_font);
	m_text.setString("Text");
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color::Black);
}

void Text::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

void Text::setPosition(float x, float y)
{
	m_text.setPosition(x, y);
}

void Text::setText(const std::string& text)
{
	m_text.setString(text);
}

sf::Text Text::getText() const
{
	return m_text;
}
