#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>



namespace my {

	struct Direction
	{
		sf::Vector2f head;
		sf::Vector2f tail;
		int headNode = -1;
		int tailNode = -1;

		Direction()
		{

		}
		Direction(sf::Vector2f h, sf::Vector2f t)
		{
			head = h;
			tail = t;
		}
	};

	class TracePath
	{
	public:
		TracePath();
		~TracePath();

		//void CombineNearLines();

		void AddPath(Direction ref);
		void DrawPath(sf::RenderWindow&	window);
	private:
		void AddLineToPath(std::vector<sf::Vertex>& paths, sf::Vertex line[2], float thickness, sf::Color color	);
	public:
		
		std::vector<Direction> paths;
		std::vector<sf::Vertex> drawPaths;
	};
}