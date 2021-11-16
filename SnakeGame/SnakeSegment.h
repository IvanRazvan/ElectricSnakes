#pragma once

#include "GameObject.h"

/*
	SnakeSegment a texture to render and a pointer to another SnakeSegment.
	This class is used in a list structure.
*/

class SnakeSegment :
	public GameObject
{
private:
	std::shared_ptr <sf::Texture> m_snakeSegmentTexture;
public:
	std::shared_ptr <SnakeSegment> m_next;

	SnakeSegment(std::shared_ptr <sf::RenderWindow> window, sf::Vector2f position);

	void Render(sf::Color colour, int borderThinckness, bool isElectric, bool isHead);
};

