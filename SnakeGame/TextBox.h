#pragma once

#include "GameObject.h"

class Application;

/*
	EAlignment is an enum class that holds the possible alignments of a text
*/
enum class EAlignment {
	eLeft,
	eCenter,
	eRight
};

/*
	TextBox is a class that handles the rendering of a text on the screen.
*/
class TextBox :
	public GameObject
{
private:
	EAlignment m_alignment;
	sf::Text m_text;
public:
	TextBox(Application* application, sf::Vector2f position, EAlignment alignment, int characterSize, sf::Color textColour, int borderThickness = 5, sf::Color outlineColour = sf::Color::Black);
	void ChangeColour(sf::Color textColour, sf::Color outlineColour = sf::Color::Black);
	void ChangeAlignment(EAlignment alignment);
	void SetString(std::string string);
	sf::Vector2f GetGlobalBounds();
	void Render();
};

