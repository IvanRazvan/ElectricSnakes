#pragma once
#include "Button.h"

/*
    PlayButton is a button pushes the game scene on the stack.
*/

class PlayButton :
    public Button
{
public:
    PlayButton(Application* application, sf::Vector2f position, sf::Vector2f size, std::string text, int characterSize, sf::Color textColour = sf::Color::White, int borderThickness = 5, sf::Color outlineColour = sf::Color::Black);
    void Action() override;
};

