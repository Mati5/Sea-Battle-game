#include "DrawLotsBtn.h"

DrawLotsBtn::DrawLotsBtn()
{
	width = 100;
	height = 50;
	color = sf::Color::Red;
	coordinate[0] = 20;
	coordinate[1] = 20;

	fontSize = 20;
	
	if (!myFont.loadFromFile("../fonts/Roboto/Roboto-Regular.ttf"))
	{
		// Error...
	}
	title.setCharacterSize(fontSize);
	title.setString("Button");
	title.setFont(myFont);
	title.setFillColor(sf::Color::White);
	
	float d = (height - fontSize-5) / 2;

	title.setPosition(this->coordinate[0]+d, this->coordinate[1]+d);

}

void DrawLotsBtn::setTitle(std::string title)
{
	this->title.setString(title);
}



sf::RectangleShape DrawLotsBtn::renderField()
{
	sf::RectangleShape shape;
	sf::Vector2f kratkaSize(this->width, this->height);

	shape.setSize(kratkaSize);
	shape.setFillColor(this->color);
	shape.setPosition(this->coordinate[0], this->coordinate[1]);


	return shape;
}

sf::Text DrawLotsBtn::renderText()
{
	
	float d = (height - fontSize - 5) / 2;

	title.setPosition(this->coordinate[0] + d, this->coordinate[1] + d);


	return title;
}
