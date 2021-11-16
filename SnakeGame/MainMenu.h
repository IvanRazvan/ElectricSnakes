#pragma once
#include "Scene.h"

class ExitButton;
class PlayButton;

/*
	MainMenu is a Scene that implements the menu for the game.
	On creation, the MainMenu will set up the scene:
	- it will load all textures
	- it will create the UI
	This class also overrides the Init, Update and Render functions from the Scene class.
*/
class MainMenu :
    public Scene
{
private:
	std::shared_ptr <PlayButton> m_playButton;
	std::shared_ptr <ExitButton> m_exitButton;

	sf::RectangleShape m_background;
	std::shared_ptr <sf::Texture> m_backgroundTexture;
public:
	void Init(Application* application) override;
	void Update() override;
	void Render() override;
};

