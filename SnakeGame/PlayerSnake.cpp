#include "PlayerSnake.h"

PlayerSnake::PlayerSnake(Game* game, std::shared_ptr<sf::RenderWindow> window, sf::Vector2f pos)
	:Snake(game, window, pos, sf::Color::White)
{
    m_stats.direction = EDirection::eNorth;
}

// This function handles the movement.
void PlayerSnake::Move()
{
    // We get the input from the keyboard and change the direction accordingly.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        ChangeDirection(EDirection::eNorth);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        ChangeDirection(EDirection::eSouth);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ChangeDirection(EDirection::eEast);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        ChangeDirection(EDirection::eWest);
    }

    // We compute the snakes movement.
    MoveSnakeBody();
}
