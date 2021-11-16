#include "SegmentList.h"
#include "SnakeSegment.h"

void SegmentList::Add(sf::Vector2f newSegment)
{
	SnakeSegment* tmp = m_start;

	while (tmp->m_next != NULL)
		tmp = tmp->m_next;

	tmp->m_next = new SnakeSegment(newSegment);
}
