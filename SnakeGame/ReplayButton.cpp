#include "ReplayButton.h"
#include "Application.h"
#include "Game.h"

ReplayButton::ReplayButton(Application* application, sf::Vector2f position, sf::Vector2f size, std::string text, int characterSize, sf::Color textColour, int borderThickness, sf::Color outlineColour)
	:Button(application, position, size, text, characterSize, textColour, borderThickness, outlineColour)
{
}

void ReplayButton::Action()
{
	m_application->RequestPopScene();
	m_application->RequestPushScene(std::make_shared<Game>());
}
