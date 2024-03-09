#include "TracePath.h"



my::TracePath::TracePath()
{
}

my::TracePath::~TracePath()
{
}

void my::TracePath::AddPath(Direction ref)
{
	float distanceTail, distanceHead;
	sf::Vector2f diff;
	sf::Vector2f diffT;

	bool foundmatch = false;

	if (paths.empty())
	{
		this->paths.push_back(ref);
		sf::Vertex line[2];
		line[0].position = ref.tail;
		line[1].position = ref.head;


		AddLineToPath(drawPaths, line, 1.0f, sf::Color(0, 250, 0));
		AddLineToPath(drawPaths, line, 3.0f, sf::Color(0, 250, 0));
		return;
	}


	for (size_t i = 0; i < paths.size(); i++)
	{
		diff.x = paths[i].head.x - ref.head.x;
		diffT.x = paths[i].tail.x - ref.tail.x;
		diff.y = paths[i].head.y - ref.head.y;
		diffT.y = paths[i].tail.y - ref.tail.y;

		distanceHead = std::sqrt(diff.x * diff.x + diff.y * diff.y);
		distanceTail = std::sqrt(diffT.x * diffT.x + diffT.y * diffT.y);
		

		if (distanceHead <= 3.0f && distanceTail <= 3.0f)
		{
			foundmatch = true;
		}

	}

	if (!foundmatch)
	{

		this->paths.push_back(ref);

		//----for draw paths----
		sf::Vertex line[2];
		line[0].position = ref.tail;
		line[1].position = ref.head;


		AddLineToPath(drawPaths, line, 1.0f, sf::Color(0, 250, 0));
		AddLineToPath(drawPaths, line, 3.0f, sf::Color(0, 250, 0));


	}
	
}

void my::TracePath::DrawPath(sf::RenderWindow& window)
{
	if (drawPaths.empty())
	{
		return;
	}
	window.draw(&drawPaths[0], drawPaths.size(), sf::Lines);
}



void my::TracePath::AddLineToPath(std::vector<sf::Vertex>& paths, sf::Vertex line[2], float thickness, sf::Color color)
{
	sf::Vector2f direction = line[1].position - line[0].position;
	sf::Vector2f normal(direction.y, -direction.x);  // Normal vector for perpendicular lines
	normal = normal / std::sqrt(normal.x * normal.x + normal.y * normal.y); // Normalize for consistent thickness

	// Create vertices for the top and bottom lines of the rectangle
	sf::Vertex topLine[] = {
		line[0].position + normal * thickness / 2.f,
		line[1].position + normal * thickness / 2.f
	};
	sf::Vertex bottomLine[] = {
		line[0].position - normal * thickness / 2.f,
		line[1].position - normal * thickness / 2.f
	};

	topLine[0].color = color;
	topLine[1].color = color;
	bottomLine[0].color = color;
	bottomLine[1].color = color;


	// Add vertices in the correct order to create a filled rectangle representing the line
	paths.push_back(topLine[0]);
	paths.push_back(topLine[1]);
	paths.push_back(bottomLine[1]);
	paths.push_back(bottomLine[0]);

}