#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Application;

/*
	This class is used in a stack structure inside the Application class.
	It is a pure virtual class that is used to create a scene for the application.
	Its main functions are Init, Update and Render.
*/
class Scene
{
protected:
	Application* m_application;
public:
	virtual void Init(Application* application) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	Application* GetApplication();
};

