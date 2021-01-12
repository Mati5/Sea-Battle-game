#include "SetCraftTab.h"

std::vector<Craft> SetCraftTab(const sf::Texture& fourMTexture, const sf::Texture& threeMTexture, const sf::Texture& twoMTexture, const sf::Texture& oneMTexture)
{
	std::vector<Craft> craftTab;
	craftTab.clear();

	for (int i = 0; i < 1; i++)
	{
		Craft craft;
		craft.getCraftSprite().setType(CraftType::fourMasted);
		craft.setCraftType(CraftType::fourMasted);
		craft.getCraftSprite().setWidth(180);
		craft.getCraftSprite().setHeight(45);
		craft.getCraftSprite().setCoordinate(11, 3);
		craft.getCraftSprite().setSprite(fourMTexture);
		craftTab.push_back(craft);
	}

	for (int i = 0; i < 2; i++)
	{
		Craft craft;
		craft.getCraftSprite().setType(CraftType::threeMasted);
		craft.setCraftType(CraftType::threeMasted);
		craft.getCraftSprite().setWidth(135);
		craft.getCraftSprite().setHeight(45);
		craft.getCraftSprite().setCoordinate(11 + (i * 3), 4);
		craft.getCraftSprite().setSprite(threeMTexture);
		craftTab.push_back(craft);
	}

	for (int i = 0; i < 3; i++)
	{
		Craft craft;
		craft.getCraftSprite().setType(CraftType::twoMasted);
		craft.setCraftType(CraftType::twoMasted);
		craft.getCraftSprite().setWidth(90);
		craft.getCraftSprite().setHeight(45);
		craft.getCraftSprite().setCoordinate(11 + (i * 2), 5);
		craft.getCraftSprite().setSprite(twoMTexture);
		craftTab.push_back(craft);
	}

	for (int i = 0; i < 4; i++)
	{
		Craft craft;
		craft.getCraftSprite().setType(CraftType::oneMasted);
		craft.setCraftType(CraftType::oneMasted);
		craft.getCraftSprite().setWidth(45);
		craft.getCraftSprite().setHeight(45);
		craft.getCraftSprite().setCoordinate(11 + (i * 1), 6);
		craft.getCraftSprite().setSprite(oneMTexture);
		craftTab.push_back(craft);
	}

	return craftTab;
}
