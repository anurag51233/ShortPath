#include "CircleScan.h"

// Function to put pixels 
// at subsequence points 
//void drawCircle(int xc, int yc, int x, int y, std::vector<sf::Vertex>& vec)
//{
//    vec.push_back(sf::Vertex(sf::Vector2f(xc + x, yc + y), sf::Color(255, 255, 255)));
//    vec.push_back(sf::Vertex(sf::Vector2f(xc - x, yc + y), sf::Color(255, 255, 255)));
//    vec.push_back(sf::Vertex(sf::Vector2f(xc + x, yc - y), sf::Color(255, 255, 255)));
//    vec.push_back(sf::Vertex(sf::Vector2f(xc - x, yc - y), sf::Color(255, 255, 255)));
//    vec.push_back(sf::Vertex(sf::Vector2f(xc - y, yc + x), sf::Color(255, 255, 255)));
//    vec.push_back(sf::Vertex(sf::Vector2f(xc + y, yc + x), sf::Color(255, 255, 255)));
//    vec.push_back(sf::Vertex(sf::Vector2f(xc + y, yc - x), sf::Color(255, 255, 255)));
//    vec.push_back(sf::Vertex(sf::Vector2f(xc - y, yc - x), sf::Color(255, 255, 255)));
//}

//// using Bresenham's algorithm 
//void circleBres(int xc, int yc, int r, std::vector<sf::Vertex>& vec)
//{
//    int x = 0;
//    int y = r;
//    vec.clear();
//    drawCircle(xc, yc, x, y, vec);
//    drawCircle(xc, yc, x, y + 1, vec);
//    drawCircle(xc, yc, x, y - 1, vec);
//    int p = 1 - r;
//    while (x < y)
//    {
//        if (p < 0)
//        {
//            x = x + 1;
//            y = y;
//            p = p + 2 * x + 1;
//        }
//        else
//        {
//            x = x + 1;
//            y = y - 1;
//            p = p + 2 * (x - y) + 1;
//        }
//        drawCircle(xc, yc, x, y, vec);
//        drawCircle(xc, yc, x, y + 1, vec);
//        drawCircle(xc, yc, x, y - 1, vec);
//
//    }
//
//}
void scancircle(int xc, int yc, int x, int y, std::vector<sf::Vertex>& vec, sf::Image& winimage)
{

    if (winimage.getPixel(xc + x, yc + y).r > 200)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc + x, yc + y), sf::Color::Red));
    }
    if (winimage.getPixel(xc - x, yc + y).r > 200)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc - x, yc + y), sf::Color::Red));
    }

    if (winimage.getPixel(xc + x, yc - y).r > 200)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc + x, yc - y), sf::Color::Red));
    }

    if (winimage.getPixel(xc - x, yc - y).r > 200)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc - x, yc - y), sf::Color::Red));
    }

    if (winimage.getPixel(xc - y, yc + x).r > 200)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc - y, yc + x), sf::Color::Red));
    }


    if (winimage.getPixel(xc + y, yc + x).r > 200)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc + y, yc + x), sf::Color::Red));
    }

    if (winimage.getPixel(xc + y, yc - x).r > 200)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc + y, yc - x), sf::Color::Red));
    }

    if (winimage.getPixel(xc - y, yc - x).r > 200)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc - y, yc - x), sf::Color::Red));
    }


}



// using Bresenham's algorithm 
void scanCircleBres(int xc, int yc, int r, std::vector<sf::Vertex>& vec, sf::Image& winimage)
{
    int x = 0;
    int y = r;
    vec.clear();
    scancircle(xc, yc, x, y - 1, vec, winimage);
    scancircle(xc, yc, x, y, vec, winimage);
    scancircle(xc, yc, x, y + 1, vec, winimage);

    int p = 1 - r;
    while (x < y)

    {
        if (p < 0)
        {
            x = x + 1;
            y = y;
            p = p + 2 * x + 1;
        }
        else
        {
            x = x + 1;
            y = y - 1;
            p = p + 2 * (x - y) + 1;
        }
        scancircle(xc, yc, x, y - 1, vec, winimage);
        scancircle(xc, yc, x, y, vec, winimage);
        scancircle(xc, yc, x, y + 1, vec, winimage);

    }

}


NodeCircle::NodeCircle()
{
}

void NodeCircle::AddNodeCircle(sf::Vector2f& pos)
{
    sf::CircleShape ref(10.0f);
    ref.setFillColor(sf::Color(0, 0, 250));

    NodeCircles.push_back(ref);
}

void NodeCircle::DrawCircle(sf::RenderWindow& window)
{
    if (!NodeCircles.empty())
    {
        for (int i = 0; i < NodeCircles.size(); ++i)
        {
            window.draw(NodeCircles[i]);
        }
    }
}

NodeCircle::~NodeCircle()
{
    NodeCircles.clear();
}

