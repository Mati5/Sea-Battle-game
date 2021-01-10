#include "BoardPlayer.h"

void BoardPlayer::tickField(Field& field)
{
	
	if (!field.getChecked())
	{
		field.setChecked(true);

		setClickedField(field);
		updateTabEl(field);

		if (field.hitCraft())
			m_boardStats++;

		checkCraftIsDestroyed(field);
	}
}