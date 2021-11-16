#include "PlayButton.h"
#include "Application.h"
#include "Game.h"

PlayButton::PlayButton(Application* application, sf::Vector2f position, sf::Vector2f size, std::string text, int characterSize, sf::Color textColour, int borderThickness, sf::Color outlineColour)
	:Button(application, position, size, text, characterSize, textColour, borderThickness, outlineColour)
{
}

void PlayButton::Action()
{
	m_application->RequestPushScene(std::make_shared<Game>());
}
