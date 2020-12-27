#include "BoardPlayer.h"

void BoardPlayer::tickField(Field field)
{
	
	if (!field.getChecked())
	{
		field.setColor(sf::Color::White);
		field.setChecked(true);

		if (field.hitCraft()) {
			field.setColor(sf::Color::Blue);
		}

		setClickedField(field);
		updateTabEl(field);

		checkCraftIsDestroyed(field);
	}
}