#include "Game.h"
#include "Settings.h"
#include "Application.h"
#include "Snake.h"
#include "AISnake.h"
#include "PlayerSnake.h"
#include "SnakeSegment.h"
#include "Collectible.h"
#include "TextBox.h"
#include "BackButton.h"
#include "ReplayButton.h"

// This function displays the scores on the screen.
void Game::DisplayHighscores()
{
    // We render the Highscore text on the screen.
    m_highscores->Render();

    // We created a new vector in which we will store all the scores.
    std::vector<std::shared_ptr<Snake>> scores;

    for (std::shared_ptr<Snake> s : m_snakes)
        scores.push_back(s);

    // We bubble sort the vector.
    for (int i = 0; i < scores.size() - 1; i++)
        for (int j = 0; j < scores.size() - i - 1; j++)
            if (scores.at(j)->GetSnakeStats()->score < scores.at(j + 1)->GetSnakeStats()->score)
            {
                std::shared_ptr<Snake> aux = scores.at(j);
                scores.at(j) = scores.at(j + 1);
                scores.at(j + 1) = aux;
                aux = nullptr;
            }

    // We firstly display the rankings in a column
    int spacing = 27;
    TextBox currentScore(m_application, { 0, 0 }, EAlignment::eLeft, 27, sf::Color::White, 3);

    for (int i = 0; i < scores.size(); i++)
    {
        currentScore.SetPosition(sf::Vector2f(screenWidth - 240, 200 + spacing * i));

        // If a snake is dead, it's ranking colour will be greyed out.
        if (scores.at(i)->GetSnakeStats()->isAlive)
            currentScore.ChangeColour(sf::Color::White);
        else
            currentScore.ChangeColour(sf::Color(100, 100, 100, 255));
        
        currentScore.SetString(std::to_string(i + 1) + ".");
        currentScore.Render();
    }

    // We then display the scores in a second column. Each score will have the colour of its snake.
    for (int i = 0; i < scores.size(); i++)
    {
        currentScore.SetPosition(sf::Vector2f(screenWidth - 180, 200 + spacing * i));
        currentScore.ChangeColour(scores.at(i)->GetSnakeStats()->colour);
        currentScore.SetString(std::to_string(scores.at(i)->GetSnakeStats()->score));
        currentScore.Render();
    }

    // We clear the vector.
    scores.clear();
}

// This functions displays the winner on the screen.
void Game::DisplayWinner()
{
    // We render an overlay above the screen.
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(screenWidth, screenHeight));
    overlay.setTexture(m_fieldTexture.get());
    overlay.setFillColor(overlay.getFillColor() - sf::Color(0, 0, 0, 100));
    m_application->GetWindow()->draw(overlay);

    // We create a vector to store all the snakes left alive.
    std::vector<std::shared_ptr<Snake>> snakesAlive;

    for (std::shared_ptr<Snake> s : m_snakes)
    {
        if (s->GetSnakeStats()->isAlive)
        {
            snakesAlive.push_back(s);
        }
    }

    // We bubble sort the vector.
    for (int i = 0; i < snakesAlive.size() - 1; i++)
        for (int j = 0; j < snakesAlive.size() - i - 1; j++)
            if (snakesAlive.at(j)->GetSnakeStats()->score < snakesAlive.at(j + 1)->GetSnakeStats()->score)
            {
                std::shared_ptr<Snake> aux = snakesAlive.at(j);
                snakesAlive.at(j) = snakesAlive.at(j + 1);
                snakesAlive.at(j + 1) = aux;
                aux = nullptr;
            }

    // We count how many snakes have the biggest score.
    int nrOfWinners = 0;
    for (std::shared_ptr<Snake> s : snakesAlive)
    {
        if (s->GetSnakeStats()->score < snakesAlive.at(0)->GetSnakeStats()->score)
            break;
        nrOfWinners++;
    }

    // We display all winners on the screen.
    sf::Vector2f position = sf::Vector2f((fieldWidth - (nrOfWinners - 1) * 80) / 2, fieldHeight / 2 + 15);
    TextBox text(m_application, position, EAlignment::eCenter, 30, sf::Color::White);

    for (int i = 0; i < nrOfWinners; i++)
    {
        text.SetPosition(sf::Vector2f(position.x + 20, position.y + 20));
        if (snakesAlive.at(i)->GetSnakeStats()->colour == sf::Color::White)
            text.SetString("You");
        else
            text.SetString("AI");

        sf::CircleShape winner(40, 6);
        winner.setPosition(position);
        position.x += 80;
        winner.setOrigin(20, 20);
        winner.setFillColor(snakesAlive.at(i)->GetSnakeStats()->colour);
        winner.setOutlineColor(sf::Color::White);
        winner.setOutlineThickness(5);

        m_application->GetWindow()->draw(winner);
        text.Render();
    }

    if (nrOfWinners > 1)
        m_winnerText->SetString("Winners");
    else
        m_winnerText->SetString("Winner");

    m_winnerText->Render();

    // We clear the vector.
    snakesAlive.clear();
}

// This functions spawns 5 collectibles and a battery.
void Game::SpawnCollectibles()
{
    // We spawn the battery.
    std::shared_ptr <Collectible> b = std::make_shared <Collectible>(GetApplication()->GetWindow(), sf::Color(20, 80, 150), true);
    b->SetPosition(GetFreePosition());
    b->ToggleActive();
    m_collectibles.emplace_back(b);

    // We another 5 collectibles.
    for (int i = 0; i < 5; i++)
    {
        std::shared_ptr <Collectible> c = std::make_shared <Collectible>(GetApplication()->GetWindow());
        c->SetPosition(GetFreePosition());
        c->ToggleActive();
        m_collectibles.emplace_back(c);
    }
}

// This functions spawns 20 snakes.
void Game::SpawnSnakes()
{
    // We spawn the Player in the middle of the screen, its default colour being white.
    std::shared_ptr<PlayerSnake> s = std::make_shared<PlayerSnake>(this, m_application->GetWindow(), sf::Vector2f(fieldWidth / 2 + kRadius, fieldHeight / 2 + 2 * kRadius));
    m_snakes.emplace_back(s);

    // The AI snakes' colours are not random, in order to avoid having too many simmilar colours.
    std::vector<sf::Color> AISnakeColours;
    #pragma region CustomColours
    AISnakeColours.emplace_back(sf::Color(80, 150, 250, 255));
    AISnakeColours.emplace_back(sf::Color(225, 15, 210, 255));
    AISnakeColours.emplace_back(sf::Color(170, 100, 135, 255));
    AISnakeColours.emplace_back(sf::Color(255, 110, 15, 255));
    AISnakeColours.emplace_back(sf::Color(200, 155, 35, 255));
    AISnakeColours.emplace_back(sf::Color(100, 195, 75, 255));
    AISnakeColours.emplace_back(sf::Color(60, 75, 195, 255));
    AISnakeColours.emplace_back(sf::Color(225, 250, 30, 255));
    AISnakeColours.emplace_back(sf::Color(35, 170, 250, 255));
    AISnakeColours.emplace_back(sf::Color(250, 30, 120, 255));
    AISnakeColours.emplace_back(sf::Color(130, 10, 15, 255));
    AISnakeColours.emplace_back(sf::Color(65, 250, 60, 255));
    AISnakeColours.emplace_back(sf::Color(110, 160, 120, 255));
    AISnakeColours.emplace_back(sf::Color(245, 40, 60, 255));
    AISnakeColours.emplace_back(sf::Color(30, 190, 125, 255));
    AISnakeColours.emplace_back(sf::Color(70, 20, 145, 255));
    AISnakeColours.emplace_back(sf::Color(145, 250, 220, 255));
    AISnakeColours.emplace_back(sf::Color(5, 110, 140, 255));
    AISnakeColours.emplace_back(sf::Color(80, 10, 50, 255));
    #pragma endregion

    // We spawn the 19 AI snakes randomly on the screen.
    for (int i = 0; i < 19; i++)
    {
        std::shared_ptr<AISnake> d = std::make_shared<AISnake>(this, m_application->GetWindow(), GetFreePosition(), AISnakeColours.at(i));
        m_snakes.emplace_back(d);
    }
}

// This functions returns how many units away the end is from the start.
int Game::GetDistance(sf::Vector2f start, sf::Vector2f end)
{
    return (abs(start.x - end.x) + abs(start.y - end.y)) / (2 * kRadius);
}

// This function returns true if a position has nothing on it, else it returns false.
bool Game::PositionIsFree(sf::Vector2f pos)
{
    // If the position is outside the bounds of the field, we return false.
    if (pos.x <= kRadius || pos.x > fieldWidth + 1 || pos.y <= kRadius || pos.y > fieldHeight + 1)
        return false;

    // If the position is occupied by a snake, we return false.
    for (std::shared_ptr<Snake> s : m_snakes)
    {
        if (s->GetSnakeStats()->isAlive == false)
            continue;

        std::shared_ptr <SnakeSegment> tmp = s->GetSnakeStats()->head;
        while (tmp != nullptr)
        {
            if (pos == tmp->GetPosition())
                return false;
            tmp = tmp->m_next;
        }
    }

    // If the position is occupied by a collectible, we return false.
    for (std::shared_ptr<Collectible> c : m_collectibles)
        if (pos == c->GetPosition() && c->IsActive())
            return false;

    // If the position is free, we return true.
    return true;
}

// This function returns true if a position is safe to travel to, else it returns false.
bool Game::PositionIsSafe(sf::Vector2f pos, Snake* snake)
{
    // If the position is outside the bounds of the field, we return false.
    if (pos.x <= kRadius || pos.x > fieldWidth + 1 || pos.y <= kRadius || pos.y > fieldHeight + 1)
        return false;

    // If the position is occupied by a snake, we return false.
    for (std::shared_ptr<Snake> s : m_snakes)
    {
        if (s->GetSnakeStats()->isAlive == false)
            continue;

        std::shared_ptr <SnakeSegment> tmp = s->GetSnakeStats()->head;
        while (tmp != nullptr)
        {
            if (pos == tmp->GetPosition() || (snake != s.get() && s->GetSnakeStats()->isElectric && GetDistance(pos, tmp->GetPosition()) <= 2 ))
                return false;
            tmp = tmp->m_next;
        }
    }

    // If the position is safe, we return true.
    return true;
}

// This function returns a free position.
sf::Vector2f Game::GetFreePosition()
{
    // We keep picking a random position an check if it is free.
    int x, y;
    do {
        x = (rand() % (fieldWidth / (2 * kRadius))) * 2 * kRadius;
        y = (rand() % (fieldHeight / (2 * kRadius))) * 2 * kRadius;
    } while (!PositionIsFree(sf::Vector2f(x, y)));

    return sf::Vector2f(x, y);
}

// This function returns a reference to the snake vector.
std::vector<std::shared_ptr<Snake>>& Game::GetSnakes()
{
    return m_snakes;
}

// This function returns a reference to the collectibles vector.
std::vector<std::shared_ptr<Collectible>>& Game::GetCollectibles()
{
    return m_collectibles;
}

// This function initialises the Game scene.
void Game::Init(Application* application)
{
    m_application = application;

    m_isRunning = true;

    //We set up the UI
    m_fieldTexture = std::make_shared<sf::Texture>();
    m_fieldTexture->loadFromFile("_texture_field.png");
    m_field.setSize(sf::Vector2f(screenWidth, screenHeight));
    m_field.setTexture(m_fieldTexture.get());

    m_hudTexture = std::make_shared<sf::Texture>();
    m_hudTexture->loadFromFile("_texture_HUD.png");
    m_hud.setSize(sf::Vector2f(screenWidth, screenHeight));
    m_hud.setTexture(m_hudTexture.get());

    m_countDown = std::make_shared <TextBox>(m_application, sf::Vector2f(screenWidth - 252, 55), EAlignment::eLeft, 60, sf::Color::White);

    m_highscores = std::make_shared <TextBox>(m_application, sf::Vector2f(screenWidth - 254, 160), EAlignment::eLeft, 40, sf::Color::White);
    m_highscores->SetString("Highscores:");

    m_winnerText = std::make_shared <TextBox>(m_application, sf::Vector2f(fieldWidth/2, fieldHeight/2 - 100), EAlignment::eCenter, 150, sf::Color::White);
    
    m_backButton = std::make_shared <BackButton>(m_application, sf::Vector2f(screenWidth - 75, screenHeight - 80), sf::Vector2f(120, 70), "Menu", 25);
    
    m_replayButton = std::make_shared <ReplayButton>(m_application, sf::Vector2f(screenWidth - 210, screenHeight - 80), sf::Vector2f(120, 70), "Replay", 25);
    
    //We spawn the snakes and the collectibles
    SpawnSnakes();
    SpawnCollectibles();

    //We start the timer
    m_timer.restart();
}

// This function handles one game logic iteration.
void Game::Update()
{
    // If the game is running, we handle the interactions of the snakes and collectibles.
    if (m_isRunning)
    {
        // We move the snakes
        for (std::shared_ptr<Snake> s : m_snakes)
            if (s->GetSnakeStats()->isAlive)
            {
                s->Move();
            }

        // We make sure there is always a battery on the screen.
        if (m_collectibles.at(0)->IsActive() == false)
        {
            m_collectibles.at(0)->SetPosition(GetFreePosition());
            m_collectibles.at(0)->ToggleActive();
        }
        // We may spawn 1 collectible
        if (rand() % 3 == 0)
            for (std::shared_ptr<Collectible> c : m_collectibles)
                if (!c->IsActive())
                {
                    c->SetPosition(GetFreePosition());
                    c->ToggleActive();
                    break;
                }

        // We check collisions after invincibility frames are over
        if ((int)m_timer.getElapsedTime().asSeconds() > 1)
        {
            for (std::shared_ptr<Snake> s : m_snakes)
                s->HandleCollisions();

            for (std::shared_ptr<Snake> s : m_snakes)
                s->HandleElectricity();
        }

        // We count alive snakes and finish game if there is only 1
        int snakesAlive = 0;
        for (std::shared_ptr<Snake> s : m_snakes)
            if (s->GetSnakeStats()->isAlive)
                snakesAlive++;

        if (snakesAlive == 1 || (int)m_timer.getElapsedTime().asSeconds() >= 90)
            m_isRunning = false;
        
        // We update the countdown text.
        m_countDown->SetString("Time:" + std::to_string(90 - (int)m_timer.getElapsedTime().asSeconds()));
    }

    //We update the buttons
    m_backButton->Update();
    m_replayButton->Update();
}

// This function handles one render iteration.
void Game::Render()
{
    // We must clear the window each time around the loop.
    m_application->GetWindow()->clear();

    // We draw the field.
    m_application->GetWindow()->draw(m_field);
    
    // We draw the collectibles.
    for (std::shared_ptr<Collectible> c : m_collectibles)
        c->Render();

    // We draw the snakes.
    for (std::shared_ptr<Snake> s : m_snakes)
        s->Render();

    // We draw the UI.
    m_application->GetWindow()->draw(m_hud);
    DisplayHighscores();
    m_countDown->Render();
    m_backButton->Render();
    m_replayButton->Render();

    // If the game is over, we display the winners.
    if (!m_isRunning)
        DisplayWinner();

    // We get the window to display its contents.
    m_application->GetWindow()->display();
}
