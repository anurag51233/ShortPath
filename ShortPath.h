#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Node.h"
#include "Scan.h"
#include "TracePath.h"


void AddLineToPath(std::vector<sf::Vertex>& paths, sf::Vertex line[2], float thickness);
void combineNearbyPixels(std::vector<sf::Vertex>& vec, float threshold);
void FilterLinesFromTracePoints(std::vector<sf::Vertex>& vec, sf::Vector2f center, sf::Image winimage);
int FindNodeCloseToPoint(my::PathNode& pathNode, sf::Vector2f point);

sf::Vector2f FindNextWalkPoint(my::Direction walkdir, sf::Image& winimage);
