#include "SnakeSegment.h"

// This function sets up the variables.
SnakeSegment::SnakeSegment(std::shared_ptr <sf::RenderWindow> window, sf::Vector2f position)
{
	SetPosition(position);
	SetWindow(window);
	m_next = nullptr;

	m_snakeSegmentTexture = std::make_shared<sf::Texture>();
	m_snakeSegmentTexture->loadFromFile("_texture_snake_segment.png");
}

// This function renders the segment on the screen.
void SnakeSegment::Render(sf::Color colour, int borderThinckness, bool isElectric, bool isHead)
{

	sf::Color outline;
	
	// If the snake is electric, the outline's width and colour will be determined by the amount of electricity left
	if (isElectric)
	{
		outline = sf::Color(20, 80, 150);
	}
	else
	{
		outline = sf::Color::White;
	}
		
	if (isHead)
	{
		// If it's the head, the shape of the segment will be a hexagon.
		sf::CircleShape head(kRadius - borderThinckness, 6);
		head.setPosition(GetPosition());
		head.setOrigin(kRadius - borderThinckness, kRadius - borderThinckness);
		head.setFillColor(colour);
		head.setOutlineColor(outline);
		head.setOutlineThickness(borderThinckness);
		head.setTexture(m_snakeSegmentTexture.get());
		GetWindow()->draw(head);
	}
	else
	{
		// If it's not the head, the shape of the segment will be a circle.
		sf::CircleShape segment(kRadius - borderThinckness);
		segment.setPosition(GetPosition());
		segment.setOrigin(kRadius - borderThinckness, kRadius - borderThinckness);
		segment.setFillColor(colour);
		segment.setOutlineColor(outline);
		segment.setOutlineThickness(borderThinckness);
		segment.setTexture(m_snakeSegmentTexture.get());
		GetWindow()->draw(segment);
	}
}
