#include "Window.hpp"

#include <vector>
#include <SFML/Graphics/Drawable.hpp>

ImcWindow::ImcWindow()
{
    m_Window = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML Shooter Game", sf::Style::Close | sf::Style::Titlebar);
    m_Window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - m_Window->getSize().x / 2,
                                       sf::VideoMode::getDesktopMode().height / 2 - m_Window->getSize().y / 2));
    m_Window->setFramerateLimit(120);
}

ImcWindow::~ImcWindow()
{
    delete m_Window;
}

void ImcWindow::Draw(const sf::Drawable &drawable, sf::Shader* shader)
{
    m_Window->draw(drawable, shader);
}
