#pragma once
#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"

class Scene;

/*
	Application is the main class of the project.
	It implements a stack of scenes in order to compute and display the contents of the game.
*/
class Application
{
private:
	std::shared_ptr <sf::RenderWindow> m_window;
	std::shared_ptr <sf::Font> m_font;
	std::shared_ptr <sf::Music> m_music;

	bool m_popScene{ false };
	bool m_pushScene{ false };
	std::shared_ptr<Scene> m_sceneToPush;

	std::stack<std::shared_ptr<Scene>> m_scenes;

	void PushScene();
	void PopScene();

public:
	Application();
	void RequestPushScene(std::shared_ptr<Scene> newScene);
	void RequestPopScene();
	void Run();

	std::shared_ptr <sf::RenderWindow>& GetWindow();
	std::shared_ptr <sf::Font>& GetFont();
};

