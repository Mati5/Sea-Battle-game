#include "SelectCraftWindow.h"



SelectCraftWindow::SelectCraftWindow()
{
	randomCraftBtn.setCoordinate(50, 400);
	
	nextPlayerBtn.setCoordinate(400, 400);
	nextPlayerBtn.setColor(sf::Color::Green);

	startGameBtn.setCoordinate(550, 400);
	startGameBtn.setColor(sf::Color::Cyan);

	startGame = false;

	// Load a texture from a file
	craft.getSpriteField().setCoordinate(10, 6);
	if (!threeMastedTexture.loadFromFile("../images/craft_3.png"))
	{
		std::cout << "Error load craft texture!" << std::endl;
	}
	else
	{
		// Assign it to a sprite
		craft.getSpriteField().setSprite(threeMastedTexture);
		
		
	}
}

void SelectCraftWindow::handleInput(sf::RenderWindow& window, sf::Event event)
{
	float mouseX = IScreen::mouseX;
	float mouseY = IScreen::mouseY;

	//Run only when pressed not realese and hold
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left) {

			if (this->craft.getSpriteField().getChecked())
			{
				this->craft.getSpriteField().setChecked(false);
			}
			else {
				if (this->craft.getSpriteField().onClick(mouseX, mouseY))
					std::cout << "Clicked craft" << std::endl;
			}

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
				switch (gameSettings.getSelectedGameMode())
				{
				case GameMode::OneVsOne:
					gameSettings.setPlayerBoard_1(board);
					board.resetBoard();
					this->setStartGame(true);
					break;
				case GameMode::OneVsAi:
					gameSettings.setPlayerBoard_1(board);
					board.resetBoard();
					board.randomCraft(4, 1);
					board.randomCraft(3, 2);
					board.randomCraft(2, 3);
					board.randomCraft(1, 4);
					gameSettings.setPlayerBoard_2(board);
					Game::Screen = std::make_shared<GameScreen>(gameSettings);
					break;
				}
				return;
			}

			if (this->startGameBtn.onClick(mouseX, mouseY))
			{
				gameSettings.setPlayerBoard_2(board);
				Game::Screen = std::make_shared<GameScreen>(gameSettings);
				return;
			}
		}
	}
	
}

void SelectCraftWindow::update()
{

	if (craft.getSpriteField().getChecked())
	{
		int x = mouseX / craft.getSpriteField().getSpaceBetweenField();
		int y = mouseY / craft.getSpriteField().getSpaceBetweenField();
		craft.getSpriteField().setCoordinate(x,y);
		craft.getSpriteField().setSprite(threeMastedTexture);
		
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

	window.draw(craft.getSpriteField().getSprite());

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
