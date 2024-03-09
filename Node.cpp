#include "Node.h"


my::PathNode::PathNode()
{
	
	
}

my::PathNode::~PathNode()
{
}

void my::PathNode::AddPathNode(sf::Vector2f posref)
{
	IntersectionNode *ref = new IntersectionNode(posref.x,posref.y);
	

	// Update position based on vectorPosition (e.g., add or subtract)
	/*sf::Vector2f vectorPosition(8, 8);
	position -= vectorPosition;*/

	
	ref->text->setString(std::to_string(pathNodes.size()));

	pathNodes.push_back(*ref);
	
}

void my::PathNode::DrawPathNode(sf::RenderWindow& window, bool drawtext)
{
	for (size_t i = 0; i<pathNodes.size();i++)
	{
		window.draw(pathNodes[i].circle);
		if (drawtext)
		{
			window.draw(*pathNodes[i].text);

		}
	}
}

