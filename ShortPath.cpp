#include "ShortPath.h"
#include "CircleScan.h"



int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1100, 800), "Short Path!!!", sf::Style::Default, settings);
  
    std::vector<sf::Vertex> tracecircle;

#pragma region TestCode

#pragma endregion


#pragma region Defines paths and lines and points

    bool bDrawLineMouse = false;
    bool bFindPath = false;
    //Contains all the path i.e. lines
    std::vector<sf::Vertex> paths;

    //a ref line when moving mouse
    sf::Vertex line[2] = {
                            sf::Vertex(sf::Vector2f(10, 10)),
                            sf::Vertex(sf::Vector2f(100, 10))
                         };

    // Set the line color (optional)
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;



    paths.push_back(line[0]);
    paths.push_back(line[1]);

#pragma endregion


#pragma region Defines for scanning path
    sf::Image winimage;
    sf::Texture wintexture;

    NodeCircle nodeCircle;

    //two circle points 
    sf::Vertex point[2];

    sf::CircleShape circlepoint1(8.f);
    sf::CircleShape circlepoint2(8.f);
    circlepoint1.setFillColor(sf::Color(0, 250, 0));
    circlepoint2.setFillColor(sf::Color(0, 250, 0));
#pragma endregion


#pragma region Text&font Code
    sf::Font font;
    if (!font.loadFromFile("res/Fonts/Banana.ttf"))
    {
        std::cout << "font was not loaded " << std::endl;
        window.close();
    }

    sf::Text *text = new sf::Text();
    text->setFont(font);
    text->setString("press 'F' for finding path");
    text->setCharacterSize(24);
    text->setFillColor(sf::Color::White);
    text->setPosition(sf::Vector2f(100,10));
#pragma endregion



    //////------handling events and draw class--------///////

    while (window.isOpen())
    {


        ///------Event Handling------///
        sf::Event event;
        while (window.pollEvent(event))
        {

#pragma region DefaultEvent

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                std::cout << "Do not resize the windows " << std::endl;
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "scancode: " << event.key.code << std::endl;
                    std::cout << "code: " << event.key.code << std::endl;
                    std::cout << "control: " << event.key.control << std::endl;
                    std::cout << "alt: " << event.key.alt << std::endl;
                    std::cout << "shift: " << event.key.shift << std::endl;
                    std::cout << "system: " << event.key.system << std::endl;
                    window.close();
                }
            }

#pragma endregion


#pragma region Handling Events for Creating paths 
            // For drawing paths and getting the point from the user 
            // winimage is updated to have 


            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::F)
                {
                    bFindPath = true;
                    line[0].color = sf::Color::Red;
                    line[1].color = sf::Color::Red;
                }
            }


           
            //Draw paths 
            /// mouse movement for drawing stuffs
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    
                    bDrawLineMouse = true; 
                    line[0].position.x = event.mouseButton.x;
                    line[0].position.y = event.mouseButton.y;
                    line[1].position.x = event.mouseButton.x;
                    line[1].position.y = event.mouseButton.y;
                    if (bFindPath)
                    {
                        point[0] = line[0];
                        point[1] = line[1];
                        point[0].position.x -= 8;
                        point[0].position.y -= 8;

                        point[1].position.x -= 8;
                        point[1].position.y -= 8;

                    }
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                if (bDrawLineMouse)
                {
                    line[1].position.x = event.mouseMove.x;
                    line[1].position.y = event.mouseMove.y;
                    if (bFindPath)
                    {
                        point[0] = line[0];
                        point[1] = line[1];
                        point[0].position.x -= 8;
                        point[0].position.y -= 8;

                        point[1].position.x -= 8;
                        point[1].position.y -= 8;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bDrawLineMouse = false;
                    if (!bFindPath)
                    {
                        AddLineToPath(paths, line);
                    }
                    

                }
            }

           
#pragma endregion
            
            //Finding path code
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    
                    // Capture the window content into the texture
                    sf::Vector2u windowSize = window.getSize();
                    wintexture.create(windowSize.x, windowSize.y);
                    wintexture.update(window);
                    winimage = wintexture.copyToImage();
                    std::cout << "scanning circle" << std::endl;

                    
                    //TODO: Code to be removed 
                    scanCircleBres(point[0].position.x+8, point[0].position.y+8, 10, tracecircle, winimage);

                }
            }
           
        }








        //////----------window handling segment----------//////
        window.clear();

        window.draw(*text);

        window.draw(&paths[0], paths.size(), sf::Lines);

        // showing lines or points when mouse is moved 
        if (bFindPath)
        {
            circlepoint1.setPosition(point[0].position);
            circlepoint2.setPosition(point[1].position);
            window.draw(circlepoint1);
            window.draw(circlepoint2);

        }
        else
        {
            window.draw(line, 2, sf::Lines);
        }

        //test draw
        if (!tracecircle.empty())
        {
            window.draw(&tracecircle[0], tracecircle.size(), sf::Points);
            

        }



        window.display();
    }

    return 0;
}

void AddLineToPath(std::vector<sf::Vertex>& paths, sf::Vertex line[2])
{
    paths.push_back(line[0]);
    paths.push_back(line[1]);

    line[0].position.x += 1;
    line[0].position.y -= 1;
    line[1].position.x += 1;
    line[1].position.y -= 1;

    paths.push_back(line[0]);
    paths.push_back(line[1]);

    line[0].position.x -= 2;
    line[1].position.x -= 2;

    paths.push_back(line[0]);
    paths.push_back(line[1]);

    line[0].position.x += 1;
    line[0].position.y += 1;
    line[1].position.x += 1;
    line[1].position.y += 2;
}
