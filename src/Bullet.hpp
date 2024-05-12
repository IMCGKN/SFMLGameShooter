#pragma once

#include "GameObject.hpp"

class ImcBullet : public ImcGameObject
{
public:
    ImcBullet(sf::Vector2f pos);

    void Update(float dt);
    void Render(sf::RenderTarget& target);

    void SetVelX(float x) { m_VelX = x; }
private:
    sf::RectangleShape m_Shape;
    float m_VelX = -1.0f;
};
