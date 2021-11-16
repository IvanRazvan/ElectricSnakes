#include "Settings.h"
#include "Application.h"
#include "Scene.h"
#include "MainMenu.h"
#include "Game.h"

// This function pushes a scene on top of the stack.
void Application::PushScene()
{
    m_pushScene = false;
    m_scenes.push(m_sceneToPush);
    m_scenes.top()->Init(this);
    m_sceneToPush = nullptr;
}

// This function pops the scene on top of the stack.
void Application::PopScene()
{
    m_popScene = false;
    if (!m_scenes.empty())
    {
        m_scenes.pop();
    }
}

// This initialises the application.
Application::Application()
{
    // We create the seed.
    srand(time(NULL));

    // We create the window.
    m_window = std::make_shared <sf::RenderWindow>(sf::VideoMode(screenWidth, screenHeight), "C++ Snake ICA : A0001151");

    // We load the font.
    m_font = std::make_shared <sf::Font>();
    if (!m_font->loadFromFile("_font.ttf"))
    {
        std::cout << "Font not found.";
        system("pause");
        exit(1);
    }
    else
    {
        std::cout << "Font used: https://www.dafont.com/alphakind.font \n";
    }

    // We load the music.
    m_music = std::make_shared <sf::Music>();
    if (!m_music->openFromFile("_music.ogg"))
    {
        std::cout << "Music not found.";
        system("pause");
        exit(1);
    }
    else
    {
        std::cout << "Music used: https://youtu.be/4Yn174EAEwk \n";
        m_music->setLoop(true);
        m_music->play();
    }
}

// This functions flags a pending push for the next loop iteration.
void Application::RequestPushScene(std::shared_ptr<Scene> newScene)
{
    m_pushScene = true;
    m_sceneToPush = newScene;
}

// This functions flags a pending pop for the next loop iteration.
void Application::RequestPopScene()
{
    m_popScene = true;
}

// This functions holds the main loop.
void Application::Run()
{
    sf::Clock delayClock;
    bool gameIsRunning{ true };

    // We push the menu scene.
    std::shared_ptr<MainMenu> menu = std::make_shared<MainMenu>();
    RequestPushScene(menu);

    // Main loop that continues until we call window.close()
    while (m_window->isOpen() && gameIsRunning)
    {
        // We process the pending push or pop.
        if (m_popScene)
            PopScene();
        if (m_pushScene)
            PushScene();

        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window->close();
                break;
            default:
                break;
            }
        }

        // We update and render the scene on top of the stack.
        m_scenes.top()->Update();     
        m_scenes.top()->Render();

        while (delayClock.getElapsedTime().asMilliseconds() < millisecondsDelay);
        delayClock.restart();
    }

    // We empty the stack.
    while (!m_scenes.empty())
        m_scenes.pop();
}

std::shared_ptr<sf::RenderWindow>& Application::GetWindow()
{
    return m_window;
}

std::shared_ptr<sf::Font>& Application::GetFont()
{
    return m_font;
}
