#include "Player.hpp"

#include <iostream>

ImcPlayer::ImcPlayer(sf::Vector2f pos)
    : ImcGameObject(pos)
{
    m_Speed = 725.0f;

    m_Texture.loadFromFile("res/player.png");
    m_Texture.generateMipmap();
    m_Texture.setSmooth(false);
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setScale(1.45f, 1.50f);
}

void ImcPlayer::Update(float dt)
{
    m_Sprite.setPosition(m_Pos);
    m_Rect = m_Sprite.getGlobalBounds();
    if(m_Pos.y >= 9.0f)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            m_Pos.y -= m_Speed * dt;
        }
    }
    if(m_Pos.y <= 673)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            m_Pos.y += m_Speed * dt;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        m_Pos.x -= m_Speed * dt;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        m_Pos.x += m_Speed * dt;
    }

    if(m_Pos.x <= 25.0f)
    {
        m_Pos.x = 25.0f;
    }
    else if(m_Pos.x >= 85.0f)
    {
        m_Pos.x = 85.0f;
    }
}

void ImcPlayer::Render(sf::RenderTarget &target)
{
    target.draw(m_Sprite);
}
