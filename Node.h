#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

namespace my
{
	struct IntersectionNode
	{
		sf::Vector2f pos;
		sf::CircleShape circle;
		sf::Font font;
		sf::Text* text = new sf::Text();
		IntersectionNode()
		{
			

			
			
		}

		IntersectionNode(float x, float y)
		{
			this->pos.x = x;
			this->pos.y = y;
			sf::Vector2f vectorPosition(8, 8);
			vectorPosition = pos - vectorPosition;

			circle.setRadius(8.0f);
			circle.setPosition(vectorPosition);
			circle.setFillColor(sf::Color(0, 0, 255));

			if (!font.loadFromFile("res/Fonts/Banana.ttf"))
			{
				std::cout << "font was not loaded " << std::endl;
			}

			text->setFont(font);
			text->setString("0");
			text->setCharacterSize(20);
			text->setFillColor(sf::Color::White);
			text->setPosition(sf::Vector2f(pos.x, pos.y));
		}


	};
	class PathNode
	{
	public:
		PathNode();
		~PathNode();

		void AddPathNode(sf::Vector2f pos);
		void DrawPathNode(sf::RenderWindow& window, bool drawtext);
	public:
		std::vector<IntersectionNode> pathNodes;

	};
}