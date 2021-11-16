#include "BackButton.h"
#include "Application.h"

BackButton::BackButton(Application* application, sf::Vector2f position, sf::Vector2f size, std::string text, int characterSize, sf::Color textColour, int borderThickness, sf::Color outlineColour)
	:Button(application, position, size, text, characterSize, textColour, borderThickness, outlineColour)
{
}

void BackButton::Action()
{
	m_application->RequestPopScene();
}
