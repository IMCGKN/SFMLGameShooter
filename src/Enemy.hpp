#pragma once

#include "GameObject.hpp"

class ImcEnemy : public ImcGameObject
{
public:
    ImcEnemy(sf::Vector2f pos);

    void Update(float dt);
    void Render(sf::RenderTarget& target);

    void SetVelX(float x) { m_VelX = x; }
private:
    float m_VelX = 1.0f;
    sf::Sprite m_Sprite;
};
