#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"

class ImcPlayer : public ImcGameObject
{
public:
    ImcPlayer(sf::Vector2f pos);

    void Update(float dt);
    void Render(sf::RenderTarget& target);
    
    sf::Sprite m_Sprite;
    int points = 0;
};
