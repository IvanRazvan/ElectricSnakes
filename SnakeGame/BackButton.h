#pragma once
#include "Button.h"

/*
    BackButton is a button that pops the current scene on top of the scenes stack.
*/

class BackButton :
    public Button
{
public:
    BackButton(Application* application, sf::Vector2f position, sf::Vector2f size, std::string text, int characterSize, sf::Color textColour = sf::Color::White, int borderThickness = 5, sf::Color outlineColour = sf::Color::Black);
    void Action() override;
};

