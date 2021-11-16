#pragma once
#include "Snake.h"

/*
	PlayerSnake expands on the Snake class by implementing the behaviour of a player controlled snake.
	On creation, the snake will be assigned with the colour white.
    A player can control it using WASD or the arrow keys.
*/
class PlayerSnake :
    public Snake
{
private:
public:
    PlayerSnake(Game* game, std::shared_ptr <sf::RenderWindow> window, sf::Vector2f pos);
    void Move() override;
};

