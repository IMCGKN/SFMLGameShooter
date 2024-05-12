#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Window.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "GameObject.hpp"
#include <vector>
#include <chrono>

enum State
{
    GAME_STATE = 0,
    DEATH_STATE = 1
};

class ImcApp
{
public:
    ImcApp();
    ~ImcApp();

    void MainLoop();

    void Render();
    void Input();
    void Update();
private:
    ImcWindow* m_Window;
    sf::Event m_Event;

    sf::Clock m_DtClock;

    sf::Clock m_StageCounterClock;

    sf::Font m_TextFont;
    sf::Text m_PointsTextCounter;
    sf::Text m_HealthText;

    sf::RectangleShape textureBackground;
    sf::Texture texture;

    sf::Music music;
    sf::SoundBuffer shootSoundBuffer;
    sf::SoundBuffer hitSoundBuffer;
    sf::Sound shootSound;
    sf::Sound killSound;

    //Game Objects
    ImcPlayer* m_Player;

    std::vector<ImcBullet> m_Bullets;
    std::vector<ImcEnemy*> m_Enemies;

    void ShootBullet();
    void SpawnStageEnemies();

    float m_Dt;
    int difficultySpawner = 4;

    bool isDead = false;

    // std::chrono::high_resolution_clock::time_point start;
    // std::chrono::high_resolution_clock::time_point end;
    // float fps;

    bool shouldIncreaseDifficulty = true;
};
