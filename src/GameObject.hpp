#pragma once

#include <SFML/Graphics.hpp>

class ImcGameObject
{
protected:
    sf::FloatRect m_Rect;
    sf::Vector2f m_Pos;

    float m_Speed = 690.0f;
    int gameObjectType = 0;
public:
    ImcGameObject(sf::Vector2f pos)
    {
        m_Pos = pos;
    }

    virtual void Update(float dt) = 0;
    virtual void Render(sf::RenderTarget& target) = 0;

    float GetSpeed() { return m_Speed; }
    sf::Vector2f GetPos() { return m_Pos; }
    sf::FloatRect GetRect() { return m_Rect; }

    sf::Clock killTimer;
    int health = 100;

    sf::Texture m_Texture;
};
