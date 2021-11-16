#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Game;
class SnakeSegment;
class Collectible;

/*
	EDirection holds all possible directions a snake can move
*/
enum class EDirection {
	eNorth,
	eSouth,
	eEast,
	eWest
};

/*
	SnakeStats holds all relevant information about the snake's specs
*/
struct SnakeStats {
	bool isAlive{ true };
	int score{ 0 };

	bool isElectric{ false };
	int electricityLeft{ 0 };

	std::shared_ptr <SnakeSegment> head;
	EDirection direction;
	std::shared_ptr <sf::Texture> electricityTexture;
	sf::Color colour;
};

/* 
	Snake holds all information about a certain snake.
	On creation, the snake will be assigned with a colour.
	A default snake will start with a lenght of 3 segments.
	A snake will be able to handle interactions with the environment(other snakes, collectibles, walls, itself).
	A snake will move and render itself on the screen.
*/
class Snake
{
protected:
	
	SnakeStats m_stats;
	Game* m_game;
	std::shared_ptr <sf::RenderWindow> m_window;

	void AddSegment();
	void AddSegments(int amount = 1);

	void MoveSnakeBody();
	bool DirectionIsValid(EDirection dir);

	void DisplayElectricity();


	void CollisionWithCollectibles();
	void CollisionWithSnake();
	void CollisionWithSelf();
	void CollisionWithWall();

public:
	Snake(Game* game, std::shared_ptr <sf::RenderWindow> window, sf::Vector2f pos, sf::Color colour);
	
	SnakeStats* GetSnakeStats();
	
	void HandleElectricity();
	void HandleCollisions();

	void ChangeDirection(EDirection dir);
	virtual void Move();

	void Render();
};

