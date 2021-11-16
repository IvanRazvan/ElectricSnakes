#include "AISnake.h"
#include "Collectible.h"
#include "Settings.h"
#include "SnakeSegment.h"
#include "Game.h"

// This function returns the closest active collectible.
std::shared_ptr<Collectible> AISnake::GetClosestCollectible(sf::Vector2f pos)
{
    int shortestDistance = INT_MAX;
    std::shared_ptr<Collectible> target = nullptr;

    for (std::shared_ptr<Collectible> c : m_game->GetCollectibles())
        if (m_game->GetDistance(pos, c->GetPosition()) < shortestDistance && c->IsActive())
        {
            shortestDistance = m_game->GetDistance(pos, c->GetPosition());
            target = c;
        }

    return target;
}

// This function returns a safe direction.
EDirection AISnake::GetSafeDirection(sf::Vector2f pos)
{
    if (m_game->PositionIsSafe(pos + sf::Vector2f(0.0f, -2 * kRadius), this))
        return EDirection::eNorth;

    if (m_game->PositionIsSafe(pos + sf::Vector2f(0.0f, 2 * kRadius), this))
        return EDirection::eSouth;

    if (m_game->PositionIsSafe(pos + sf::Vector2f(2 * kRadius, 0.0f), this))
        return EDirection::eEast;

    if (m_game->PositionIsSafe(pos + sf::Vector2f(-2 * kRadius, 0.0f), this))
        return EDirection::eWest;

    return EDirection::eNorth;
}

AISnake::AISnake(Game* game, std::shared_ptr<sf::RenderWindow> window, sf::Vector2f pos, sf::Color colour)
    :Snake(game, window, pos, colour)
{
}

// This function will try to move the snake towards the closest collectible. 
void AISnake::Move()
{
    // We begin by getting a reference to the closest collectible.
    std::shared_ptr<Collectible> target = GetClosestCollectible(m_stats.head->GetPosition());
    int distance = INT_MAX;
    EDirection newDir;

    if (target == nullptr)
    {
        // If the collectible doesn't exists, we follow a safe direction.
        ChangeDirection(GetSafeDirection(m_stats.head->GetPosition()));
    }
    else
    {
        // If the collectible exists, we check which direction will safely get us closer to it.

        sf::Vector2f attemptPos;
        attemptPos = m_stats.head->GetPosition() + sf::Vector2f(0.0f, -2 * kRadius);
        if (distance > m_game->GetDistance(attemptPos, target->GetPosition()) && m_game->PositionIsSafe(attemptPos, this) && DirectionIsValid(EDirection::eNorth))
        {
            newDir = EDirection::eNorth;
            distance = m_game->GetDistance(attemptPos, target->GetPosition());
        }

        attemptPos = m_stats.head->GetPosition() + sf::Vector2f(0.0f, 2 * kRadius);
        if (distance > m_game->GetDistance(attemptPos, target->GetPosition()) && m_game->PositionIsSafe(attemptPos, this) && DirectionIsValid(EDirection::eSouth))
        {
            newDir = EDirection::eSouth;
            distance = m_game->GetDistance(attemptPos, target->GetPosition());
        }

        attemptPos = m_stats.head->GetPosition() + sf::Vector2f(2 * kRadius, 0.0f);
        if (distance > m_game->GetDistance(attemptPos, target->GetPosition()) && m_game->PositionIsSafe(attemptPos, this) && DirectionIsValid(EDirection::eEast))
        {
            newDir = EDirection::eEast;
            distance = m_game->GetDistance(attemptPos, target->GetPosition());
        }

        attemptPos = m_stats.head->GetPosition() + sf::Vector2f(-2 * kRadius, 0.0f);
        if (distance > m_game->GetDistance(attemptPos, target->GetPosition()) && m_game->PositionIsSafe(attemptPos, this) && DirectionIsValid(EDirection::eWest))
        {
            newDir = EDirection::eWest;
            distance = m_game->GetDistance(attemptPos, target->GetPosition());
        }

        // If no direction was at least safe, we go North.
        if (distance == INT_MAX)
        {
            newDir = EDirection::eNorth;
        }

        // We move the snake in the best direction we could find.
        ChangeDirection(newDir);
    }

    // We compute the snakes movement.
    MoveSnakeBody();
}
