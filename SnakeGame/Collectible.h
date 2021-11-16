#pragma once

#include "GameObject.h"

/*
	The collectible class holds variables and methods that are used to render and process a collectible's behaviour.
	A collectible can be set as a battery only at instantiation.
	A collectible can be toggled on or off:
		-when toggled on, its value will receive a random value and it will be repositioned to an empty spot.
		-when toggled off, it won't interact with anything in the game.
*/

class Collectible : 
	public GameObject
{
private:
	bool m_isActive{ false };
	int m_value;
	bool m_isBattery{ false };

	sf::Color m_colour;
	std::shared_ptr <sf::Texture> m_collectibleTexture;
	std::shared_ptr <sf::Texture> m_auraTexture;

public:
	Collectible(std::shared_ptr<sf::RenderWindow> window, sf::Color colour = sf::Color::Yellow, bool isBattery = false);
	
	int GetValue() const;
	bool IsActive() const;
	bool IsBattery() const;
	
	void ToggleActive();
	void Render();
};

