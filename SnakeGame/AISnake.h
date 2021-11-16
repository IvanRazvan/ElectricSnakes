#pragma once
#include "Snake.h"

/*
    AISnake expands on the Snake class by implementing the behaviour of an AI controlled snake.
    On creation, the snake will be assigned with a colour.
    The AI will keep moving towards the closest collectible while avoiding collisions at all costs.
*/
class AISnake :
    public Snake
{
private:
    std::shared_ptr<Collectible> GetClosestCollectible(sf::Vector2f pos);
    EDirection GetSafeDirection(sf::Vector2f pos);
public:
    AISnake(Game* game, std::shared_ptr <sf::RenderWindow> window, sf::Vector2f pos, sf::Color colour);
    void Move() override;
};

