#include <SFML/Graphics.hpp>
#include <iostream>




int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Short Path!!!", sf::Style::Default, settings);
  

#pragma region Defines paths and lines

    bool bDrawLineMouse = false;
    
    //Contains all the paths 
    std::vector<sf::Vertex> paths;

    //a ref line
    sf::Vertex line[2] = {
                            sf::Vertex(sf::Vector2f(10, 10)),
                            sf::Vertex(sf::Vector2f(100, 10))
                         };

    // Set the line color (optional)
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;


    paths.push_back(line[0]);
    paths.push_back(line[1]);

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


#pragma region Creating paths


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

                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                if (bDrawLineMouse)
                {
                    line[1].position.x = event.mouseMove.x;
                    line[1].position.y = event.mouseMove.y;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bDrawLineMouse = false;
                    paths.push_back(line[0]);
                    paths.push_back(line[1]);

                }
            }
#pragma endregion

            /*if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                    std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
            }*/
        }









        window.clear();


        window.draw(&paths[0], paths.size(), sf::Lines);
        window.draw(line, 2, sf::Lines);


        window.display();
    }

    return 0;
}