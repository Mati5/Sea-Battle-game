#include "IncDecBtn.h"

IncDecBtn::IncDecBtn()
{
    m_incButton.setWidth(45);
    m_incButton.setHeight(45);
    m_incButton.loadTexture("../images/plus.png");
    
    m_decButton.setWidth(45);
    m_decButton.setHeight(45);
    m_decButton.setCoordinate(80, 20);
    m_decButton.loadTexture("../images/minus.png");
    
}

Button IncDecBtn::getIncButton() const
{
    return m_incButton;
}

Button IncDecBtn::getDecButton() const
{
    return m_decButton;
}

void IncDecBtn::renderIncDecBtn(sf::RenderWindow& window)
{
    window.draw(m_decButton.getSprite());
    window.draw(m_incButton.getSprite());
}

void IncDecBtn::setPosition(int x, int y)
{
    m_incButton.setCoordinate(x, y);
    m_decButton.setCoordinate(x + int(m_incButton.getWidth()*1.2), y);
    m_incButton.loadTexture("../images/plus.png");
    m_decButton.loadTexture("../images/minus.png");
}
