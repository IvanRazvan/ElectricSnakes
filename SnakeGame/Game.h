#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Scene.h"

class Application;
class GameObject;
class Snake;
enum class EDirection;
class Collectible;
class TextBox;
class BackButton;
class ReplayButton;

/*
    Game is a Scene that implements the snake game.
    On creation, the Game will set up the scene:
    - it will load all textures
    - it will spawn the snakes and the collectibles
    - it will start the timer
    This class also overrides the Init, Update and Render functions from the Scene class.
*/
class Game :
    public Scene
{
private:
    bool m_isRunning;
    std::vector<std::shared_ptr<Snake>> m_snakes;
    std::vector<std::shared_ptr<Collectible>> m_collectibles;

    sf::Clock m_timer;

    sf::RectangleShape m_hud;
    std::shared_ptr <sf::Texture> m_hudTexture;

    sf::RectangleShape m_field;
    std::shared_ptr <sf::Texture> m_fieldTexture;

    std::shared_ptr <TextBox> m_countDown;
    std::shared_ptr <TextBox> m_highscores;

    std::shared_ptr <BackButton> m_backButton;
    std::shared_ptr <ReplayButton> m_replayButton;

    std::shared_ptr <TextBox> m_winnerText;

    void DisplayHighscores();
    void DisplayWinner();

    void SpawnCollectibles();
    void SpawnSnakes();

public:
    int GetDistance(sf::Vector2f start, sf::Vector2f end);
    bool PositionIsFree(sf::Vector2f pos);
    bool PositionIsSafe(sf::Vector2f pos, Snake* snake);
    sf::Vector2f GetFreePosition();

    std::vector<std::shared_ptr<Snake>>& GetSnakes();
    std::vector<std::shared_ptr<Collectible>>& GetCollectibles();

    void Init(Application* application) override;
    void Update() override;
    void Render() override;
};

