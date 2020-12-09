#include "GameScreen.h"

void GameScreen::update(bool leftMouseBtnPressed, float mouseX, float mouseY)
{
	this->setLeftMouseBtnPressed(leftMouseBtnPressed);

	if (leftMouseBtnPressed)
	{
		//Set user turn
		if (this->playerBoard_1.getClickedField().getChecked() && !this->playerBoard_1.getClickedField().hitCraft())
		{
			Field none;
			this->playerBoard_1.setClickedField(none);
			this->setTurn(true);
		}
		if (this->playerBoard_2.getClickedField().getChecked() && !this->playerBoard_2.getClickedField().hitCraft())
		{
			Field none;
			this->playerBoard_2.setClickedField(none);
			this->setTurn(false);
		}

		if (playerDrawLotsBtn_1.onClick(mouseX, mouseY))
		{
			std::cout << "CLICKED BUTTON RAND" << std::endl;
			this->playerBoard_1.resetBoard();
			this->playerBoard_1.randomCraft(4, 1);
			this->playerBoard_1.randomCraft(3, 2);
			this->playerBoard_1.randomCraft(2, 3);
			this->playerBoard_1.randomCraft(1, 4);
		}
	}
}

void GameScreen::render(sf::RenderWindow& window)
{
	sf::View playerView_1(sf::FloatRect(0.f, 0.f, 1140.f, 680.f));
	playerView_1.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	sf::View playerView_2(sf::FloatRect(0.f, 0.f, 1140.f, 680.f));
	playerView_2.setViewport(sf::FloatRect(0.5f, 0.f, 1.f, 1.f));

	sf::View control(sf::FloatRect(0.f, 0.f, 100.f, 100.f));
	control.setViewport(sf::FloatRect(0.0f, 0.5f, 1.f, 1.f));

	window.clear();

	window.setView(playerView_1);
	this->playerBoard_1.renderBoard(window, leftMouseBtnPressed, true); //!this->getTurn()

	window.setView(playerView_2);
	this->playerBoard_2.renderBoard(window, leftMouseBtnPressed, true); //this->getTurn()

	window.setView(control);
	window.draw(playerDrawLotsBtn_1.renderField());
}

void GameScreen::setLeftMouseBtnPressed(bool leftMouseBtnPressed)
{
	this->leftMouseBtnPressed = leftMouseBtnPressed;
}

void GameScreen::setTurn(bool turn)
{
	this->turn = turn;
}

bool GameScreen::getTurn()
{
	return this->turn;
}
