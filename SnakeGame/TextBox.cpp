#include "TextBox.h"
#include "Application.h"

// This function sets the text.
TextBox::TextBox(Application* application, sf::Vector2f position, EAlignment alignment, int characterSize, sf::Color textColour, int borderThickness, sf::Color outlineColour)
    :  m_alignment(alignment)
{
    m_text.setFont(*application->GetFont());
    m_text.setCharacterSize(characterSize);
    m_text.setOutlineThickness(borderThickness);
    m_text.setFillColor(textColour);
    m_text.setOutlineColor(outlineColour);
    SetWindow(application->GetWindow());
    SetPosition(position);
};

// This function changes the colour of the text.
void TextBox::ChangeColour(sf::Color textColour, sf::Color outlineColour)
{
    m_text.setFillColor(textColour);
    m_text.setOutlineColor(outlineColour);
}

// This function changes the alignment of the text.
void TextBox::ChangeAlignment(EAlignment alignment)
{
    m_alignment = alignment;
}

// This function changes the string of the text.
void TextBox::SetString(std::string string)
{
    m_text.setString(string);
}

// This returns a Vector2f containing the width and height of the text.
sf::Vector2f TextBox::GetGlobalBounds()
{
    return sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height);
}

// This function renders the text according to the alignment
void TextBox::Render()
{
    switch (m_alignment)
    {
    case EAlignment::eLeft:
        m_text.setPosition(GetPosition().x, GetPosition().y - m_text.getGlobalBounds().height / 2 - m_text.getCharacterSize() / 10);
        break;
    case EAlignment::eCenter:
        m_text.setPosition(GetPosition().x - m_text.getGlobalBounds().width / 2 + m_text.getCharacterSize() / 10, GetPosition().y - m_text.getGlobalBounds().height / 2 - m_text.getCharacterSize() / 15);
        break;
    case EAlignment::eRight:
        m_text.setPosition(GetPosition().x - m_text.getGlobalBounds().width, GetPosition().y - m_text.getGlobalBounds().height / 2 - m_text.getCharacterSize() / 10);
        break;
    default:
        break;
    }

    GetWindow()->draw(m_text);
}
