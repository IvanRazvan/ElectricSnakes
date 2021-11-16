#include "GameObject.h"

void GameObject::SetPosition(sf::Vector2f newPosition)
{
	m_position = newPosition;
}

sf::Vector2f GameObject::GetPosition() const
{
	return m_position;
}

void GameObject::SetWindow(std::shared_ptr <sf::RenderWindow> window)
{
	m_window = window;
}

std::shared_ptr <sf::RenderWindow> GameObject::GetWindow() const
{
	return m_window;
}
