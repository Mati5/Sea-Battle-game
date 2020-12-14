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

public:
	SelectCraftWindow();
	/*implementacja funkcji z interfesju*/
	void update(bool leftMouseBtnPressed, float mouseX, float mouseY) override;
	void render(sf::RenderWindow& window) override;

	void setStartGame(bool startGame);
};

