#include "SelectCraftWindow.h"



SelectCraftWindow::SelectCraftWindow()
{
	randomCraftBtn.setCoordinate(50, 400);
	
	nextPlayerBtn.setCoordinate(400, 400);
	nextPlayerBtn.setColor(sf::Color::Green);

	startGameBtn.setCoordinate(550, 400);
	startGameBtn.setColor(sf::Color::Cyan);

	startGame = false;
}

void SelectCraftWindow::update(bool leftMouseBtnPressed, float mouseX, float mouseY)
{
	if (leftMouseBtnPressed)
	{
		if (this->randomCraftBtn.onClick(mouseX, mouseY)) 
		{
			board.resetBoard();
			board.randomCraft(4, 1);
			board.randomCraft(3, 2);
			board.randomCraft(2, 3);
			board.randomCraft(1, 4);
		}
		if (this->nextPlayerBtn.onClick(mouseX, mouseY))
		{
			gameSettings.setPlayerBoard_1(board);
			board.resetBoard();
			this->setStartGame(true);
		}
		if (this->startGameBtn.onClick(mouseX, mouseY))
		{
			gameSettings.setPlayerBoard_2(board);
			Game::Screen = std::make_shared<GameScreen>(gameSettings);
		}
	}
}

void SelectCraftWindow::render(sf::RenderWindow& window)
{


	for (int y = 0; y < board.getDimensionY(); y++)
	{
		for (int x = 0; x < board.getDimensionX(); x++)
		{
			Field field = board.getFieldTab()[y][x];

			//Display craft
			if (field.getType() != CraftType::zeroMasted && field.getType() != CraftType::forbid)
				field.setColor(sf::Color::Green);

			window.draw(field.renderField());
		}
	}

	window.draw(this->randomCraftBtn.renderField());
	if(!startGame)
		window.draw(this->nextPlayerBtn.renderField());
	if (startGame)
		window.draw(this->startGameBtn.renderField());
}

void SelectCraftWindow::setStartGame(bool startGame)
{
	this->startGame = startGame;
}
