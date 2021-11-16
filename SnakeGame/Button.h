#pragma once
#include "GameObject.h"

class TextBox;
class Application;
enum class EAlignment;

/*
    Button is a pure virtual class that implements the functionalities of a UI button.
    The Action function will hold the implementation of each button's particular functionality.
*/
class Button :
    public GameObject
{
private:
    std::shared_ptr <TextBox> m_text;
    sf::RectangleShape m_box;
    sf::Color m_color;
    std::shared_ptr <sf::Texture> m_buttonTexture;
protected:
    Application* m_application;
public:
    explicit Button(Application* application, sf::Vector2f position, sf::Vector2f size, std::string text, int characterSize, sf::Color textColour = sf::Color::White, int borderThickness = 5, sf::Color outlineColour = sf::Color::Black);
    bool IsHover();
    void Render();
    void Update();
    virtual void Action() = 0;
};

