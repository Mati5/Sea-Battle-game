#pragma once
#include "Board.h"
#include "Field.h"
#include<Windows.h>

class BoardAi: public Board
{
	std::vector<std::vector<int>> m_availableField{};
	std::vector<Field> m_hitCraftTab;

public:
	BoardAi();

	Field action(std::array<std::array<Field, 10>, 10> fieldTab, std::vector<Craft> craftTab);

	Field getAvailableField(const std::array<std::array<Field, 10>, 10>& fieldTab);

	void delAvailableField(int index);

	void delForbidAvailableField(const std::vector<Field>& forbidArea);

	int getIndexAvailableField(int coordinateX, int coordinateY);

	void clearHitCraftTab();
};

