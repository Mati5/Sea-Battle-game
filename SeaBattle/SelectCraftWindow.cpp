#include "SelectCraftWindow.h"

void SelectCraftWindow::update(bool leftMouseBtnPressed, float mouseX, float mouseY)
{
	if (leftMouseBtnPressed)
	{

	}
}

void SelectCraftWindow::render(sf::RenderWindow& window)
{
	for (int y = 0; y < board.getDimensionY(); y++)
	{
		for (int x = 0; x < board.getDimensionX(); x++)
		{
			Field field = board.getFieldTab()[y][x];

			window.draw(field.renderField());
		}
	}
}
