#pragma once
#include "IScreen.h"
#include "GameSettings.h"
#include "Board.h"
#include "Button.h"
#include "Game.h"
#include "GameScreen.h"
#include "SelectCraftWindow.h"
#include "Craft.h"

class SelectCraftWindow: public IScreen
{
	GameSettings gameSettings;
	Board board;
	Button randomCraftBtn;
	Button nextPlayerBtn;
	Button startGameBtn;
	bool startGame;
	sf::Texture threeMastedTexture;
	Craft craft;
	//bool leftMouseBtnPressed;
	Craft selectedCraft;

public:
	SelectCraftWindow();
	/*implementacja funkcji z interfesju*/
	void handleInput(sf::RenderWindow& window, sf::Event event);
	void update() override;
	void render(sf::RenderWindow& window) override;

	void setStartGame(bool startGame);
};

