#include "Enemy.hpp"

ImcEnemy::ImcEnemy(sf::Vector2f pos)
    : ImcGameObject(pos)
{
    m_Pos = pos;
    int n = rand() % 3 + 1;
    std::string file = "res/meteorite" + std::to_string(n) + ".png";
    m_Texture.loadFromFile(file);
    m_Texture.generateMipmap();
    m_Texture.setSmooth(false);
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setScale(1.8f, 1.8f);
    m_Speed = 379.0f;
}

void ImcEnemy::Update(float dt)
{
    m_Sprite.setPosition(m_Pos);
    m_Pos.x -= m_VelX * m_Speed * dt;
    m_Rect = m_Sprite.getGlobalBounds();
}

void ImcEnemy::Render(sf::RenderTarget &target)
{
    target.draw(m_Sprite);
}
