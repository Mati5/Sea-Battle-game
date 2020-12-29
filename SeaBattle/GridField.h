#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GridField
{
protected:
	std::vector<int> m_coordinate;
	float m_width;
	float m_height;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

public:
	GridField();

	virtual ~GridField();

	virtual void setCoordinate(int x, int y);

	std::vector<int> getCoordinate() const;

	virtual int getCoordinateX() const;

	virtual int getCoordinateY() const;

	void setWidth(float width);

	float getWidth() const;

	void setHeight(float height);

	float getHeight() const;

	virtual bool onClick(float mouseX, float mouseY);

	void loadTexture(const std::string& location);

	void setSprite(const sf::Texture& texture);

	sf::Sprite getSprite() const;
};