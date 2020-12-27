#pragma once
#include "Board.h"
#include<Windows.h>

class BoardPlayer: public Board
{
	bool m_leftMouseBtnPressed{ false };
public:
	void tickField(Field field);
};





//Board player
/*if (turn && !Ai && m_leftMouseBtnPressed) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
	sf::Vector2f worldPos = mWindow.mapPixelToCoords(mousePosition);

	float mouseX = worldPos.x;
	float mouseY = worldPos.y;

	if (field.onClick(mouseX, mouseY)) {

		setClickedField(field);
		updateTabEl(field);

		//check if craft is destroyed
		checkCraftIsDestroyed(field);
	}
}*/