#include "Button.h"
#include "TextBox.h"
#include "Application.h"

// This function sets up the button.
Button::Button(Application* application, sf::Vector2f position, sf::Vector2f size, std::string text, int characterSize, sf::Color textColour, int borderThickness, sf::Color outlineColour)
{
	m_application = application;

	SetWindow(m_application->GetWindow());

	m_buttonTexture = std::make_shared<sf::Texture>();
	m_buttonTexture->loadFromFile("_texture_button.png");

	m_box.setSize(size);
	SetPosition(sf::Vector2f(position.x - m_box.getGlobalBounds().width / 2, position.y - m_box.getGlobalBounds().height / 2));
	m_box.setPosition(GetPosition());
	m_box.setTexture(m_buttonTexture.get());

	m_text = std::make_shared<TextBox>(m_application, sf::Vector2f(0,0), EAlignment::eCenter, characterSize, textColour, borderThickness, outlineColour);
	m_text->SetString(text);
	m_text->SetPosition(sf::Vector2f(GetPosition().x + m_box.getGlobalBounds().width / 2, GetPosition().y + m_box.getGlobalBounds().height / 2));

	m_color = m_box.getFillColor();
}

// This function returns true if the mouse is hovering on top of the button, else it returns false.
bool Button::IsHover()
{
	return m_box.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*GetWindow())));
}

// This renders the button on the screen.
void Button::Render()
{
	GetWindow()->draw(m_box);
	m_text->Render();
}

// This updates the button's behaviour.
void Button::Update()
{
	if (IsHover())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			Action();
		else
			m_box.setFillColor(sf::Color(m_color.r / 2, m_color.g / 2, m_color.b / 2));
	}
	else
		m_box.setFillColor(m_color);
}
