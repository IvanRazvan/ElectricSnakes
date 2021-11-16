#pragma once
#include "Button.h"

/*
    ExitButton is a button that closes the application.
*/

class ExitButton :
    public Button
{
public:
    ExitButton(Application* application, sf::Vector2f position, sf::Vector2f size, std::string text, int characterSize, sf::Color textColour = sf::Color::White, int borderThickness = 5, sf::Color outlineColour = sf::Color::Black);
    void Action() override;
};

