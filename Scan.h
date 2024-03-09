#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TracePath.h"
#include "ShortPath.h"
//
//void drawCircle(int xc, int yc, int x, int y, std::vector<sf::Vertex>& vec);
//void circleBres(int xc, int yc, int r, std::vector<sf::Vertex>& vec);
void scancircle(int xc, int yc, int x, int y, std::vector<sf::Vertex>& vec, sf::Image& winimage);
void Debugscancircle(int xc, int yc, int x, int y, std::vector<sf::Vertex>& vec, sf::Image& winimage);
void scanCircleBres(int xc, int yc, int r, std::vector<sf::Vertex>& vec, sf::Image& winimage);
void DebugscanCircleBres(int xc, int yc, int r, std::vector<sf::Vertex>& vec, sf::Image& winimage);

bool scanNearPointPixel(sf::Vector2f scanPoint, sf::Image& winimage);
bool scanNearPointPixelforline(sf::Vector2f scanPoint, sf::Image& winimage);
sf::Vector2f scanNextWalkPoint(my::Direction movingDirection, sf::Image& winimage, sf::RenderWindow& window);

float distanceOfVector(sf::Vector2f& v1, sf::Vector2f& v2);

bool scanNodeCircleBres(int xc, int yc, int r, std::vector<sf::Vertex>& vec, sf::Image& winimage);
bool scanNodecircle(int xc, int yc, int x, int y, std::vector<sf::Vertex>& vec, sf::Image& winimage);

