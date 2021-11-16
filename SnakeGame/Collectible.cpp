#include "Collectible.h"

//Sets up variables and loads appropriate textures
Collectible::Collectible(std::shared_ptr<sf::RenderWindow> window, sf::Color colour, bool isBattery)
	: m_colour(colour - sf::Color(0,0,0,200)), m_isBattery(isBattery)
{
	SetWindow(window);

	m_collectibleTexture = std::make_shared<sf::Texture>();

	if(isBattery)
		m_collectibleTexture->loadFromFile("_texture_battery.png");
	else
		m_collectibleTexture->loadFromFile("_texture_collectible.png");

	m_auraTexture = std::make_shared<sf::Texture>();
	m_auraTexture->loadFromFile("_texture_aura.png");
}


int Collectible::GetValue() const
{
	return m_value;
}

bool Collectible::IsActive() const
{
	return m_isActive;
}

bool Collectible::IsBattery() const
{
	return m_isBattery;
}

void Collectible::ToggleActive()
{
	m_isActive = !m_isActive;

	if (m_isActive)
		m_value = 3 + rand() % 5;
}

void Collectible::Render()
{
	if (m_isActive)
	{
		//Render the aura around the collectible
		sf::CircleShape aura(GetValue() * kRadius);
		aura.setPosition(GetPosition());
		aura.setOrigin(GetValue() * kRadius, GetValue() * kRadius);
		aura.setFillColor(m_colour);
		aura.setTexture(m_auraTexture.get());
		GetWindow()->draw(aura);

		//Render the texture of the collectible
		sf::RectangleShape collectible;
		collectible.setSize(sf::Vector2f(2 * kRadius + 3, 2 * kRadius + 3));
		collectible.setPosition(GetPosition());
		collectible.setOrigin(kRadius + 1.5f, kRadius + 1.5f);
		collectible.setTexture(m_collectibleTexture.get());
		GetWindow()->draw(collectible);
	}
}
