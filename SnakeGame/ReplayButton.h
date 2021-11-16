#pragma once
#include "Button.h"

/*
    ReplayButton is a button reloads the game scene.
*/

class ReplayButton :
    public Button
{
public:
    ReplayButton(Application* application, sf::Vector2f position, sf::Vector2f size, std::string text, int characterSize, sf::Color textColour = sf::Color::White, int borderThickness = 5, sf::Color outlineColour = sf::Color::Black);
    void Action() override;
};

