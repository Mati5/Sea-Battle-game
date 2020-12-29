#include "BoardPlayer.h"

void BoardPlayer::tickField(Field field)
{
	
	if (!field.getChecked())
	{
		field.setChecked(true);

		setClickedField(field);
		updateTabEl(field);

		checkCraftIsDestroyed(field);
	}
}