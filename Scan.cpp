#include "Scan.h"
#include <cmath>
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

float distanceOfVector(sf::Vector2f& v1, sf::Vector2f& v2)
{
    sf::Vector2f direction(v1 - v2);
    return std::sqrt(direction.x * direction.x + direction.y * direction.y);

}
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
    //vec.clear();
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

bool scanNodecircle(int xc, int yc, int x, int y, std::vector<sf::Vertex>& vec, sf::Image& winimage)
{

    if (winimage.getPixel(xc + x, yc + y).b > 200 && winimage.getPixel(xc + x, yc + y).r < 10)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc - y, yc + x), sf::Color::Red));
        return true;

    }
    if (winimage.getPixel(xc - x, yc + y).b > 200 && winimage.getPixel(xc - x, yc + y).r < 10)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc - y, yc + x), sf::Color::Red));
        return true;
    }

    if (winimage.getPixel(xc + x, yc - y).b > 200 && winimage.getPixel(xc + x, yc - y).r < 10)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc + x, yc - y), sf::Color::Red));
        return true;
    }

    if (winimage.getPixel(xc - x, yc - y).b > 200 && winimage.getPixel(xc - x, yc - y).r < 10)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc - x, yc - y), sf::Color::Red));
        return true;
    }

    if (winimage.getPixel(xc - y, yc + x).b > 200 && winimage.getPixel(xc - x, yc + y).r < 10)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc - y, yc + x), sf::Color::Red));
        return true;
    }


    if (winimage.getPixel(xc + y, yc + x).b > 200 && winimage.getPixel(xc + x, yc + y).r < 10)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc + y, yc + x), sf::Color::Red));
        return true;
    }

    if (winimage.getPixel(xc + y, yc - x).b > 200 && winimage.getPixel(xc + x, yc - y).r < 10)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc + y, yc - x), sf::Color::Red));
        return true;
    }

    if (winimage.getPixel(xc - y, yc - x).b > 200 && winimage.getPixel(xc - x, yc - y).r < 10)
    {
        vec.push_back(sf::Vertex(sf::Vector2f(xc - y, yc - x), sf::Color::Red));
        return true;
    }


}



// using Bresenham's algorithm 
bool scanNodeCircleBres(int xc, int yc, int r, std::vector<sf::Vertex>& vec, sf::Image& winimage)
{
    int x = 0;
    int y = r;
    bool value;
    //vec.clear();
    if (scanNodecircle(xc, yc, x, y - 1, vec, winimage))
        return true;
    if(scanNodecircle(xc, yc, x, y, vec, winimage))
        return true;

    if(scanNodecircle(xc, yc, x, y + 1, vec, winimage))
        return true;


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
        if (scanNodecircle(xc, yc, x, y - 1, vec, winimage))
        {
            return true;
        }
        if (scanNodecircle(xc, yc, x, y, vec, winimage))
        {
            return true;
        }
        if (scanNodecircle(xc, yc, x, y + 1, vec, winimage))
        {
            return true;
        }
    }

    return false;

}




void Debugscancircle(int xc, int yc, int x, int y, std::vector<sf::Vertex>& vec, sf::Image& winimage)
{

    
        vec.push_back(sf::Vertex(sf::Vector2f(xc + x, yc + y), sf::Color::Red));
    
    
        vec.push_back(sf::Vertex(sf::Vector2f(xc - x, yc + y), sf::Color::Red));
    

   
        vec.push_back(sf::Vertex(sf::Vector2f(xc + x, yc - y), sf::Color::Red));
    

    
        vec.push_back(sf::Vertex(sf::Vector2f(xc - x, yc - y), sf::Color::Red));
    

    
        vec.push_back(sf::Vertex(sf::Vector2f(xc - y, yc + x), sf::Color::Red));
    


    
        vec.push_back(sf::Vertex(sf::Vector2f(xc + y, yc + x), sf::Color::Red));
    

    
        vec.push_back(sf::Vertex(sf::Vector2f(xc + y, yc - x), sf::Color::Red));
   

    
        vec.push_back(sf::Vertex(sf::Vector2f(xc - y, yc - x), sf::Color::Red));
    


}



// using Bresenham's algorithm 
void DebugscanCircleBres(int xc, int yc, int r, std::vector<sf::Vertex>& vec, sf::Image& winimage)
{
    int x = 0;
    int y = r;
    //vec.clear();
    Debugscancircle(xc, yc, x, y - 1, vec, winimage);
    Debugscancircle(xc, yc, x, y, vec, winimage);
    Debugscancircle(xc, yc, x, y + 1, vec, winimage);

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
        Debugscancircle(xc, yc, x, y - 1, vec, winimage);
        Debugscancircle(xc, yc, x, y, vec, winimage);
        Debugscancircle(xc, yc, x, y + 1, vec, winimage);

    }

}

sf::Vector2f scanNextWalkPoint(my::Direction movingDirection, sf::Image &winimage, sf::RenderWindow& window)
{
    sf::Vector2f scanPoint;
    sf::Vector2f direction = movingDirection.head - movingDirection.tail;
    sf::Vector2f normal(direction.y, -direction.x);  
    
    // find out unit normal and direction of the movingDirection
    normal = normal / std::sqrt(normal.x * normal.x + normal.y * normal.y); 
    direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);

    direction = direction;
    
    scanPoint = movingDirection.head;

    do
    {
        //getupto the edge of the line
        scanPoint = scanPoint + (direction);
        
    } while (scanNearPointPixel(scanPoint, winimage));


    std::cout << "scanpoints are : " << scanPoint.x << " , " << scanPoint.y << std::endl;
    std::cout <<"heads are : " << movingDirection.head.x << " , " << movingDirection.head.y << std::endl;
    
    //scanPoint = scanPoint - (direction*1.0f);


    return scanPoint;

}


bool scanNearPointPixelforline(sf::Vector2f scanPoint, sf::Image& winimage)
{
    return ((winimage.getPixel(scanPoint.x, scanPoint.y).r > 200)   ||
        (winimage.getPixel(scanPoint.x + 1, scanPoint.y).r > 200) ||
        (winimage.getPixel(scanPoint.x, scanPoint.y + 1).r > 200) ||
        (winimage.getPixel(scanPoint.x - 1, scanPoint.y).r > 200) ||
        (winimage.getPixel(scanPoint.x, scanPoint.y - 1).r > 200) ||
        (winimage.getPixel(scanPoint.x - 1, scanPoint.y - 1).r > 200) ||
        (winimage.getPixel(scanPoint.x + 1, scanPoint.y - 1).r > 200) ||
        (winimage.getPixel(scanPoint.x - 1, scanPoint.y + 1).r > 200) ||
        (winimage.getPixel(scanPoint.x + 1, scanPoint.y + 1).r > 200) 
        );
}




bool scanNearPointPixel(sf::Vector2f scanPoint, sf::Image& winimage)
{


    bool value = false;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (scanPoint.y > 780)
            {
                
                return false;
            }
            if (scanPoint.x > 1080) { return false; }
            if (scanPoint.y < 10)
            {
                
                return false;
            }
            if (scanPoint.x < 10) {  return false; }





            if(winimage.getPixel(scanPoint.x + i, scanPoint.y + j).r > 200);
            {
                value = true;
            }
        }

    }
    return value;
}