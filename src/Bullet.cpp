#include "Bullet.hpp"

ImcBullet::ImcBullet(sf::Vector2f pos)
    : ImcGameObject(pos)
{
    m_Pos = pos;
    m_Shape.setFillColor(sf::Color::Green);
    m_Shape.setPosition(m_Pos);
    m_Shape.setSize(sf::Vector2f(7.0f, 5.5f));
    m_Speed = 920.0f;
    health = 2.0f;
}

void ImcBullet::Update(float dt)
{
    m_Shape.setPosition(m_Pos);
    m_Pos.x -= m_VelX * m_Speed * dt;
    m_Rect = m_Shape.getGlobalBounds();
}

void ImcBullet::Render(sf::RenderTarget &target)
{
    target.draw(m_Shape);
}
