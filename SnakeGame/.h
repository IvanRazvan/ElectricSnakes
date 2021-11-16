#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class SnakeSegment;

class SegmentList
{
private:
	SnakeSegment* m_start;
public:
	SegmentList() { m_start->m_next = NULL; }
	void Add(sf::Vector2f newSegment);
};

