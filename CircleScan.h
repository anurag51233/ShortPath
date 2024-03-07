#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

//
//void drawCircle(int xc, int yc, int x, int y, std::vector<sf::Vertex>& vec);
//void circleBres(int xc, int yc, int r, std::vector<sf::Vertex>& vec);
void scancircle(int xc, int yc, int x, int y, std::vector<sf::Vertex>& vec, sf::Image& winimage);
void scanCircleBres(int xc, int yc, int r, std::vector<sf::Vertex>& vec, sf::Image& winimage);

class NodeCircle
{
public:
	NodeCircle();
	void AddNodeCircle(sf::Vector2f& pos);
	void DrawCircle(sf::RenderWindow& window);
	~NodeCircle();

private:

	std::vector<sf::CircleShape> NodeCircles;

};

