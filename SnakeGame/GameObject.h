#pragma once

#include "Settings.h"

/*
	A base class used to hold the position of an entity, along with its target render window. 
*/
class GameObject
{
private:
	sf::Vector2f m_position;
	std::shared_ptr <sf::RenderWindow> m_window;
public:
	void SetPosition(sf::Vector2f newPosition);
	sf::Vector2f GetPosition() const;

	void SetWindow(std::shared_ptr <sf::RenderWindow> window);
	std::shared_ptr <sf::RenderWindow> GetWindow() const;
};

