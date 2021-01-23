#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(): m_tickForbidAreaBtn(Settings::get().getShowForbidArea())
{
	setBackground("../images/bg1.png");

	m_logoTexture.setRepeated(true);
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(windowWidth / 2 - float(m_logoTexture.getSize().x) / 2, 70);

	m_backBtn.setCoordinate(int(windowWidth / 2 - m_backBtn.getWidth() / 2), int(windowHeight-100));
	m_backBtn.setWidth(160);
	m_backBtn.setHeight(50);
	m_backBtn.loadTexture("../images/back-btn.png");
	
	m_tickForbidAreaText.setText("Tick forbid area:");
	m_tickForbidAreaText.setPosition(450, 140);

	m_quantityCraftFieldText.setText("Quantity available field:");
	m_quantityCraftFieldText.setPosition(450, 190);

	m_maxCraftFieldText.setText("/ " + std::to_string(Settings::get().getMaxCraftField()));
	m_maxCraftFieldText.setPosition(760, 190);

	m_currentCraftFieldText.setText(std::to_string(Settings::get().getCurrentCraftField()));
	m_currentCraftFieldText.setPosition(730, 190);

	m_fourMasthedQuantityInfoText.setText("Four masthed quantity:");
	m_fourMasthedQuantityInfoText.setPosition(450, 240);
	m_fourMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityFourMasthed()));
	m_fourMasthedQuantityText.setPosition(725, 240);
	m_fourMasthedIncDecBtn.setPosition(750, 235);

	m_threeMasthedQuantityInfoText.setText("Three masthed quantity:");
	m_threeMasthedQuantityInfoText.setPosition(450, 300);
	m_threeMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityThreeMasthed()));
	m_threeMasthedQuantityText.setPosition(725, 300);
	m_threeMasthedIncDecBtn.setPosition(750, 295);

	m_twoMasthedQuantityInfoText.setText("Two masthed quantity:");
	m_twoMasthedQuantityInfoText.setPosition(450, 360);
	m_twoMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityTwoMasthed()));
	m_twoMasthedQuantityText.setPosition(725, 360);
	m_twoMasthedIncDecBtn.setPosition(750, 355);

	m_oneMasthedQuantityInfoText.setText("One masthed quantity:");
	m_oneMasthedQuantityInfoText.setPosition(450, 420);
	m_oneMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityOneMasthed()));
	m_oneMasthedQuantityText.setPosition(725, 420);
	m_oneMasthedIncDecBtn.setPosition(750, 415);

	m_tickForbidAreaBtn.setCoordinate(650, 135);
	m_tickForbidAreaBtn.updateCoordinate();
}

void SettingsScreen::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		if (m_tickForbidAreaBtn.onClick(mouseX, mouseY))
		{
			m_tickForbidAreaBtn.setChecked(!m_tickForbidAreaBtn.getChecked());
			m_tickForbidAreaBtn.checkIsChecked();
			Settings::get().setShowForbidArea(m_tickForbidAreaBtn.getChecked());		
		}

		if (m_backBtn.onClick(mouseX, mouseY))
		{
			Game::Screen = std::make_shared<StartScreen>();
			return;
		}
		//if (Settings::get().getMaxCraftField()>=Settings::get().getCurrentCraftField())
		//{
			if (Settings::get().getMaxCraftField() >= Settings::get().getCurrentCraftField()+4 && m_fourMasthedIncDecBtn.getIncButton().onClick(mouseX, mouseY))
			{
				Settings::get().incDecQuantityCraft(CraftType::fourMasted, 1);
				m_fourMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityFourMasthed()));
			}

			if (Settings::get().getMaxCraftField() >= Settings::get().getCurrentCraftField() + 3 && m_threeMasthedIncDecBtn.getIncButton().onClick(mouseX, mouseY))
			{
				Settings::get().incDecQuantityCraft(CraftType::threeMasted, 1);
				m_threeMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityThreeMasthed()));
			}

			if (Settings::get().getMaxCraftField() >= Settings::get().getCurrentCraftField() + 2 && m_twoMasthedIncDecBtn.getIncButton().onClick(mouseX, mouseY))
			{
				Settings::get().incDecQuantityCraft(CraftType::twoMasted, 1);
				m_twoMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityTwoMasthed()));
			}

			if (Settings::get().getMaxCraftField() >= Settings::get().getCurrentCraftField() + 1 &&
				Settings::get().getMaxOneMasthed() >= Settings::get().getQuantityOneMasthed() &&
				m_oneMasthedIncDecBtn.getIncButton().onClick(mouseX, mouseY))
			{
				Settings::get().incDecQuantityCraft(CraftType::oneMasted, 1);
				m_oneMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityOneMasthed()));
			}
		//}
	
		if (m_fourMasthedIncDecBtn.getDecButton().onClick(mouseX, mouseY))
		{
			Settings::get().incDecQuantityCraft(CraftType::fourMasted, -1);
			m_fourMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityFourMasthed()));
		}

		if (m_threeMasthedIncDecBtn.getDecButton().onClick(mouseX, mouseY))
		{
			Settings::get().incDecQuantityCraft(CraftType::threeMasted, -1);
			m_threeMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityThreeMasthed()));
		}

		if (m_twoMasthedIncDecBtn.getDecButton().onClick(mouseX, mouseY))
		{
			Settings::get().incDecQuantityCraft(CraftType::twoMasted, -1);
			m_twoMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityTwoMasthed()));
		}

		if (m_oneMasthedIncDecBtn.getDecButton().onClick(mouseX, mouseY))
		{
			Settings::get().incDecQuantityCraft(CraftType::oneMasted, -1);
			m_oneMasthedQuantityText.setText(std::to_string(Settings::get().getQuantityOneMasthed()));
		}
	}
}

void SettingsScreen::update(sf::Time deltaTime)
{
	m_currentCraftFieldText.setText(std::to_string(Settings::get().getCurrentCraftField()));
}

void SettingsScreen::render(sf::RenderWindow& window)
{
	window.clear();
	window.draw(backgroundSprite);
	window.draw(m_logoSprite);
	window.draw(m_tickForbidAreaText.getText());

	window.draw(m_quantityCraftFieldText.getText());
	window.draw(m_maxCraftFieldText.getText());
	window.draw(m_currentCraftFieldText.getText());

	window.draw(m_fourMasthedQuantityInfoText.getText());
	window.draw(m_fourMasthedQuantityText.getText());
	m_fourMasthedIncDecBtn.renderIncDecBtn(window);

	window.draw(m_threeMasthedQuantityInfoText.getText());
	window.draw(m_threeMasthedQuantityText.getText());
	m_threeMasthedIncDecBtn.renderIncDecBtn(window);

	window.draw(m_twoMasthedQuantityInfoText.getText());
	window.draw(m_twoMasthedQuantityText.getText());
	m_twoMasthedIncDecBtn.renderIncDecBtn(window);

	window.draw(m_oneMasthedQuantityInfoText.getText());
	window.draw(m_oneMasthedQuantityText.getText());
	m_oneMasthedIncDecBtn.renderIncDecBtn(window);

	window.draw(m_tickForbidAreaBtn.getSprite());

	window.draw(m_backBtn.getSprite());
}
