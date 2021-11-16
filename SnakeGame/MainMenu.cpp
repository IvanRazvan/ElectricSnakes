#include "MainMenu.h"
#include "ExitButton.h"
#include "PlayButton.h"
#include "Application.h"

// This function initialises the MainMenu scene.
void MainMenu::Init(Application* application)
{
	m_application = application;

	// We set up the UI.
	m_playButton = std::make_shared <PlayButton>(m_application, sf::Vector2f(screenWidth / 2, screenHeight / 2), sf::Vector2f(250, 120), "Play", 40);
	m_exitButton = std::make_shared <ExitButton>(m_application, sf::Vector2f(screenWidth/2, screenHeight/2 + 200), sf::Vector2f(250, 120), "Exit", 40);

	m_backgroundTexture = std::make_shared<sf::Texture>();
	m_backgroundTexture->loadFromFile("_texture_menu.png");
	m_background.setSize(sf::Vector2f(screenWidth, screenHeight));
	m_background.setTexture(m_backgroundTexture.get());
}

// This function handles one menu logic iteration.
void MainMenu::Update()
{
	// We update the buttons.
	m_exitButton->Update();
	m_playButton->Update();
}

// This function handles one render iteration.
void MainMenu::Render()
{
	// We must clear the window each time around the loop.
	m_application->GetWindow()->clear();

	// We render the UI.
	m_application->GetWindow()->draw(m_background);
	m_exitButton->Render();
	m_playButton->Render();

	// We get the window to display its contents.
	m_application->GetWindow()->display();
}
