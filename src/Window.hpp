#pragma once

#include <SFML/Graphics.hpp>

class ImcWindow
{
public:
    ImcWindow();
    ~ImcWindow();

    sf::RenderWindow& getWindow() const { return *m_Window; }

    void Draw(const sf::Drawable& drawable, sf::Shader* shader = nullptr);

    void closeWindow() { m_Window->close(); }
private:
    sf::RenderWindow *m_Window;
};
