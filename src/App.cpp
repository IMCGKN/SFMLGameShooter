#include "App.hpp"

#include <iostream>
#include <math.h>
#include <random>

ImcApp::ImcApp()
{
    m_Window = new ImcWindow();
    m_Player = new ImcPlayer(sf::Vector2f(40.0f, 350.0f));
    srand(time(NULL));

    m_TextFont.loadFromFile("res/JetBrainsMonoNerdFont-ExtraLightItalic.ttf");
    m_PointsTextCounter.setFont(m_TextFont);
    m_PointsTextCounter.setCharacterSize(25.0f);
    m_PointsTextCounter.setFillColor(sf::Color(32.0f, 200.0f, 80.0f, 200.0f));
    m_PointsTextCounter.setLetterSpacing(1.5f);
    m_PointsTextCounter.setPosition(50.0f, 670.0f);
    m_PointsTextCounter.setString("Points: 0");
    m_HealthText.setFont(m_TextFont);
    m_HealthText.setCharacterSize(27.0f);
    m_HealthText.setFillColor(sf::Color(205.0f, 32.0f, 50.0f, 200.0f));
    m_HealthText.setLetterSpacing(1.5f);
    m_HealthText.setPosition(1020.0f, 670.0f);
    m_HealthText.setString("Health: 100");

    texture.loadFromFile("res/background.png");
    textureBackground.setSize(sf::Vector2f(1280, 720));
    textureBackground.setTexture(&texture);

    music.openFromFile("res/GameSong.wav");
    music.setLoop(true);
    music.setVolume(95);

    shootSoundBuffer.loadFromFile("res/laserShoot.wav");
    shootSound.setBuffer(shootSoundBuffer);
    shootSound.setVolume(70);
    hitSoundBuffer.loadFromFile("res/hitHurt.wav");
    killSound.setBuffer(hitSoundBuffer);
    killSound.setVolume(70);
}

ImcApp::~ImcApp()
{
    delete m_Window;
    for(auto enemy : m_Enemies)
        delete enemy;
    m_Enemies.clear();
    m_Enemies.shrink_to_fit();
}

void ImcApp::MainLoop()
{
    music.play();
    while(m_Window->getWindow().isOpen() && isDead == false)
    {
        m_Dt = m_DtClock.restart().asSeconds();
        // start = std::chrono::high_resolution_clock::now();

        Input();

        Update();

        Render();
        // end = std::chrono::high_resolution_clock::now();

        // float fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
        // std::cout << fps << '\n';
    }
}

void ImcApp::Render()
{
    m_Window->getWindow().clear(sf::Color::Black);
    m_Window->Draw(textureBackground);
    for(auto& bullet : m_Bullets)
    {
        bullet.Render(m_Window->getWindow());
    }
    for(auto& enemy : m_Enemies)
    {
        enemy->Render(m_Window->getWindow());
    }
    m_Player->Render(m_Window->getWindow());
    m_Window->Draw(m_PointsTextCounter);
    m_Window->Draw(m_HealthText);
    m_Window->getWindow().display();
}

void ImcApp::Input()
{
    while(m_Window->getWindow().pollEvent(m_Event))
    {
        switch (m_Event.type)
        {
        case sf::Event::Closed:
            m_Window->closeWindow();
            break;
        case sf::Event::KeyPressed:
            switch (m_Event.key.code)
            {
            case sf::Keyboard::Escape:
                m_Window->closeWindow();
                break;
            default:
                break;
            }
            break;
        case sf::Event::KeyReleased:
            switch (m_Event.key.code)
            {
            case sf::Keyboard::Space:
                shootSound.play();
                ShootBullet();
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void ImcApp::Update()
{
    m_Player->Update(m_Dt);
    for(int e = 0; e < m_Enemies.size(); e++)
    {
        m_Enemies[e]->Update(m_Dt);
        if(m_Enemies[e]->killTimer.getElapsedTime().asSeconds() >= 5.50f)
        {
            m_Enemies.erase(m_Enemies.begin() + e);
        }
        if(m_Enemies[e]->GetRect().intersects(m_Player->GetRect()))
        {
            m_Enemies.erase(m_Enemies.begin() + e);
            m_Player->health -= 10;
            std::string health = "Health: " + std::to_string(m_Player->health);
            m_HealthText.setString(health);
            killSound.play();
        }
        for(int b = 0; b < m_Bullets.size(); b++)
        {
            if(m_Bullets[b].GetRect().intersects(m_Enemies[e]->GetRect()) && m_Enemies[e]->GetPos().x <= 1280)
            {
                m_Bullets[b].health--;
                if(m_Bullets[b].health <= 0)
                {
                    m_Bullets.erase(m_Bullets.begin() + b);
                }
                m_Enemies.erase(m_Enemies.begin() + e);
                killSound.play();
                m_Player->points++;
                std::string p = "Points: " + std::to_string(m_Player->points);
                m_PointsTextCounter.setString(p);
            }
        }
    }

    for(int b = 0; b < m_Bullets.size(); b++)
    {
        m_Bullets[b].Update(m_Dt);
        if(m_Bullets[b].killTimer.getElapsedTime().asSeconds() >= 5.50f)
        {
            m_Bullets.erase(m_Bullets.begin() + b);
        }
    }
    SpawnStageEnemies();

    if(difficultySpawner >= 18.0f)
    {
        difficultySpawner = 18.0f;
        shouldIncreaseDifficulty = false;
    }

    if(m_Player->health <= 0)
    {
        isDead = true;
    }
}

void ImcApp::ShootBullet()
{
    sf::Vector2f posCenter;
    posCenter.x = m_Player->GetPos().x + 60.0f;
    posCenter.y = m_Player->GetPos().y + 21.0f;
    ImcBullet bullet(posCenter);
    m_Bullets.push_back(bullet);
}

void ImcApp::SpawnStageEnemies()
{
    if(m_StageCounterClock.getElapsedTime().asSeconds() >= 6.5f)
    {
        for(int i = 0; i < difficultySpawner; i++)
        {
            float randX = rand() % 300 + 1280;
            float randY = rand() % 690;
            ImcEnemy *enemy = new ImcEnemy(sf::Vector2f((float)randX, (float)randY));
            m_Enemies.push_back(enemy);
        }
        m_StageCounterClock.restart();
        if(shouldIncreaseDifficulty == true)
        {
            difficultySpawner += 2.0f;
            std::cout << difficultySpawner << '\n';
        }
    }
}
