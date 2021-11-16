#include "Snake.h"
#include "SnakeSegment.h"
#include "Settings.h"
#include "Game.h"
#include "Collectible.h"

// This function adds a new segment to the tail.
void Snake::AddSegment()
{
	std::shared_ptr <SnakeSegment> tmp = m_stats.head;

	while (tmp->m_next != NULL)
		tmp = tmp->m_next;

	tmp->m_next = std::make_shared<SnakeSegment>(m_window, tmp->GetPosition());
}

// This function adds a certain amout of new segments to the tail.
void Snake::AddSegments(int amount)
{
	for (int i = 0; i < amount; i++)
		AddSegment();
}

// This function moves the last segment of the tail to where the head should go.
void Snake::MoveSnakeBody()
{
	//If there is no head, it means the snake is dead.
	if (m_stats.head == nullptr)
	{
		m_stats.isAlive = false;
		return;
	}

	//We loop through every segment until we reach the last one.
	std::shared_ptr <SnakeSegment> tmp1 = m_stats.head;

	while (tmp1->m_next->m_next != NULL)
	{
		tmp1 = tmp1->m_next;
	}

	std::shared_ptr <SnakeSegment> tmp2 = tmp1->m_next;
	tmp1->m_next = NULL;
	tmp2->m_next = m_stats.head;
	m_stats.head = tmp2;

	//Depending on the direction the snake is moving, we place the last segment on the right position.
	switch (m_stats.direction)
	{
	case EDirection::eNorth:
		m_stats.head->SetPosition(m_stats.head->m_next->GetPosition() + sf::Vector2f(0.0f, -2 * kRadius));
		break;
	case EDirection::eSouth:
		m_stats.head->SetPosition(m_stats.head->m_next->GetPosition() + sf::Vector2f(0.0f, 2 * kRadius));
		break;
	case EDirection::eEast:
		m_stats.head->SetPosition(m_stats.head->m_next->GetPosition() + sf::Vector2f(2 * kRadius, 0.0f));
		break;
	case EDirection::eWest:
		m_stats.head->SetPosition(m_stats.head->m_next->GetPosition() + sf::Vector2f(-2 * kRadius, 0.0f));
		break;
	default:
		break;
	}

	//We decrease the remaining electricity charges.
	if (m_stats.electricityLeft > 0)
		m_stats.electricityLeft--;
	else
		m_stats.isElectric = false;
}

// This function doesn't allow the snake to turn back into its own body.
bool Snake::DirectionIsValid(EDirection dir)
{
	if (m_stats.direction == EDirection::eNorth && dir == EDirection::eSouth)
		return false;
	if (m_stats.direction == EDirection::eSouth && dir == EDirection::eNorth)
		return false;
	if (m_stats.direction == EDirection::eEast && dir == EDirection::eWest)
		return false;
	if (m_stats.direction == EDirection::eWest && dir == EDirection::eEast)
		return false;

	return true;
}

// This function displays the electricity power-up on the screen.
void Snake::DisplayElectricity()
{
	if (m_stats.isElectric)
	{
		// We loop through every segment.
		std::shared_ptr <SnakeSegment> tmp = m_stats.head;

		while (tmp != nullptr)
		{
			// Using the GetDistance function, we render the electricity texture only on the tiles that are at most 2 units away.
			for (int i = -2; i <= 2; i++)
				for (int j = -2; j <= 2; j++)
				{
					if (m_game->GetDistance(sf::Vector2f(tmp->GetPosition().x + i * 2 * kRadius, tmp->GetPosition().y + j * 2 * kRadius), tmp->GetPosition()) <= 2)
					{
						sf::RectangleShape electricity;
						electricity.setSize(sf::Vector2f(2 * kRadius, 2 * kRadius));
						electricity.setPosition(sf::Vector2f(tmp->GetPosition().x + i * 2 * kRadius, tmp->GetPosition().y + j * 2 * kRadius));
						electricity.setOrigin(kRadius, kRadius);
						electricity.setTexture(m_stats.electricityTexture.get());
						electricity.setRotation((rand() % 6) * 60);
						m_window->draw(electricity);
					}
				}

			tmp = tmp->m_next;
		}
	}
}

// This function handles the interaction with other snakes while the electricity power-up is active.
void Snake::HandleElectricity()
{
	if (m_stats.isElectric)
	{
		// We loop through every snake.
		for (std::shared_ptr<Snake> s : m_game->GetSnakes())
		{
			// We skip a snake if its this one, dead or is also has the electricity power-up.
			if (s.get() == this || s->m_stats.isAlive == false || s->m_stats.isElectric)
				continue;

			// We loop through that snake's segments.
			std::shared_ptr <SnakeSegment> otherTmp = s->m_stats.head;

			while (otherTmp != nullptr)
			{
				std::shared_ptr <SnakeSegment> thisTmp = m_stats.head;

				// For each of its segment, we loop through this snake's segments.
				while (thisTmp != nullptr && otherTmp != nullptr)
				{	
					// If both segments are closer than 2 units away, this snake will cut through the other one.
					if (m_game->GetDistance(thisTmp->GetPosition(), otherTmp->GetPosition()) <= 2)
					{
						otherTmp->m_next = nullptr;
						otherTmp = nullptr;

						if (s->m_stats.head == nullptr || s->m_stats.head->m_next == nullptr)
							s->m_stats.isAlive = false;
					}

					if(thisTmp!=nullptr)
						thisTmp = thisTmp->m_next;
				}

				if(otherTmp!=nullptr)
					otherTmp = otherTmp->m_next;
			}
		}
	}
}

// This function handles the interaction with collectibles.
void Snake::CollisionWithCollectibles()
{
	// We loop through all collectibles and collect the active ones upon collision.
	for (std::shared_ptr<Collectible> c : m_game->GetCollectibles())
		if (c->IsActive() && m_stats.head->GetPosition() == c->GetPosition())
		{
			m_stats.score = m_stats.score + 100 * c->GetValue();
			
			if (c->IsBattery())
			{
				// If it's a battery, we toggle on the electricity power-up.
				m_stats.isElectric = true;
				m_stats.electricityLeft = c->GetValue();
			}
			else
			{
				// If it's a normal collectible, we increase the tail.
				AddSegments(c->GetValue());
			}

			// We then toggle off the collectible.
			c->ToggleActive();
		}

}

// This function handles the interaction with other snakes.
void Snake::CollisionWithSnake()
{
	// We loop through all snakes.
	for (std::shared_ptr<Snake> s : m_game->GetSnakes())
	{
		// We skip the snake if it's this one, or it's dead.
		if (s.get() == this || s->m_stats.isAlive == false)
			continue;

		// We loop through every segment of that snake.
		std::shared_ptr <SnakeSegment> tmp = s->m_stats.head;

		while (tmp != nullptr)
		{
			// If this snake's head is colling with any of the segments, it dies.
			if (m_stats.head->GetPosition() == tmp->GetPosition())
			{
				if (tmp != s->m_stats.head || (tmp == s->m_stats.head && m_stats.score < s->m_stats.score))
					m_stats.isAlive = false;
			}

			tmp = tmp->m_next;
		}
	}
}

// This function handles the interaction with itself.
void Snake::CollisionWithSelf()
{
	// We loop through every segment except the head.
	std::shared_ptr <SnakeSegment> tmp = m_stats.head->m_next;

	while (tmp != nullptr)
	{
		// If the head is colling with any of the segments, it dies.
		if (m_stats.head->GetPosition() == tmp->GetPosition())
			m_stats.isAlive = false;

		tmp = tmp->m_next;
	}
}

// This function handles the interaction with walls.
void Snake::CollisionWithWall()
{
	// If the head is outside the bounds of the field, the snake dies.
	if (m_stats.head->GetPosition().x <= 0 || m_stats.head->GetPosition().x > fieldWidth || m_stats.head->GetPosition().y <= 0 || m_stats.head->GetPosition().y > fieldHeight)
	{
		m_stats.isAlive = false;
	}
}

// This function sets up the variables of a snake.
Snake::Snake(Game* game, std::shared_ptr <sf::RenderWindow> window, sf::Vector2f pos,sf::Color colour)
	: m_game(game), m_window(window)
{
	m_stats.colour = colour;

	m_stats.electricityTexture = std::make_shared<sf::Texture>();
	m_stats.electricityTexture->loadFromFile("_texture_electricity.png");



	m_stats.head = std::make_shared<SnakeSegment>(m_window, pos);
	AddSegments(2);
}

SnakeStats* Snake::GetSnakeStats()
{
	return &m_stats;
}

// This function handles all collisions.
void Snake::HandleCollisions()
{
	if (m_stats.isAlive)
	{
		CollisionWithCollectibles();

		if (m_stats.isAlive)
			CollisionWithSnake();

		if (m_stats.isAlive)
			CollisionWithSelf();

		if (m_stats.isAlive)
			CollisionWithWall();
	}
}

// This function changes the snake's direction to a new one, only if it's valid.
void Snake::ChangeDirection(EDirection dir)
{
	if (DirectionIsValid(dir))
		m_stats.direction = dir;
}

// This function moves the snakes body.
void Snake::Move()
{
	MoveSnakeBody();
}

// This function renders the snake on the screen.
void Snake::Render()
{
	if (m_stats.isAlive)
	{
		// We first displays the electricity on the screen.
		DisplayElectricity();

		// If the snake is electric, we emulate a border animation.
		int borderWidth;
		if (m_stats.isElectric)
			borderWidth = m_stats.electricityLeft;
		else
			borderWidth = 1;

		// We loop through each segment and render it on the screen.
		m_stats.head->Render(m_stats.colour, borderWidth, m_stats.isElectric, true);

		std::shared_ptr <SnakeSegment> tmp = m_stats.head->m_next;

		while (tmp != NULL)
		{
			tmp->Render(m_stats.colour, borderWidth, m_stats.isElectric, false);

			tmp = tmp->m_next;
		}
	}
}


